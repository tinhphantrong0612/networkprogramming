#pragma once
#include "stream.h"
#include "auth.h"
#include "player.h"

class Lobby {
public:
	unsigned long long id;
	int host;
	int team_number;
	int player_number;
	int team_players[MAX_NUM_PLAYER];
	Player players[MAX_NUM_PLAYER];
	int state;

	Lobby();
	Lobby(unsigned long long id);
	Lobby(unsigned long long id, int team_number, int state);
	~Lobby();

	void create_lobby_request(Socket& socket, int team_number);
	void get_lobby_request(Socket& socket);
	void join_lobby_request(Socket& socket, int game_id, int team_id);
	void quit_lobby_request(Socket& socket);
	void start_game_request(Socket& socket);
	void kick_request(Socket& socket, int player_id);

	Player create_lobby_response(char* payload, char* username);
	void get_lobby_response(char* payload, Lobby* lobbies, int& size);
	Player join_lobby_response(char* payload, char* username, int& game_id, int& team_id, int& team_number);
	void quit_lobby_response(char* payload);
	void start_game_response(char* payload);
	void update_lobby_response(char* payload);
	void kick_response(char* payload, int player_id);
};
