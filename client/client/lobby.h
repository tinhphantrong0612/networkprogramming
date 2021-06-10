#pragma once
#include "stream.h"
#include "auth.h"
#include "player.h"

class Lobby {
public:
	int id;
	int team_number;
	int player_size;
	Player players[MAX_NUM_PLAYER];
	int team_players[MAX_NUM_PLAYER];
	int state;

	Lobby();
	Lobby(int id);
	Lobby(int id, int team_number);
	~Lobby();

	void create_lobby_request(Socket& socket, int team_number);
	void get_lobby_request(Socket& socket);
	void join_lobby_request(Socket& socket, int game_id, int team_id, Player& player);
	void quit_lobby_request(Socket& socket);
	void start_game_request(Socket& socket);

	void create_lobby_response(char* payload);
	void get_lobby_response(char* payload, Lobby* lobbies, int& size);
	Player join_lobby_response(char* payload);
	void quit_lobby_response(char* payload);
	void start_game_response(char* payload);
	void update_lobby_response(char* payload);
};
