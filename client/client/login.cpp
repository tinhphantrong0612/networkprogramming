#include "stdafx.h"
#include "stream.h"

void login(Socket& socket, char* username, char* password) {
	char mess[PAYLOAD_SIZE];
	strcat_s(mess, PAYLOAD_SIZE, username);
	strcat_s(mess, PAYLOAD_SIZE, " ");
	strcat_s(mess, PAYLOAD_SIZE, password);
	socket.tcp_send(LOGIN, 0, mess);
}