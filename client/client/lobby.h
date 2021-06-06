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

	void create_lobby_request(Socket& socket, int team_number);
	void get_lobby_request(Socket& socket);
	void join_lobby_request(Socket& socket, char* id, char* team_id, Player& player);
	void change_team_request(Socket& socket, int team_id);
	void ready_request(Socket& socket);
	void unready_request(Socket& socket);

	void create_lobby_response(char* payload);
	Lobby* get_lobby_response(char* payload);
	Player join_lobby_response(char* payload);
	Player change_team_response(char* payload);
	Player ready_response(char* payload);
	Player unready_response(char* payload);
};