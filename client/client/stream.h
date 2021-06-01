#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#include "constant.h"

class Socket {
private:
	SOCKET client_socket;
	int port_number;
	char ip_address[INET_ADDRSTRLEN];

public:
	Socket(int port_number, char* ip_address);
	~Socket();

	void set_timeout(int time);
	int connect_to_server();
	void tcp_send(char* code, int id, char* payload);
};

// Initialize winsock
int initWSA();
