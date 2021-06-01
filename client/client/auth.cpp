#include "stdafx.h"
#include "stream.h"


void auth_payload(char* username, char* password, char* mess) {
	strcat_s(mess, PAYLOAD_SIZE, username);
	strcat_s(mess, PAYLOAD_SIZE, " ");
	strcat_s(mess, PAYLOAD_SIZE, password);
}

void login(Socket& socket, char* username, char* password) {
	char mess[PAYLOAD_SIZE] = "";
	auth_payload(username, password, mess);
	socket.tcp_send(LOGIN, 0, mess);
}

void signup(Socket& socket, char* username, char* password) {
	char mess[PAYLOAD_SIZE] = "";
	auth_payload(username, password, mess);
	socket.tcp_send(SIGNUP, 0, mess);
}