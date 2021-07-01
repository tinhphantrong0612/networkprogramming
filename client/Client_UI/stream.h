#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include "constant.h"

#pragma comment(lib, "ws2_32.lib")

class Socket {
public:
    SOCKET client_socket;
    int port_number;
    char ip_address[INET_ADDRSTRLEN];

    Socket();
    Socket(int port_number, char* ip_address);
    ~Socket();

    void set_timeout(int time);
    int connect_to_server();
    int tcp_send(char* code, char* payload);
    int tcp_receive(char*code, char* payload);
    int Receive(char *buffer);
};

