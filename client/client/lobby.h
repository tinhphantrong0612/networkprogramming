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
	static void get_lobby_request(Socket& socket);
	void join_lobby_request(Socket& socket, int game_id, int team_id, Player& player);
	void change_team_request(Socket& socket, int team_id);
	void ready_request(Socket& socket);
	void unready_request(Socket& socket);
	void quit_lobby_request(Socket& socket);
	void start_game_request(Socket& socket);

	void create_lobby_response(char* payload);
	static Lobby* get_lobby_response(char* payload);
	Player join_lobby_response(char* payload);
	Player change_team_response(char* payload);
	Player ready_response(char* payload);
	Player unready_response(char* payload);
	void quit_lobby_response(char* payload);
	void start_game_response(char* payload);
};