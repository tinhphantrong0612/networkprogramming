#include "stdafx.h"
#include "stream.h"
#include "util.h"

Socket::Socket(int port_number, char* ip_address) : port_number{ port_number }{
	strcpy_s(this->ip_address, INET_ADDRSTRLEN, ip_address);

	this->client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->client_socket == INVALID_SOCKET) {
		printf("Can't create socket for client with error: %d\n", WSAGetLastError());
	}
}

Socket::~Socket() {
	closesocket(this->client_socket);
};

void Socket::set_timeout(int time) {
	setsockopt(this->client_socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)(&time), sizeof(int));
}

int Socket::connect_to_server() {
	//Set info for server socket
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(this->port_number);
	inet_pton(AF_INET, this->ip_address, &serverAddr.sin_addr);


	//Set client connect state
	if (connect(this->client_socket, (sockaddr *)&serverAddr, sizeof(serverAddr))) {
		printf("Can't connect to the server with error: %d\n", WSAGetLastError());
		return WSAGetLastError();
	}
	return 0;
}

void Socket::tcp_send(char* code, int id, char* payload) {
	char mess[BUFF_SIZE] = "";
	pack(code, id, payload, mess);
	int ret = send(this->client_socket, mess, strlen(mess), 0);
	if (ret == SOCKET_ERROR) {
		printf("Can't send to the server with error: %d\n", WSAGetLastError());
	}
}

int initWSA() {
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData)) {
		WSACleanup();
		printf("Initialize failed!! with error: %d", WSAGetLastError());
		return WSAGetLastError();
	}
	return 0;
}
