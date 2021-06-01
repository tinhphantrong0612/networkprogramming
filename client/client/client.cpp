// client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

int main(int argc, char* argv[])
{
	//Get port number and address
	int port_number = atoi(argv[2]);
	char* ip_address = argv[1];

	// Initialize winsock
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData)) {
		WSACleanup();
		printf("Initialize failed!! with error: %d", WSAGetLastError());
		return 1;
	}

	//Create client socket
	SOCKET clientSock;
	clientSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSock == INVALID_SOCKET) {
		printf("Can't create socket for client with error: %d\n", WSAGetLastError());
		return 1;
	}


	//Set timeout option
	int tv = 5000;		//Timeout: 5s
	setsockopt(clientSock, SOL_SOCKET, SO_RCVTIMEO, (const char*)(&tv), sizeof(int));

	//Set info for server socket
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port_number);
	inet_pton(AF_INET, ip_address, &serverAddr.sin_addr);


	//Set client connect state
	if (connect(clientSock, (sockaddr *)&serverAddr, sizeof(serverAddr))) {
		printf("Can't connect to the server with error: %d\n", WSAGetLastError());
		return 1;
	}

	printf("Client started!!\n");

	bool running = true;
	while (running) {
		printf("Haha");
	}

	//End
	closesocket(clientSock);
	WSACleanup();
	return 0;
}

