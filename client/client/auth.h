#pragma once

#include "stream.h"

class User {
private:
	char username[USERNAME_LEN];
	Socket socket;
	User(Socket socket, char* username);
	~User();

	void login(char* password);
	void signup(char* password1, char* password2);
};
