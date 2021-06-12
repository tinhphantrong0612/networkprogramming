#include "stdafx.h"
#include "util.h"
#include "auth.h"

User::User() : state{ USER_NONAUTH } {
	strcpy_s(this->username, USERNAME_LEN, DEFAULT_USRNAME);
}

User::~User() {

}

void User::login_request(Socket& socket, char* username, char* password) {
	// Send login request
	char payload[PAYLOAD_SIZE + 1] = "";
	auth_payload(username, password, payload);
	socket.tcp_send(LOGIN, payload);
	strcpy_s(this->username, USERNAME_LEN, username);
}

void User::signup_request(Socket& socket, char* username, char* password1, char* password2) {
	if (strcmp(password1, password2)) {
		printf("The confirm password doesn't match");	// This line replace by UI notification
	}
	// Send signup request
	char payload[PAYLOAD_SIZE + 1] = "";
	auth_payload(username, password1, payload);
	socket.tcp_send(SIGNUP, payload);
	strcpy_s(this->username, USERNAME_LEN, username);
}

void User::login_response(char* payload) {
	Auth response = auth_data(payload);
	if (!strcmp(response.result_code, LOGIN_SUCCESS))
		this->state = USER_AUTH;
	else if (!strcmp(response.result_code, LOGIN_E_ELSEWHERE) || !strcmp(response.result_code, LOGIN_E_ALREADY)) {
		printf("Already login or login by other client\n");	// This line replace by UI notification
	}
	else if (!strcmp(response.result_code, LOGIN_E_NOTEXIST) || !strcmp(response.result_code, LOGIN_E_PASSWORD)) {
		printf("Username or password are wrong");	// This line replace by UI notification
	}
	else {
		printf("Invalid operation\n");	// This line replace by UI notification
	}
}

void User::signup_response(char* payload) {
	Auth response = auth_data(payload);
	if (!strcmp(response.result_code, SIGNUP_SUCCESS))
		printf("Sign up successful with username: %s", username);	// This line replace by UI notifications
	else if (!strcmp(response.result_code, SIGNUP_E_FORMAT) || !strcmp(response.result_code, SIGNUP_E_EXIST)) {
		printf("Your username is invalid\n");	// This line replace by UI notifications
	}
	else {
		printf("Invalid operation\n");	// This line replace by UI notification
	}
}

void User::logout_request(Socket& socket) {
	socket.tcp_send(LOGOUT, ""); 
}

void User::logout_rexponse(char* payload) {
	Auth response = auth_data(payload);

	if (!strcmp(response.result_code, LOGOUT_SUCCESS)) {
		this->state = USER_NONAUTH;
		printf("Logout success\n");	// This line replace by UI notification and goto login scene
	}
	else if (!strcmp(response.result_code, LOGOUT_E_NOTAUTH)) {
		printf("Your client hasn't logged in\n");	// This line replace by UI notification
	}
	else if (!strcmp(response.result_code, LOGOUT_E_INGAME)) {
		printf("You can't loggout while in the game\n");	// This line replace by UI notification
	}
	else {
		printf("Invalid operation\n");	// This line replace by UI notification
	}
}