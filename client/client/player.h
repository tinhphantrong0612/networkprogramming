#pragma once
#include "stream.h"

class Player {
public:
	int id;
	char username[USERNAME_LEN];
	int team_id;
	int state;

	Player();
	Player(char * username);
	Player(int id, char* username, int team_id, int state);

	~Player();

	void ready_request(Socket& socket);
	void unready_request(Socket& socket);
	void change_team_request(Socket& socket, int team_id);
	void attack_castle_request(Socket& socket, int castle_id, int question_id, int answer_id);
	void attack_mine_request(Socket& socket, int mine_id, int type, int question_id, int answer_id);
	void buy_weapon_request(Socket& socket, int weapon_id);
	void buy_wall_request(Socket& socket, int wall_id);

	void ready_response(char* payload);
	void unready_response(char* payload);
	void change_team_response(char* payload, int& team_id);
	void attack_castle_reponse(char* payload);
	void attack_mine_response(char* payload);
	void buy_weapon_response(char* payload);
	void buy_wall_response(char* payload);
};