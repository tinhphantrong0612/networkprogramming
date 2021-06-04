#pragma once

#include "auth.h"

struct Auth {
	int request_code;
};

struct Create_lobby {
	int request_code;
	int id;
};

struct Join_lobby {
	int request_code;
	int id;
	int team_number;
	User player_list[MAX_NUM_PLAYER];
};