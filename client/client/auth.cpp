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

User::User(char* username, int state) : state{ state }{
	strcpy_s(this->username, USERNAME_LEN, username);
}

User::~User() {

}

void User::login_request(Socket& socket, char* username, char* password) {
	// Send login request
	char mess[PAYLOAD_SIZE + 1] = "";
	auth_payload(username, password, mess);
	socket.tcp_send(LOGIN, mess);
	strcpy_s(this->username, USERNAME_LEN, username);
}

void User::signup_request(Socket& socket, char* username, char* password1, char* password2) {
	if (strcmp(password1, password2)) {
		throw ValidationError("The confirm password doesn't match");	// Dòng này thay thông báo của UI
	}
	// Send signup request
	char mess[PAYLOAD_SIZE + 1] = "";
	auth_payload(username, password1, mess);
	socket.tcp_send(SIGNUP, mess);
}

void User::login_response(char* payload) {
	Auth response = auth_data(payload);
	if (!strcmp(response.result_code, LOGIN_SUCCESS))
		this->state = USER_AUTH;
	else if (!strcmp(response.result_code, LOGIN_E_NOTEXIST)) {
		strcpy_s(this->username, USERNAME_LEN, "");
	}
	else if (!strcmp(response.result_code, LOGIN_E_PASSWORD)) {
		printf("Password is wrong\n");	// Dòng này thay thông báo của UI
	}
	else {
		printf("Already login or login by other client\n");	// Dòng này thay thông báo của UI
	}
}

void User::signup_response(char* payload) {
	Auth response = auth_data(payload);
	if (!strcmp(response.result_code, SIGNUP_SUCCESS))
		printf("Sign up successful with username: %s", username);	// Dòng này thay thông báo của UI
}

void User::logout_request(Socket& socket) {
	socket.tcp_send(LOGOUT, ""); 
}

void User::logout_rexponse(char* payload) {
	Auth response = auth_data(payload);

	if (!strcmp(response.result_code, LOGOUT_SUCCESS)) {
		printf("Logout success\n");	// Dòng này thay thế bằng UI sang đăng nhập
	}
}