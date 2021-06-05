#pragma once
#include "stream.h"
#include "auth.h"
#include "player.h"

class Lobby {
public:
	int id;
	int team_number;

	Player players[MAX_NUM_PLAYER];
	int team_players[MAX_NUM_PLAYER];
	int state;

	Lobby();
	Lobby(int id);
	Lobby(int id, int team_number);
	~Lobby();

	static Lobby create_lobby(Socket& socket, int team_number);

	static Lobby* get_lobby(Socket& socket);

	static Lobby join_lobby(Socket& socket, char* id, char* team_id, Player& player);
};