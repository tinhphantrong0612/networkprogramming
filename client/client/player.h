#pragma once
#include "stream.h"

class Player {
public:
	int id;
	char username[USERNAME_LEN];
	int game_id;
	int team_id;
	int state;

	Player();
	Player(char * username);
	Player(int id, char* username, int game_id, int team_id, int state);
	~Player();

	void change_team_request(Socket& socket, int team_id);
	void change_team_response(char* payload);
};