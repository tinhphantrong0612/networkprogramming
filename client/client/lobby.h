#pragma once
#include "stream.h"
#include "auth.h"
#include "player.h"

class Lobby {
public:
<<<<<<< HEAD
	int id;
	int host;
=======
	unsigned long long id;
>>>>>>> 9a6400dd80bd5ef61e072bc57dbee08e6c1349ab
	int team_number;
	int player_number;
	Player players[MAX_NUM_PLAYER];
	int team_players[MAX_NUM_PLAYER];
	int state;

	Lobby();
	Lobby(unsigned long long id);
	Lobby(unsigned long long id, int team_number);
	~Lobby();

	void create_lobby_request(Socket& socket, int team_number);
	void get_lobby_request(Socket& socket);
	void join_lobby_request(Socket& socket, unsigned long long game_id, int team_id);
	void quit_lobby_request(Socket& socket);
	void start_game_request(Socket& socket);

	Player create_lobby_response(char* payload, char* username);
<<<<<<< HEAD
	void get_lobby_response(char* payload, Lobby* lobbies, int& size);
	Player join_lobby_response(char* payload, char* username, int team_id, int team_number);
=======
	void get_lobby_response(char* payload, Lobby* lobbies,int& size);
	Player join_lobby_response(char* payload, char* username);
>>>>>>> 9a6400dd80bd5ef61e072bc57dbee08e6c1349ab
	void quit_lobby_response(char* payload);
	void start_game_response(char* payload);
	void update_lobby_response(char* payload);
};
