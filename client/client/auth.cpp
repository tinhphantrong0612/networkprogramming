#include "stdafx.h"
#include "util.h"
#include "auth.h"
#include "except.h"

User::User() {
	strcpy_s(this->username, USERNAME_LEN, DEFAULT_USRNAME);
}

User::User(char* username){
	strcpy_s(this->username, USERNAME_LEN, username);
}

User::User(char* username, bool is_login) : is_login{is_login}{
	strcpy_s(this->username, USERNAME_LEN, username);
}

User::~User() {

}

User User::login(Socket& socket, char* username, char* password) {
	// Send login request
	char mess[PAYLOAD_SIZE] = "";
	auth_payload(username, password, mess);
	socket.tcp_send(LOGIN, mess);
	
	//Receive response
	char code[CODE_SIZE];
	char payload[PAYLOAD_SIZE];
	socket.tcp_receive(code, payload);

	if (!strcmp(code, LOGIN)) {
		Auth auth = auth_data(payload);
		if (auth.request_code == OK)
			return User(username, true);
	}
	return User();
}

void User::signup(Socket& socket, char* username, char* password1, char* password2) {
	if (strcmp(password1, password2)) {
		throw ValidationError("The confirm password doesn't match");
	}
	// Send signup request
	char mess[PAYLOAD_SIZE] = "";
	auth_payload(username, password1, mess);
	socket.tcp_send(SIGNUP, mess);

	//Receive signup response
	char code[CODE_SIZE];
	char payload[PAYLOAD_SIZE];
	socket.tcp_receive(code, payload);

	if (!strcmp(code, LOGIN)) {
		Auth auth = auth_data(payload);
		if (auth.request_code == OK)
			printf("Sign up successful with username: %s", username);	// Dòng này thay thông báo của UI
	}
}
