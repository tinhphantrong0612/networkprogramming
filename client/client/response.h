#pragma once

#include "auth.h"

struct Auth {
	int result_code;
};

struct Create_lobby {
	int result_code;
	int id;
};

struct Get_lobby {
	int result_code;
	Lobby lobbies[MAX_LOBBY];
};

struct Join_lobby {
	int result_code;
	int id;
	int team_number;
	User player_list[MAX_NUM_PLAYER];
};