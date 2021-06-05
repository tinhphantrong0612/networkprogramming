#pragma once
#include "constant.h"

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

};