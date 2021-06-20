#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#include "constant.h"

struct Buffer {
	char code[CODE_SIZE + 1];
	char payload[PAYLOAD_SIZE + 1];
	Buffer();
	Buffer(char* code, char* payload) {
		strcpy_s(this->code, CODE_SIZE + 1, code);
		strcpy_s(this->payload, PAYLOAD_SIZE + 1, payload);
	}
};

class Socket {
public:
	SOCKET client_socket;
	int port_number;
	char ip_address[INET_ADDRSTRLEN];

	Socket();
	Socket(int port_number, char* ip_address);
	~Socket();


	// Initialize winsock
	int initWSA();
	void set_timeout(int time);
	int connect_to_server();
	int tcp_send(char* code, char* payload);
	int tcp_receive(Buffer* buffer);
};

