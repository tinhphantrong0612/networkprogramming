#pragma once

#include "stream.h"

class User {
public:
	int id;
	char username[USERNAME_LEN];
	bool is_login= false;

	User();
	User(char* username);
	User(char* username, bool is_login);
	static User login(Socket& socket, char* username, char* password);
	static void signup(Socket& socket, char* username, char* password1, char* password2);

	~User();
};
