// Server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <map>
#include <string>
#pragma comment(lib, "Ws2_32.lib")
using namespace std;

#include "declare.h"
#include "const.h"
#include "struct.h"
#include "utilities.h"

map <string, pair<string, int>> accountMap;
CRITICAL_SECTION				criticalSection;
GAME							games[GAME_NUM];

int main(int argc, char* argv[])
{
	DWORD				nEvents = 0;
	DWORD				index;
	PLAYER				players[WSA_MAXIMUM_WAIT_EVENTS];
	WSAEVENT			events[WSA_MAXIMUM_WAIT_EVENTS];
	WSANETWORKEVENTS	sockEvent;

	//Step 1: Initiate WinSock
	WSADATA wsaData;
	WORD wVersion = MAKEWORD(2, 2);
	if (WSAStartup(wVersion, &wsaData)) {
		printf("Winsock 2.2 is not supported\n");
		return 0;
	}

	//Step 2: Construct LISTEN socket	
	SOCKET listenSock;
	listenSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//Step 3: Bind address to socket
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(SERVER_PORT);
	inet_pton(AF_INET, SERVER_ADDR, &serverAddr.sin_addr);

	players[0] = (PLAYER)malloc(sizeof(_player));
	players[0]->socket = listenSock;
	events[0] = WSACreateEvent(); //create new events
	nEvents++;

	// Associate event types FD_ACCEPT and FD_CLOSE
	// with the listening socket and newEvent   
	WSAEventSelect(players[0]->socket, events[0], FD_ACCEPT | FD_CLOSE);


	if (bind(listenSock, (sockaddr *)&serverAddr, sizeof(serverAddr)))
	{
		printf("Error %d: Cannot associate a local address with server socket.", WSAGetLastError());
		return 0;
	}

	//Step 4: Listen request from client
	if (listen(listenSock, 10)) {
		printf("Error %d: Cannot place server socket in state LISTEN.", WSAGetLastError());
		return 0;
	}

	printf("Server started!\n");
	loadAccountMap(ACCOUNT_FILE);

	SOCKET connSock;
	sockaddr_in clientAddr;
	char clientIP[INET_ADDRSTRLEN];
	int clientAddrLen = sizeof(clientAddr);
	int ret, i, clientPort;
	
	for (i = 1; i < WSA_MAXIMUM_WAIT_EVENTS; i++) {
		players[i] = (PLAYER)malloc(sizeof(_player));
		updatePlayerInfo(players[i], 0, 0, 0, 0, 0, 0, 0, 0, NOT_AUTHORIZED);
	}

	for (i = 1; i < GAME_NUM; i++) {
		games[i] = (GAME)malloc(sizeof(_game));
		emptyGame(games[i]);
	}
	while (1) {
		//wait for network events on all socket
		index = WSAWaitForMultipleEvents(nEvents, events, FALSE, WSA_INFINITE, FALSE);
		if (index == WSA_WAIT_FAILED) {
			printf("Error %d: WSAWaitForMultipleEvents() failed\n", WSAGetLastError());
			break;
		}

		index = index - WSA_WAIT_EVENT_0;
		WSAEnumNetworkEvents(players[index]->socket, events[index], &sockEvent);

		if (sockEvent.lNetworkEvents & FD_ACCEPT) {
			if (sockEvent.iErrorCode[FD_ACCEPT_BIT] != 0) {
				printf("FD_ACCEPT failed with error %d\n", sockEvent.iErrorCode[FD_READ_BIT]);
				continue;
			}

			if ((connSock = accept(players[index]->socket, (sockaddr *)&clientAddr, &clientAddrLen)) == INVALID_SOCKET) {
				printf("Error %d: Cannot permit incoming connection.\n", WSAGetLastError());
				continue;
			}

			inet_ntop(AF_INET, &clientAddr.sin_addr, clientIP, INET_ADDRSTRLEN);
			clientPort = ntohs(clientAddr.sin_port);

			printf("Accept connection from client [%s:%d]!\n", clientIP, clientPort);

			//Add new client into client array
			if (nEvents == WSA_MAXIMUM_WAIT_EVENTS) {
				printf("\nToo many clients.");
				closesocket(connSock);
			}
			else { // Add to last
				updatePlayerInfo(players[nEvents], connSock, clientIP, clientPort, 0, 0, 0, 0, 0, NOT_AUTHORIZED);
				events[nEvents] = WSACreateEvent();
				WSAEventSelect(players[nEvents]->socket, events[nEvents], FD_READ | FD_CLOSE);
				nEvents++;
			}

			//reset event
			WSAResetEvent(events[index]);
			continue;
		}

		if (sockEvent.lNetworkEvents & FD_READ) {
			//Receive message from client
			if (sockEvent.iErrorCode[FD_READ_BIT] != 0) {
				printf("FD_READ failed with error %d\n", sockEvent.iErrorCode[FD_READ_BIT]);
				break;
			}

			ret = Communicate(players[index]);
			//Release socket and event if an error occurs
			if (ret <= 0) {
				closesocket(players[index]->socket);
				clearPlayerInfo(players[index], accountMap);
				WSACloseEvent(events[index]);
				if (index != nEvents - 1) Swap(players[index], players[nEvents - 1], events[index], events[nEvents - 1]); // Swap last event and socket with the empties
				nEvents--;
				continue;
			}
			continue;
		}

		if (sockEvent.lNetworkEvents & FD_CLOSE) {
			if (sockEvent.iErrorCode[FD_CLOSE_BIT] != 0) {
				printf("FD_CLOSE failed with error %d from client [%s:%d]\n", sockEvent.iErrorCode[FD_CLOSE_BIT], players[index]->IP, players[index]->port);
			}
			//Release socket and event
			closesocket(players[index]->socket);
			clearPlayerInfo(players[index], accountMap);
			WSACloseEvent(events[index]);
			if (index != nEvents - 1) Swap(players[index], players[nEvents - 1], events[index], events[nEvents - 1]);
			nEvents--;
		}
	}
	return 0;
}

/* The swap function replace just-disconnected player with last player in array
* @param	emptyPlayer		[IN/OUT]	Just-disconnected player
* @param	lastPlayer		[IN/OUT]	Last player in array
* @param	emptyEvent		[IN/OUT]	Event bind with emptyPlayer
* @param	lastEvent		[IN/OUT]	Event bind with lastPlayer
* @return	nothing
*/
void Swap(PLAYER emptyPlayer, PLAYER lastPlayer, WSAEVENT emptyEvent, WSAEVENT lastEvent) {
	// Copy memory of lastPlayer to emptyPlayer
	memcpy_s(emptyPlayer, sizeof(_player), lastPlayer, sizeof(_player));
	if (emptyPlayer->game != NULL) { // Replace lastPlayer with emptyPlayer in lastPlayer's game and team
		GAME playerGame = emptyPlayer->game;
		playerGame->players[emptyPlayer->gameIndex] = emptyPlayer;
		playerGame->teams[emptyPlayer->teamIndex]->players[emptyPlayer->placeInTeam] = emptyPlayer;
	}
	emptyEvent = WSACreateEvent(); // Recreate event
	WSAEventSelect(emptyPlayer->socket, emptyEvent, FD_READ | FD_CLOSE); // Bind event with socket
	updatePlayerInfo(lastPlayer, 0, 0, 0, 0, 0, 0, 0, 0, NOT_AUTHORIZED); // Empty the lastPlayer
	WSACloseEvent(lastEvent); // Close lastEvent
}

/* The Communicate function communicate with a player
* @param	player		[IN]		Player's info
* @return	SOCKET_ERROR or number of received bytes
*/
int Communicate(PLAYER player) {
	int received;
	int length;
	char opcode[3];
	char *buff = (char *)malloc(BUFF_SIZE);

	received = Receive(player, buff, HEADER_SIZE, MSG_WAITALL); // Receive message
	if (received == SOCKET_ERROR) {
		return SOCKET_ERROR;
	}
	buff[HEADER_SIZE] = 0;
	opcode[0] = buff[0];
	opcode[1] = buff[1];
	opcode[2] = 0;
	length = ((buff[2] + 256) % 256) * 256 + (buff[3] + 256) % 256;
	received = receiveAndProcessPayload(player, opcode, length, buff);
	free(buff);
	return received;
}

/* The send() wrapper function*/
int Send(PLAYER player, char *buff, int size, int flags) {
	int ret;
	int sent = 0;
	int turn = 0;
	while (sent < size) {
		ret = send(player->socket, buff + sent, size - sent, flags);
		if (ret == SOCKET_ERROR) {
			if (turn > 10) {
				printf("Error %d: Cannot send to player [%s:%d], disconnect!", WSAGetLastError(), player->IP, player->port);
				return SOCKET_ERROR;
			}
			else if (WSAGetLastError() == WSAEWOULDBLOCK) {
				turn++;
				continue;
			}
			else {
				printf("Error %d: Cannot send to player [%s:%d], disconnect!", WSAGetLastError(), player->IP, player->port);
				return SOCKET_ERROR;
			}
		}
		else sent += ret;
	}
	return sent;
}

/* The recv() wrapper function*/
int Receive(PLAYER player, char *buff, int size, int flags) {
	int ret;
	int received = 0;
	int turn = 0;
	while (received < size) {
		ret = recv(player->socket, buff + received, size - received, flags);
		if (ret == SOCKET_ERROR) {
			if (turn > 10) {
				printf("Error %d: Cannot receive to player [%s:%d], disconnect!", WSAGetLastError(), player->IP, player->port);
				return SOCKET_ERROR;
			}
			else if (WSAGetLastError() == WSAEWOULDBLOCK) {
				turn++;
				continue;
			}
			else {
				printf("Error %d: Cannot receive from player [%s:%d], disconnect!", WSAGetLastError(), player->IP, player->port);
				return SOCKET_ERROR;
			}
		}
		else received += ret;
	}
	return received;
}

/* The receiveAndProcessPayload function receives and processes payload
	* @param	player		[IN]		Player's info
	* @param	opcode		[IN]		Operation code
	* @param	length		[IN]		Size of payload
	* @param	buff		[IN/OUT]	Buffer to handle
	* @return	SOCKET_ERROR or process result
*/
int receiveAndProcessPayload(PLAYER player, char *opcode, int length, char *buff) {
	int ret = 0;
	if (length > 0) ret = Receive(player, buff, length, 0);
	buff[ret] = 0;
	if (ret == SOCKET_ERROR) return SOCKET_ERROR;
	if (strcmp(opcode, LOGIN) == 0) ret = handleLogin(player, opcode, buff);
	else if (strcmp(opcode, SIGNUP) == 0) ret = handleSignUp(player, opcode, buff);
	else if (strcmp(opcode, CREATE_GAME) == 0) ret = handleCreateGame(player, opcode, buff);
	else if (strcmp(opcode, GET_LOBBY) == 0) ret = handleGetLobby(player, opcode, buff);
	else if (strcmp(opcode, JOIN_GAME) == 0) ret = handleJoinGame(player, opcode, buff);
	return ret;
}

/* The setResponseAndSend function sets response and sends to player
	* @param	player		[IN]		Player's info
	* @param	opcode		[IN]		Operation code
	* @param	response	[IN]		Response buffer
	* @param	responseLen	[IN]		Size of response
	* @param	buff		[IN]		Buffer to send
	* @return	Send result
*/
int setResponseAndSend(PLAYER player, char *opcode, char *response, int responseLen, char *buff) {
	buff[0] = opcode[0];
	buff[1] = opcode[1];
	buff[2] = responseLen / 256;
	buff[3] = responseLen % 256;
	strcpy_s(buff + 4, BUFF_SIZE, response);
	return Send(player, buff, 4 + responseLen, 0);
}

/* The handleLogin function handle login request from a player
	* @param	player		[IN]		Player's info
	* @param	opcode		[IN]		Operation code
	* @param	buff		[IN]		Buffer to handle
	* @return	Send Response result
*/
int handleLogin(PLAYER player, char *opcode, char *buff) {
	if (player->state != NOT_AUTHORIZED) return setResponseAndSend(player, opcode, LOGIN_E_ALREADY, strlen(LOGIN_E_ALREADY), buff);
	char *space = strchr(buff, ' ');
	if (space == NULL || space + 1 == NULL) {
		return setResponseAndSend(player, opcode, LOGIN_E_NOTEXIST, strlen(LOGIN_E_NOTEXIST), buff);
	}
	unsigned int usernameLen = (int) (space - buff);
	unsigned int passwordLen = strlen(space + 1);
	if (usernameLen > ACCOUNT_SIZE || passwordLen > ACCOUNT_SIZE) {
		return setResponseAndSend(player, opcode, LOGIN_E_NOTEXIST, strlen(LOGIN_E_NOTEXIST), buff);
	}
	char username[ACCOUNT_SIZE];
	char password[ACCOUNT_SIZE];
	sscanf_s(buff, "%s %s", username, ACCOUNT_SIZE, password, ACCOUNT_SIZE);
	if (strlen(password) < passwordLen) return setResponseAndSend(player, opcode, LOGIN_E_NOTEXIST, strlen(LOGIN_E_NOTEXIST), buff);
	map<string, pair<string, int>>::iterator it;
	it = accountMap.find(username);
	if (it == accountMap.end()) return setResponseAndSend(player, opcode, LOGIN_E_NOTEXIST, strlen(LOGIN_E_NOTEXIST), buff);
	else if (strcmp(it->second.first.c_str(), password) != 0) return setResponseAndSend(player, opcode, LOGIN_E_PASSWORD, strlen(LOGIN_E_PASSWORD), buff);
	else if (it->second.second == AUTHORIZED) return setResponseAndSend(player, opcode, LOGIN_E_ELSEWHERE, strlen(LOGIN_E_ELSEWHERE), buff);
	else {
		updatePlayerInfo(player, player->socket, player->IP, player->port, 0, 0, 0, 0, username, AUTHORIZED);
		it->second.second = AUTHORIZED;
		return setResponseAndSend(player, opcode, LOGIN_SUCCESS, strlen(LOGIN_SUCCESS), buff);
	}
}

/* The handleSignUp function handle signup request from a player
	* @param	player		[IN]		Player's info
	* @param	opcode		[IN]		Operation code
	* @param	buff		[IN]		Buffer to handle
	* @return	Send Response result
*/
int handleSignUp(PLAYER player, char *opcode, char *buff) {
	if (player->state != NOT_AUTHORIZED) return setResponseAndSend(player, opcode, SIGNUP_E_LOGGEDIN, strlen(SIGNUP_E_LOGGEDIN), buff);
	char *space = strchr(buff, ' ');
	if (space == NULL || space + 1 == NULL) {
		return setResponseAndSend(player, opcode, SIGNUP_E_FORMAT, strlen(SIGNUP_E_FORMAT), buff);
	}
	unsigned int usernameLen = (int)(space - buff);
	unsigned int passwordLen = strlen(space + 1);
	if (usernameLen > ACCOUNT_SIZE || passwordLen > ACCOUNT_SIZE) {
		return setResponseAndSend(player, opcode, SIGNUP_E_FORMAT, strlen(SIGNUP_E_FORMAT), buff);
	}
	char username[ACCOUNT_SIZE];
	char password[ACCOUNT_SIZE];
	sscanf_s(buff, "%s %s", username, ACCOUNT_SIZE, password, ACCOUNT_SIZE);
	if (strlen(password) < passwordLen) return setResponseAndSend(player, opcode, SIGNUP_E_FORMAT, strlen(SIGNUP_E_FORMAT), buff);
	map<string, pair<string, int>>::iterator it;
	it = accountMap.find(username);
	if (it != accountMap.end()) return setResponseAndSend(player, opcode, SIGNUP_E_EXIST, strlen(SIGNUP_E_EXIST), buff);
	else {
		accountMap[username] = make_pair(password, NOT_AUTHORIZED);
		addNewAccount(ACCOUNT_FILE, username, password);
		return setResponseAndSend(player, opcode, SIGNUP_SUCCESS, strlen(SIGNUP_SUCCESS), buff);
	}
}

/* The handleSignUp function handle signup request from a player
	* @param	player		[IN]		Player's info
	* @param	opcode		[IN]		Operation code
	* @param	buff		[IN]		Buffer to handle
	* @return	Send Response result
*/
int handleCreateGame(PLAYER player, char *opcode, char *buff) {
	if (player->state == NOT_AUTHORIZED) return setResponseAndSend(player, opcode, CREATE_E_NOTAUTH, strlen(CREATE_E_NOTAUTH), buff);
	else if (player->state != AUTHORIZED) return setResponseAndSend(player, opcode, CREATE_E_INGAME, strlen(CREATE_E_NOTAUTH), buff);
	else {
		int i;
		int teamNum = atoi(buff);
		if ((teamNum < 2) || (teamNum > 4)) return setResponseAndSend(player, opcode, CREATE_E_INVALIDTEAM, strlen(CREATE_E_INVALIDTEAM), buff);
		for (i = 0; i < GAME_NUM; i++) {
			if (games[i]->id == 0) {
				createGame(player, games[i], teamNum);
				break;
			}
		}
		if (i == GAME_NUM) return setResponseAndSend(player, opcode, CREATE_E_FULLGAME, strlen(CREATE_E_FULLGAME), buff);
		long long gameId = games[i]->id;
		strcpy_s(buff + 4, BUFF_SIZE, CREATE_SUCCESS);
		strcat_s(buff, BUFF_SIZE, " ");
		_i64toa_s(gameId, buff + 8, BUFF_SIZE, 10);
		return setResponseAndSend(player, opcode, buff + 4, strlen(buff + 4), buff);
	}
}

/* The handleGetLobby function handle get lobby request from a player
	* @param	player		[IN]		Player's info
	* @param	opcode		[IN]		Operation code
	* @param	buff		[IN]		Buffer to handle
	* @return	Send Response result
*/
int handleGetLobby(PLAYER player, char *opcode, char *buff) {
	if (player->state == NOT_AUTHORIZED) return setResponseAndSend(player, opcode, LOBBY_E_NOTAUTH, strlen(LOBBY_E_NOTAUTH), buff);
	else {
		strcpy_s(buff + 4, BUFF_SIZE, LOBBY_SUCCESS);
		buff[7] = ' ';
		getLobbyList(buff + 8);
		return setResponseAndSend(player, opcode, buff + 4, strlen(buff + 4), buff);
	}
}

/* The getLobbyList function get lobby list from all games
	* @param	buff		[IN/OUT]	Buffer to store lobby list
	* @return	Nothing
*/
void getLobbyList(char *buff) {
	int countLobby = 0;
	for (int i = 0; i < GAME_NUM; i++) {
		if (games[i]->id != 0 && games[i]->gameState == WAITING) {
			getGameInfo(games[i], buff + countLobby * 29);
			countLobby++;
		}
	}
}

void getTeamPlayerString(GAME game, char *buff) {
	for (int i = 0; i < PLAYER_NUM; i++) {
		if (game->players[i] == NULL) {
			buff[i] = 'x';
		}
		else {
			_itoa_s(game->players[i]->teamIndex, buff + i, BUFF_SIZE, 10);
		}
	}
	strcat_s(buff, BUFF_SIZE, " ");
}

/* The getGameInfo function handle get a single game info
	* @param	buff		[IN/OUT]	Buffer to store game info
	* @return	Nothing
*/
void getGameInfo(GAME game, char *buff) {
	_i64toa_s(game->id, buff, BUFF_SIZE, 10); // 13 bytes
	strcat_s(buff, BUFF_SIZE, " "); // Add space - 14 bytes
	_itoa_s(game->teamNum, buff + 14, BUFF_SIZE, 10); // add numbers of team - 15 bytes
	strcat_s(buff, BUFF_SIZE, " "); // Add space - 16 bytes
	getTeamPlayerString(game, buff + 16);
}

int handleJoinGame(PLAYER player, char *opcode, char *buff) {
	if (player->state == NOT_AUTHORIZED) return setResponseAndSend(player, opcode, JOIN_E_NOTAUTH, strlen(JOIN_E_NOTAUTH), buff);
	else if (player->state != AUTHORIZED) return setResponseAndSend(player, opcode, JOIN_E_ALREADY, strlen(JOIN_E_ALREADY), buff);
	else {
		char *space = strchr(buff, ' ');
		if (space == NULL) return setResponseAndSend(player, opcode, JOIN_E_FORMAT, strlen(JOIN_E_FORMAT), buff);
		int distance = int(space - buff);
		if (distance != 13) return setResponseAndSend(player, opcode, JOIN_E_FORMAT, strlen(JOIN_E_FORMAT), buff);
		space[0] = 0;
		long long gameId = _atoi64(buff);
		int team = atoi(space + 1);
		int i, emptyPlaceInTeam, emptyPlaceInGame, countPlayer = 0;
		GAME game = NULL;
		for (i = 0; i < GAME_NUM; i++) {
			if (games[i]->id == gameId) {
				game = games[i];
			}
		}
		if (i == GAME_NUM || game == NULL) {
			strcpy_s(buff + 4, BUFF_SIZE, JOIN_E_NOGAME);
			buff[7] = ' ';
			getLobbyList(buff + 8);
			return setResponseAndSend(player, opcode, buff + 4, strlen(buff + 4), buff);
		}
		if (game->gameState != WAITING) {
			strcpy_s(buff + 4, BUFF_SIZE, JOIN_E_PLAYING);
			buff[7] = ' ';
			getLobbyList(buff + 8);
			return setResponseAndSend(player, opcode, buff + 4, strlen(buff + 4), buff);
		}
		for (i = 0; i < PLAYER_NUM; i++) {
			if (game->players[i] == NULL) {
				emptyPlaceInGame = i;
			}
			else countPlayer++;
		}
		if (countPlayer == game->teamNum * 3) {
			strcpy_s(buff + 4, BUFF_SIZE, JOIN_E_FULLGAME);
			buff[7] = ' ';
			getLobbyList(buff + 8);
			return setResponseAndSend(player, opcode, buff + 4, strlen(buff + 4), buff);
		}
		if ((team < 0) || (team > game->teamNum - 1)) {
			strcpy_s(buff + 4, BUFF_SIZE, JOIN_E_NOTEAM);
			buff[7] = ' ';
			getLobbyList(buff + 8);
			return setResponseAndSend(player, opcode, buff + 4, strlen(buff + 4), buff);
		}
		for (i = 0; i < 3; i++) {
			if (game->teams[team]->players[i] == NULL) {
				emptyPlaceInTeam = i;
				break;
			}
		}
		if (i == 3) {
			strcpy_s(buff + 4, BUFF_SIZE, JOIN_E_FULLTEAM);
			buff[7] = ' ';
			getLobbyList(buff + 8);
			return setResponseAndSend(player, opcode, buff + 4, strlen(buff + 4), buff);
		}
		game->teams[team]->players[emptyPlaceInTeam] = player;
		game->players[emptyPlaceInGame] = player;
		updatePlayerInfo(player, player->socket, player->IP, player->port, team, emptyPlaceInTeam, emptyPlaceInGame, game, player->account, JOINT);
		strcpy_s(buff + 4, BUFF_SIZE, JOIN_SUCCESS); // 7 bytes
		buff[7] = ' '; // 8 bytes
		_i64toa_s(game->id, buff + 8, BUFF_SIZE, 10); // 21 bytes
		buff[21] = ' '; // 22 bytes
		buff[22] = emptyPlaceInGame + 48;
		buff[23] = ' ';
		getTeamPlayerString(game, buff + 25);
		strcat_s(buff + 4, BUFF_SIZE, " ");
		for (i = 0; i < PLAYER_NUM; i++) {
			if (game->players[i] != NULL) {
				buff[strlen(buff + 4) + 4] = i + 48;
				strcat_s(buff + 4, BUFF_SIZE, " ");
				strcat_s(buff + 4, BUFF_SIZE, game->players[i]->account);
				strcat_s(buff + 4, BUFF_SIZE, " ");
				buff[strlen(buff + 4) + 4] = game->players[i]->state + 48;
				strcat_s(buff + 4, BUFF_SIZE, " ");
			}
		};
		for (i = 0; i < PLAYER_NUM; i++) {
			if (game->players[i] != NULL) {
				if (setResponseAndSend(game->players[i], opcode, buff + 4, strlen(buff), buff) == SOCKET_ERROR) {
					printf("?????");
				}
			}
		}
	}
	return 0;
}