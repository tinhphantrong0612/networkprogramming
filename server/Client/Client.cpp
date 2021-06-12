// Client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "winsock2.h"
#include "ws2tcpip.h"
#include <iostream>
#include <string>
#include <process.h>

#pragma comment(lib, "Ws2_32.lib")

#define BUFF_SIZE 2048

using namespace std;

void process(char *, int);

unsigned __stdcall receiveThread(void * param) {
	SOCKET client = (SOCKET)param;
	char *buff = (char *)malloc(BUFF_SIZE);
	int ret, msgLen, received;
	while (1) {
		ret = recv(client, buff, 5, MSG_WAITALL);
		if (ret == SOCKET_ERROR) {
			printf("Error %d: Cannot receive message from server.\n", WSAGetLastError());
			return 0;
		}
		else {
			msgLen = (((buff[3] + 256) % 256) * 256) + (buff[4] + 256) % 256;
			received = 0;

			while (received < msgLen) {
				ret = recv(client, buff + received, msgLen - received, 0);
				if (ret == SOCKET_ERROR) {
					printf("Error %d: Cannot receive message from server.\n", WSAGetLastError());
					return 0;
				}
				else {
					received += ret;
				}
			}
			buff[received] = 0;
			printf("Response: %s\n", buff);
		}
	}
}

void process(char *buff, int size) {
	printf("Response: %s\n", buff);
}

int main(int argc, char *argv[])
{
	// Step 1: Init winsock
	WSADATA wsaData;
	WORD wVersion = MAKEWORD(2, 2);
	if (WSAStartup(wVersion, &wsaData)) {
		printf("WinSock 2.2 is not supported!\n");
		return 0;
	}

	printf("WinSock Initiated!\n");

	// Step 2: Construct socket
	SOCKET client;
	client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (client == INVALID_SOCKET) {
		printf("Error %d: Cannot create server socket.", WSAGetLastError());
		return 0;
	}

	// Step 3: Specify server address
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons((atoi(argv[2])));
	inet_pton(AF_INET, argv[1], &serverAddr.sin_addr);

	// Step 4: Request connect to server
	if (connect(client, (sockaddr *)&serverAddr, sizeof(serverAddr))) {
		printf("Error %d: Cannot connect to server.\n", WSAGetLastError());
		return 0;
	}

	printf("Connected to server!\n");

	// Step 5: Communicate with server
	char *buff = (char *)malloc(BUFF_SIZE);
	int ret, msgLen, sent, received, func;
	_beginthreadex(NULL, NULL, &receiveThread, (void*) client, 0, 0);

	while (1) {
		// Send message
		printf("Choose function:\n1. Login\n2. Sign Up\n3. Log out\n4. Create Game\n5. Get Lobby\n6. Join Game\nYou choose: ");
		gets_s(buff, BUFF_SIZE);
		if (buff[0] == 49) strcpy_s(buff, BUFF_SIZE, "100");
		else if (buff[0] == 50) strcpy_s(buff, BUFF_SIZE, "101");
		else if (buff[0] == 51) strcpy_s(buff, BUFF_SIZE, "102");
		else if (buff[0] == 52) strcpy_s(buff, BUFF_SIZE, "103");
		else if (buff[0] == 53) strcpy_s(buff, BUFF_SIZE, "104");
		else if (buff[0] == 54) strcpy_s(buff, BUFF_SIZE, "105");
		printf("Send to server: ");
		gets_s(buff + 5, BUFF_SIZE);

		buff[3] = strlen(buff + 5) / 256;
		buff[4] = strlen(buff + 5) % 256;

		msgLen = strlen(buff + 5) + 5; // number of bytes left after send
		sent = 0; // Number of sent bytes
		while (sent < msgLen) {
			ret = send(client, buff + sent, msgLen - sent, 0);
			if (ret == SOCKET_ERROR) {
				printf("Error %d: Cannot send data to server.\n", WSAGetLastError());
				return 0;
			}
			sent += ret;
		}
		memset(buff, 0, BUFF_SIZE);
	}

	// Step 6: Close socket
	closesocket(client);

	// Step 7: Terminate Winsock
	WSACleanup();

	return 1;
}