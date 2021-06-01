#include "stdafx.h"
#include "util.h"
#include "auth.h"
#include "except.h"

User::User(char* username){
	strcpy_s(this->username, USERNAME_LEN, username);
}

User::~User() {

}

void login(Socket& socket, char* username, char* password) {
	char mess[PAYLOAD_SIZE] = "";
	auth_payload(username, password, mess);
	socket.tcp_send(LOGIN, 0, mess);
}

void signup(Socket& socket, char* username, char* password1, char* password2) {
	if (strcmp(password1, password2)) {
		throw ValidationError("The confirm password doesn't match");
	}
	char mess[PAYLOAD_SIZE] = "";
	auth_payload(username, password1, mess);
	socket.tcp_send(SIGNUP, 0, mess);
}
