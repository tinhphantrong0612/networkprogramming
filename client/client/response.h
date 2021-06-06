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
	int team_players[MAX_NUM_PLAYER];
	Player players[MAX_NUM_PLAYER];

	//Extra info
	int player_number;
};

struct Change_team : public Join_lobby{
	Change_team(Join_lobby& data);

};

struct Ready : public Join_lobby {
	Ready(Join_lobby& data);
};

struct Unready : public Join_lobby {
	Unready(Join_lobby& data);
};