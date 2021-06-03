// Server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

#include "declare.h"
#include "const.h"
#include "struct.h"
#include "utilities.h"

int main(int argc, char* argv[])
{
	DWORD				nEvents = 0;
	DWORD				index;
	PLAYER				player[WSA_MAXIMUM_WAIT_EVENTS];
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

	player[0] = (PLAYER)malloc(sizeof(_player));
	player[0]->socket = listenSock;
	events[0] = WSACreateEvent(); //create new events
	nEvents++;

	// Associate event types FD_ACCEPT and FD_CLOSE
	// with the listening socket and newEvent   
	WSAEventSelect(player[0]->socket, events[0], FD_ACCEPT | FD_CLOSE);


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

	SOCKET connSock;
	sockaddr_in clientAddr;
	char clientIP[INET_ADDRSTRLEN];
	int clientAddrLen = sizeof(clientAddr);
	int ret, i, clientPort;

	for (i = 1; i < WSA_MAXIMUM_WAIT_EVENTS; i++) {
		player[i] = (PLAYER)malloc(sizeof(_player));
		updatePlayerInfo(player[i], 0, 0, 0, 0, 0, 0, 0, 0, NOT_AUTHORIZED);
	}
	while (1) {
		//wait for network events on all socket
		index = WSAWaitForMultipleEvents(nEvents, events, FALSE, WSA_INFINITE, FALSE);
		if (index == WSA_WAIT_FAILED) {
			printf("Error %d: WSAWaitForMultipleEvents() failed\n", WSAGetLastError());
			break;
		}

		index = index - WSA_WAIT_EVENT_0;
		WSAEnumNetworkEvents(player[index]->socket, events[index], &sockEvent);

		if (sockEvent.lNetworkEvents & FD_ACCEPT) {
			if (sockEvent.iErrorCode[FD_ACCEPT_BIT] != 0) {
				printf("FD_ACCEPT failed with error %d\n", sockEvent.iErrorCode[FD_READ_BIT]);
				continue;
			}

			if ((connSock = accept(player[index]->socket, (sockaddr *)&clientAddr, &clientAddrLen)) == INVALID_SOCKET) {
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
				updatePlayerInfo(player[nEvents], connSock, clientIP, clientPort, 0, 0, 0, 0, 0, NOT_AUTHORIZED);
				events[nEvents] = WSACreateEvent();
				WSAEventSelect(player[nEvents]->socket, events[nEvents], FD_READ | FD_CLOSE);
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

			ret = Communicate(player[index]);
			//Release socket and event if an error occurs
			if (ret <= 0) {
				closesocket(player[index]->socket);
				clearPlayerInfo(player[index]);
				WSACloseEvent(events[index]);
				if (index != nEvents - 1) Swap(player[index], player[nEvents - 1], events[index], events[nEvents - 1]); // Swap last event and socket with the empties
				nEvents--;
				continue;
			}
			continue;
		}

		if (sockEvent.lNetworkEvents & FD_CLOSE) {
			if (sockEvent.iErrorCode[FD_CLOSE_BIT] != 0) {
				printf("FD_CLOSE failed with error %d from client [%s:%d]\n", sockEvent.iErrorCode[FD_CLOSE_BIT], player[index]->IP, player[index]->port);
			}
			//Release socket and event
			closesocket(player[index]->socket);
			clearPlayerInfo(player[index]);
			WSACloseEvent(events[index]);
			if (index != nEvents - 1) Swap(player[index], player[nEvents - 1], events[index], events[nEvents - 1]);
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
		GAME game = emptyPlayer->game;
		game->players[emptyPlayer->gameIndex] = emptyPlayer;
		game->teams[emptyPlayer->teamIndex]->players[emptyPlayer->placeInTeam] = emptyPlayer;
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
	char *buff = (char *)malloc(BUFF_SIZE);

	received = recv(player->socket, buff, HEADER_SIZE, MSG_WAITALL); // Receive message
	if (received == SOCKET_ERROR) {
		return SOCKET_ERROR;
	}
	printf("AAAAAAAAAAAAAAAAAAA");
	return received;
}

/* The send() wrapper function*/
int Send(PLAYER player, char *buff, int size, int flags) {
	int ret;
	int sent = 0;
	while (sent < size) {
		ret = send(player->socket, buff + sent, size - sent, flags);
		if (ret == SOCKET_ERROR) {
			if (WSAGetLastError() == WSAEWOULDBLOCK) {
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
	while (received < size) {
		ret = recv(player->socket, buff + received, size - received, flags);
		if (ret == SOCKET_ERROR) {
			if (WSAGetLastError() == WSAEWOULDBLOCK) {
				continue;
			}
			else {
				printf("Error %d: Cannot receive from player [%s:%d], disconnect!",WSAGetLastError(), player->IP, player->port);
				return SOCKET_ERROR;
			}
		}
		else received += ret;
	}
	return received;
}