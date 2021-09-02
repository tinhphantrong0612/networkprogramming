// SingleIOCPServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <winsock2.h>
#include <WS2tcpip.h>
#include <windows.h>
#include <stdio.h>
#include <process.h>
#include <conio.h>
#include <iostream>
#include <map>
#include <time.h>

using namespace std;

#pragma comment(lib, "Ws2_32.lib")
#include "const.h"
#include "util.h"
#include "struct.h"
#include "handle.h"
// Structure definition
typedef struct {
	SOCKET socket;
	int index; // To refer to player
} PER_HANDLE_DATA, *LPPER_HANDLE_DATA;

map <string, pair<string, int>> accountMap; // Account map, <account, pair<password, login_state>>
CRITICAL_SECTION                accountMapCriticalSection; // Account map's critical section, allow single access at a time
CRITICAL_SECTION				gameListCriticalSection; // Game list's critical section, allow single access at a time
GAME                            games[GAME_NUM]; // Game list
DWORD                           num_player = 0; // Number of current players
PLAYER                          players[MAX_CLIENT]; // Player list

// Pre-declaration function
unsigned __stdcall serverWorkerThread(LPVOID CompletionPortID);
unsigned __stdcall timelyUpdate(LPVOID game); // Update resources to player every 30 seconds
int		header_data_check(char *, int, int&); // Validate header data
int		deleteClient(int); // Remove client
LPPER_IO_OPERATION_DATA	Communicate(LPPER_IO_OPERATION_DATA, PLAYER, char *);
void	processPayload(PLAYER, char *, char *);
void	clearPlayerInfo(PLAYER, char *);

int main(int argc, char* argv[])
{
	HANDLE completionPort;
	SYSTEM_INFO systemInfo;
	LPPER_HANDLE_DATA perHandleData;
	LPPER_IO_OPERATION_DATA perIoData;
	DWORD transferredBytes;
	DWORD flags;
	char buff[BUFF_SIZE];

	// Initiate WinSock
	WSADATA wsaData;
	WORD wVersion = MAKEWORD(2, 2);
	if (WSAStartup(wVersion, &wsaData)) {
		printf("Winsock 2.2 is not supported\n");
		return 0;
	}

	// Setup an I/O completion port
	if ((completionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0)) == NULL) {
		printf("CreateIoCompletionPort() failed with error %d\n", GetLastError());
		return 1;
	}

	//  Determine how many processors are on the system
	GetSystemInfo(&systemInfo);

	//Create worker threads based on the number of processors available on the
	// system. Create two worker threads for each processor 
	for (int i = 0; i < (int)systemInfo.dwNumberOfProcessors * 2; i++) {
		// Create a server worker thread and pass the completion port to the thread
		if (_beginthreadex(0, 0, serverWorkerThread, (void*)completionPort, 0, 0) == 0) {
			printf("Create thread failed with error %d\n", GetLastError());
			return 1;
		}
	}

	// Construct LISTEN socket  
	SOCKET listenSock;
	if ((listenSock = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET) {
		printf("WSASocket() failed with error %d\n", WSAGetLastError());
		return 1;
	}


	//Step 3: Bind address to socket
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(SERVER_PORT);
	inet_pton(AF_INET, SERVER_ADDR, &serverAddr.sin_addr);


	if (bind(listenSock, (sockaddr *)&serverAddr, sizeof(serverAddr)))
	{
		printf("Error %d: Cannot associate a local address with server socket.", WSAGetLastError());
		return 0;
	}

	//Step 4: Listen request from client
	if (listen(listenSock, 20)) {
		printf("Error %d: Cannot place server socket in state LISTEN.", WSAGetLastError());
		return 0;
	}

	printf("Server started!\n");
	loadAccountMap((char*) ACCOUNT_FILE);
	SOCKET connSock;
	sockaddr_in clientAddr;
	char clientIP[INET_ADDRSTRLEN];
	int clientAddrLen = sizeof(clientAddr);
	int i, clientPort;

	for (i = 0; i < MAX_CLIENT; i++) {
		players[i] = (PLAYER)malloc(sizeof(_player));
		updatePlayerInfo(players[i], INVALID_SOCKET, 0, 0, 0, 0, 0, 0, 0, NOT_AUTHORIZED);
		InitializeCriticalSectionAndSpinCount(&players[i]->criticalSection, 1000);
	}

	for (i = 0; i < GAME_NUM; i++) {
		games[i] = (GAME)malloc(sizeof(_game));
		createEmptyGame(games[i]);
		InitializeCriticalSectionAndSpinCount(&games[i]->criticalSection, 1000);
	}

	InitializeCriticalSectionAndSpinCount(&accountMapCriticalSection, 1000);
	InitializeCriticalSectionAndSpinCount(&gameListCriticalSection, 1000);

	while (1) {
		if (num_player == MAX_CLIENT) {
			printf("\nToo many clients.");
		}
		else {
			// Accept connections
			if ((connSock = WSAAccept(listenSock, (sockaddr*)&clientAddr, &clientAddrLen, NULL, 0)) == SOCKET_ERROR) {
				printf("WSAAccept() failed with error %d\n", WSAGetLastError());
				return 1;
			}

			// Create a socket information structure to associate with the socket
			if ((perHandleData = (LPPER_HANDLE_DATA)GlobalAlloc(GPTR, sizeof(PER_HANDLE_DATA))) == NULL) {
				printf("GlobalAlloc() failed with error %d\n", GetLastError());
				return 1;
			}

			// Associate the accepted socket with the original completion port
			printf("Socket number %d got connected...\n", connSock);

			// Add information to players
			inet_ntop(AF_INET, &clientAddr.sin_addr, clientIP, INET_ADDRSTRLEN);
			clientPort = ntohs(clientAddr.sin_port);

			// Find empty slot
			for (int i = 0; i < MAX_CLIENT; i++) {
				if (players[i]->socket == INVALID_SOCKET) {
					updatePlayerInfo(players[i], connSock, clientIP, clientPort, 0, 0, 0, 0, 0, NOT_AUTHORIZED);
					perHandleData->index = i;
					num_player++;
					break;
				}
			}

			if (CreateIoCompletionPort((HANDLE)connSock, completionPort, (DWORD)perHandleData, 0) == NULL) {
				printf("CreateIoCompletionPort() failed with error %d\n", GetLastError());
				return 1;
			}


			// Create per I/O socket information structure to associate with the WSARecv call
			if ((perIoData = (LPPER_IO_OPERATION_DATA)GlobalAlloc(GPTR, sizeof(PER_IO_OPERATION_DATA))) == NULL) {
				printf("GlobalAlloc() failed with error %d\n", GetLastError());
				return 1;
			}

			ZeroMemory(&(perIoData->overlapped), sizeof(OVERLAPPED));
			perIoData->sentBytes = 0;
			perIoData->recvBytes = 0;
			perIoData->dataBuff.len = BUFF_SIZE;
			perIoData->dataBuff.buf = perIoData->buffer;
			perIoData->operation = RECEIVE;
			flags = 0;

			if (WSARecv(connSock, &(perIoData->dataBuff), 1, &transferredBytes, &flags, &(perIoData->overlapped), NULL) == SOCKET_ERROR) {
				if (WSAGetLastError() != ERROR_IO_PENDING) {
					printf("WSARecv() failed with error %d\n", WSAGetLastError());
					closesocket(perHandleData->socket);
					clearPlayerInfo(players[perHandleData->index], buff);
					continue;
				}
			}
		}
	}

	for (i = 0; i < MAX_CLIENT; i++) {
		DeleteCriticalSection(&players[i]->criticalSection);
	}
	for (i = 0; i < GAME_NUM; i++) {
		DeleteCriticalSection(&games[i]->criticalSection);
	}
	DeleteCriticalSection(&accountMapCriticalSection);
	DeleteCriticalSection(&gameListCriticalSection);
	return 0;
}

unsigned __stdcall serverWorkerThread(LPVOID completionPortID)
{
	HANDLE completionPort = (HANDLE)completionPortID;
	DWORD transferredBytes;
	LPPER_HANDLE_DATA perHandleData;
	LPPER_IO_OPERATION_DATA perIoData;
	DWORD flags = 0;
	char buff[BUFF_SIZE];

	while (TRUE) {
		if (GetQueuedCompletionStatus(completionPort, &transferredBytes, (LPDWORD)&perHandleData, (LPOVERLAPPED *)&perIoData, INFINITE) == 0) {
			printf("GetQueuedCompletionStatus() failed with error %d\n", GetLastError());
			closesocket(perHandleData->socket);
			clearPlayerInfo(players[perHandleData->index], buff);
			GlobalFree(perHandleData);
			GlobalFree(perIoData);
			continue;
		}

		// Check to see if an error has occurred on the socket and if so
		// then close the socket and cleanup the SOCKET_INFORMATION structure
		// associated with the socket
		if (transferredBytes == 0) {
			closesocket(perHandleData->socket);
			clearPlayerInfo(players[perHandleData->index], buff);
			GlobalFree(perHandleData);
			GlobalFree(perIoData);
			continue;
		}
		// Receive
		if (perIoData->operation == RECEIVE) {
			perIoData->bufLen += transferredBytes;
			perIoData->buffer[perIoData->bufLen] = 0;
			if (perIoData->bufLen < HEADER_SIZE) { // Keep receiving if smaller than header size
				Receive(players[perHandleData->index], perIoData);
			}
			else {
				int requestLen;
				while (header_data_check(perIoData->buffer, perIoData->bufLen, requestLen)) { // Validate header and get request length
					if (requestLen > strlen(perIoData->buffer)) { // Invalid request length
						requestLen = -1;
						break;
					}
					char request[BUFF_SIZE];
					memset(request, 0, BUFF_SIZE);
					strncpy_s(request, BUFF_SIZE, perIoData->buffer, requestLen); // Get request
					strcpy_s(perIoData->buffer, BUFF_SIZE, perIoData->buffer + requestLen); // Push the leftover to the head of buffer
					perIoData->bufLen -= requestLen; // Update data length in buffer
					memset(perIoData->buffer + perIoData->bufLen, 0, BUFF_SIZE - perIoData->bufLen); // Clear data after buff length

					// Process data with request
					perIoData = Communicate(perIoData, players[perHandleData->index], request);
					/*printf("After Communicate: %p\n", perIoData);*/
				}
				if (requestLen == -1) { // Handle invalid request length
					printf("Invalid message from %d\n", perHandleData->socket);
					closesocket(perHandleData->socket);
					clearPlayerInfo(players[perHandleData->index], buff);
					GlobalFree(perIoData);
					GlobalFree(perHandleData);
					continue;
				}
				else {
					Receive(players[perHandleData->index], perIoData);
				}
			}

		}
		// Send the leftover if not completed
		else if (perIoData->sentBytes + transferredBytes < perIoData->bufLen) {
			Send(players[perHandleData->index], perIoData, transferredBytes);
		}
		else if (perIoData->sentBytes + transferredBytes >= perIoData->bufLen){ // Free perIoData after send
			GlobalFree(perIoData);
		}
	}

}

unsigned __stdcall timelyUpdate(LPVOID game) {
	GAME currGame = (GAME)game;
	int loopCount = 0;
	int index = 0, tmpTeam;
	//char* updateBuff = (char *)malloc(BUFF_SIZE);
	while (TRUE) {
		while (!TryEnterCriticalSection(&currGame->criticalSection)) {}
		//Check if one team remain
		tmpTeam = TEAM_NUM;
		for (index = 0; index < PLAYER_NUM; index++) {
			if (currGame->players[index] != NULL) {
				if (tmpTeam == TEAM_NUM)
					tmpTeam = currGame->players[index]->teamIndex;
				else {
					if (currGame->players[index]->teamIndex != tmpTeam)
						break;
				}
			}
		}
		//Update resource
		if ((getTime() - currGame->startAt) >= loopCount * LOOP_TIME) {
			loopCount++;
			for (int i = 0; i < CASTLE_NUM; i++) {
				if (currGame->castles[i]->occupiedBy >= 0 && currGame->castles[i]->occupiedBy < TEAM_NUM) {
					currGame->teams[currGame->castles[i]->occupiedBy]->gold += ADDITION_GOLD;
				}
			}
			for (int i = 0; i < MINE_NUM; i++) {
				currGame->mines[i]->resources[WOOD] += ADDITION_WOOD;
				currGame->mines[i]->resources[STONE] += ADDITION_STONE;
				currGame->mines[i]->resources[IRON] += ADDITION_IRON;
			}
			currGame = informUpdate(currGame, (char *)TIMELY_UPDATE, currGame->updateBuff, &loopCount);
		}
		//End game
		if (index == PLAYER_NUM || (getTime() - currGame->startAt) >= MAX_LOOP * LOOP_TIME) {
			currGame = informEndGame(currGame, (char *)UPDATE_GAME, (char*)UPDATE_GAME_OVER, currGame->updateBuff);
			resetGame(currGame);
			LeaveCriticalSection(&currGame->criticalSection);
			break;
		}
		LeaveCriticalSection(&currGame->criticalSection);
		Sleep(2000);
	}
	return 1;
}

/* The deleteClient function remove player from player list
* @param	index			[IN]	Player's index in player list
* @return	Player's index in player list
*/
int deleteClient(int index) {
	printf("Closing socket %d\n", players[index]->socket);
	if (closesocket(players[index]->socket) == SOCKET_ERROR) {
		printf("closesocket() failed with error %d\n", WSAGetLastError());
	}
	char buff[BUFF_SIZE];
	clearPlayerInfo(players[index], buff); // Clear player's information
	return index;
}

/* The header_data_check function validate header of a request and calculate request payload size
* @param	buffer			[IN]	Buffer of a single perIoData object
* @param	size			[IN]	Buffer length of a single perIoData object
* @param	requestLen		[OUT]	Request payload size
* @return	true/false if valid/not valid
*/
int header_data_check(char * buffer, int size, int &requestLen) {
	if (size > HEADER_SIZE) {
		if ((buffer[HEADER_SIZE - 2] + 255) % 256 > 8) { // When the payload is too big
			requestLen = -1;
			return false;
		}
	}
	requestLen = ((buffer[HEADER_SIZE - 2] + 255) % 256) * 255 + (buffer[HEADER_SIZE - 1] + 255) % 256 + HEADER_SIZE; // Calculate payload length
	return size < requestLen ? false : true;
}

/* The Receive function receive message from client, each client has a single LPPER_IO_OPERATION_DATA object for receiving on server
* @param	player			[IN]	Client to receive from
* @param	perIoData		[IN]	LPPER_IO_OPERATION_DATA object to receive and store message
* @return	0
*/
int Receive(PLAYER player, LPPER_IO_OPERATION_DATA perIoData) {
	DWORD transferredBytes;
	DWORD flags = 0;
	ZeroMemory(&(perIoData->overlapped), sizeof(OVERLAPPED));
	perIoData->dataBuff.len = BUFF_SIZE - perIoData->bufLen;
	perIoData->dataBuff.buf = perIoData->buffer + perIoData->bufLen;
	if (WSARecv(player->socket, &(perIoData->dataBuff), 1, &transferredBytes, &flags, &(perIoData->overlapped), NULL) == SOCKET_ERROR) {
		if (WSAGetLastError() != ERROR_IO_PENDING) {
			printf("WSARecv() failed with error %d\n", WSAGetLastError());
			return WSAGetLastError();
		}
	}
	return 0;
}

/* The send() wrapper function*/
/* The Send function send message to a client, each send use a seperated LPPER_IO_OPERATION_DATA object
* @param	player			[IN]	Player receive message
* @param	buff			[IN]	Message to send
* @return	0/1
*/
int Send(PLAYER player, char* buff) {
	DWORD transferredBytes;
	LPPER_IO_OPERATION_DATA perIoData;

	// Create per I/O socket information structure to associate with the WSASend call
	if ((perIoData = (LPPER_IO_OPERATION_DATA)GlobalAlloc(GPTR, sizeof(PER_IO_OPERATION_DATA))) == NULL) {
		printf("GlobalAlloc() failed with error %d\n", GetLastError());
		return 1;
	}

	ZeroMemory(&(perIoData->overlapped), sizeof(OVERLAPPED));
	strcpy_s(perIoData->buffer, BUFF_SIZE, buff);

	perIoData->bufLen = strlen(buff);
	perIoData->dataBuff.buf = perIoData->buffer;
	perIoData->dataBuff.len = perIoData->bufLen;
	perIoData->recvBytes = 0;
	perIoData->sentBytes = 0;
	perIoData->operation = SEND;
	if (WSASend(player->socket, &(perIoData->dataBuff), 1, &transferredBytes, 0, &(perIoData->overlapped), NULL) == SOCKET_ERROR) {
		if (WSAGetLastError() != ERROR_IO_PENDING) {
			printf("WSASend() failed with error %d\n", WSAGetLastError());
			return 0;
		}
	}

	return 1;
}
/* The Send function send leftover to a client if not completed
* @param	player			[IN]	Player receive message
* @param	perIoData		[IN]	LPPER_IO_OPERATION_DATA object store message to send
* @param	transferredBytes	[IN]	Number of bytes were sent
* @return	0/1
*/
int Send(PLAYER player, LPPER_IO_OPERATION_DATA perIoData, DWORD transferredBytes) {
	ZeroMemory(&(perIoData->overlapped), sizeof(OVERLAPPED));
	perIoData->sentBytes += transferredBytes;
	perIoData->dataBuff.buf = perIoData->buffer + perIoData->sentBytes;
	perIoData->dataBuff.len = perIoData->bufLen - perIoData->sentBytes;
	perIoData->operation = SEND;
	if (WSASend(player->socket, &(perIoData->dataBuff), 1, &transferredBytes, 0, &(perIoData->overlapped), NULL) == SOCKET_ERROR) {
		if (WSAGetLastError() != ERROR_IO_PENDING) {
			printf("WSASend() failed with error %d\n", WSAGetLastError());
			return WSAGetLastError();
		}
	}
	return 1;
}

/* The Communicate function split opcode and payload
* @param	perIoData		[IN/OUT]	Somehow after join game, perIoData from thread will be lost, so store it in this function
* @param	player			[IN/OUT]	Player
* @param	buff			[IN]		A message from client
* @return	passed in perIoData
*/
LPPER_IO_OPERATION_DATA Communicate(LPPER_IO_OPERATION_DATA perIoData, PLAYER player, char *buff) {
	char opcode[OP_SIZE + 1];
	strncpy_s(opcode, OP_SIZE + 1, buff, OP_SIZE);
	strcpy_s(buff, BUFF_SIZE, buff + HEADER_SIZE);
	processPayload(player, opcode, buff);
	return perIoData;
}

/* The processPayload function handle request from client
* @param	player			[IN/OUT]	Player
* @param	opcode			[IN]		Operation code
* @param	buff			[IN]		Buffer to send message
* @return	nothing
*/
void processPayload(PLAYER player, char *opcode, char *buff) {
	if (strcmp(opcode, LOGIN) == 0) {
		printf("Handle login request from player [%s:%d]: %s\n", player->IP, player->port, buff);
		handleLogin(player, opcode, buff);
	}
	else if (strcmp(opcode, SIGNUP) == 0) {
		printf("Handle signup request from player [%s:%d]: %s\n", player->IP, player->port, buff);
		handleSignUp(player, opcode, buff);
	}
	else if (strcmp(opcode, CREATE_GAME) == 0) {
		printf("Handle create game request from player [%s:%d]: %s\n", player->IP, player->port, buff);
		handleCreateGame(player, opcode, buff);
	}
	else if (strcmp(opcode, GET_LOBBY) == 0) {
		printf("Handle get lobby request from player [%s:%d]: %s\n", player->IP, player->port, buff);
		handleGetLobby(player, opcode, buff);
	}
	else if (strcmp(opcode, JOIN_GAME) == 0) {
		printf("Handle join game request from player [%s:%d]: %s\n", player->IP, player->port, buff);
		handleJoinGame(player, opcode, buff);
	}
	else if (strcmp(opcode, CHANGE_TEAM) == 0) {
		printf("Handle change team request from player [%s:%d]: %s\n", player->IP, player->port, buff);
		handleChangeTeam(player, opcode, buff);
	}
	else if (strcmp(opcode, READY_PLAY) == 0) {
		printf("Handle ready request from player [%s:%d]: %s\n", player->IP, player->port, buff);
		handleReadyPlay(player, opcode, buff);
	}
	else if (strcmp(opcode, UNREADY_PLAY) == 0) {
		printf("Handle unready request from player [%s:%d]: %s\n", player->IP, player->port, buff);
		handleUnreadyPlay(player, opcode, buff);
	}
	else if (strcmp(opcode, QUIT_GAME) == 0) {
		printf("Handle quit game request from player [%s:%d]: %s\n", player->IP, player->port, buff);
		handleQuitGame(player, opcode, buff);
	}
	else if (strcmp(opcode, START_GAME) == 0) {
		printf("Handle start game request from player [%s:%d]: %s\n", player->IP, player->port, buff);
		handleStartGame(player, opcode, buff);
	}
	else if (strcmp(opcode, KICK) == 0) {
		printf("Handle kick request from player [%s:%d]: %s\n", player->IP, player->port, buff);
		handleKick(player, opcode, buff);
	}
	else if (strcmp(opcode, LOGOUT) == 0) {
		printf("Handle log out request from player [%s:%d]: %s\n", player->IP, player->port, buff);
		handleLogOut(player, opcode, buff);
	}
	else if (strcmp(opcode, ATTACK_CASTLE) == 0) {
		printf("Handle attack castle from player [%s:%d]: %s\n", player->IP, player->port, buff);
		handleAttackCastle(player, opcode, buff);
	}
	else if (strcmp(opcode, ATTACK_MINE) == 0) {
		printf("Handle attack mine from player [%s:%d]: %s\n", player->IP, player->port, buff);
		handleAttackMine(player, opcode, buff);
	}
	else if (strcmp(opcode, BUY_WEAPON) == 0) {
		printf("Handle buy weapon from player [%s:%d]: %s\n", player->IP, player->port, buff);
		handleBuyWeapon(player, opcode, buff);
	}
	else if (strcmp(opcode, BUY_WALL) == 0) {
		printf("Handle buy wall from player [%s:%d]: %s\n", player->IP, player->port, buff);
		handleBuyWall(player, opcode, buff);
	}
	else if (strcmp(opcode, CHEAT) == 0) {
		printf("Guess who is cheating? Player[%s:%d]: %s", player->IP, player->port, buff);
		handleCheat(player, opcode, buff);
	}
	else {
		printf("Unknown header from player [%s:%d]: %s\n", player->IP, player->port, buff);
		setResponseAndSend(player, (char *) UNKNOWN_HEADER, (char *) UNKNOWN_HEADER, strlen(UNKNOWN_HEADER), buff);
	}
	return;
}

/* The updatePlayerInfo function clear a player info
* @param	player			[IN/OUT]	Player
* @param	buff			[IN]		Buffer to send message to all other player in game room
* @return	nothing
*/
void clearPlayerInfo(PLAYER player, char *buff) {
	// Remove player from game and team
	while (!TryEnterCriticalSection(&player->criticalSection)) {}
	// If player in a game
	if (player->game != NULL) {
		while (!TryEnterCriticalSection(&player->game->criticalSection)) {}
		GAME game = player->game;
		int i;
		game->players[player->gameIndex] = NULL; // Remove player from game
		game->teams[player->teamIndex]->players[player->placeInTeam] = NULL; // Remove player from team
		for (i = 0; i < PLAYER_NUM; i++) { // Find the not-empty place in game
			if (game->players[i] != NULL) {
				break;
			}
		}
		if (i == PLAYER_NUM) emptyGame(game); // If all of them are empty, empty the game
		else {
			if (player->gameIndex == game->host) { // Update host player
				game->host = i;
				if (game->gameState == ONGOING) game->players[game->host]->state = PLAYING;
				else if (game->gameState == WAITING) game->players[game->host]->state = JOINT;
			}
			// Inform game room about player's leaving
			informGameRoomChange(game, player->gameIndex, (char *) UPDATE_LOBBY, (char *) UPDATE_LOBBY_QUIT, buff);
		}
		LeaveCriticalSection(&game->criticalSection);
	}
	map<string, pair<string, int>>::iterator it = accountMap.find(player->account); // Log player out
	if (it != accountMap.end()) it->second.second = NOT_AUTHORIZED;
	updatePlayerInfo(player, INVALID_SOCKET, 0, 0, 0, 0, 0, 0, 0, NOT_AUTHORIZED); // Update player information
	LeaveCriticalSection(&player->criticalSection);
}
