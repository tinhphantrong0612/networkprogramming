#include "stdafx.h"
#include "util.h"
#include "auth.h"
#include "except.h"

User::User(Socket socket, char* username) : socket{ socket } {
	strcpy_s(this->username, USERNAME_LEN, username);
}

User::~User() {

}

void User::login(char* password) {
	char mess[PAYLOAD_SIZE] = "";
	auth_payload(this->username, password, mess);
	this->socket.tcp_send(LOGIN, 0, mess);
}

void User::signup(char* password1, char* password2) {
	if (strcmp(password1, password2)) {
		throw ValidationError("The confirm password doesn't match");
	}
	char mess[PAYLOAD_SIZE] = "";
	auth_payload(this->username, password1, mess);
	this->socket.tcp_send(SIGNUP, 0, mess);
}
