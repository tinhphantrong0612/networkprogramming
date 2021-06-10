#pragma once

#include "stream.h"

class User {
public:
	int id;
	char username[USERNAME_LEN];
	int state = USER_NONAUTH;

	User();
	User(char* username);
	User(char* username, int state);
	void login_request(Socket& socket, char* username, char* password);
	void signup_request(Socket& socket, char* username, char* password1, char* password2);
	void logout_request(Socket& socket);

	void login_response(char* payload);
	void signup_response(char* payload);
	void logout_rexponse(char* payload);

	~User();
};
