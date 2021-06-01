#pragma once

#include "stream.h"

class User {
public:
	char username[USERNAME_LEN];
	bool is_ready = false;
	User(char* username);
	~User();
};
