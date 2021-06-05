// client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stream.h"


void receive_data(Socket& socket);


int main(int argc, char* argv[])
{
	//Get port number and address
	int port_number = atoi(argv[2]);
	char* ip_address = argv[1];


	return 0;
}

void receive_data(Socket& socket) {
	//Receive response
	char code[CODE_SIZE + 1];
	char payload[PAYLOAD_SIZE + 1];
	socket.tcp_receive(code, payload);
	if (!strcmp(code, LOGIN)) {

	}
	else if (!strcmp(code, SIGNUP)) {

	}
}