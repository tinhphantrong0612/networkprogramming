#pragma once

#include "auth.h"
#include "lobby.h"
#include "player.h"

struct Auth {
	char* result_code;
};

struct Create_lobby {
	char* result_code;
	int id;
};

struct Get_lobby {
	char* result_code;
	Lobby lobbies[MAX_LOBBY];
};

struct Join_lobby {
	char* result_code;
	int id;
	int ingame_id;
	int team_number;
	int player_number;
	int team_players[MAX_NUM_PLAYER];
	Player players[MAX_NUM_PLAYER];

};