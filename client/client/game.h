#pragma once

#include "team.h"
#include "mine.h"
#include "lobby.h"

class Game {
public:
	int id;
	int start_at;
	int team_number;
	Team teams[MAX_TEAM_OF_GAME];
	Mine mines[MAX_MINE_OF_GAME];
	Castle castles[MAX_CASTLE_OF_GAME];

	Game();
	Game(int id, int team_number, Player* players, int player_size);
	void init_game(int id, int team_number, Player* players, int player_number);
	void update_timely_response(char* payload);
	void update_game_response(char * payload, Lobby& lobby);
};