#pragma once

#include "auth.h"
#include "lobby.h"
#include "player.h"
#include "question.h"

struct Auth {
	char result_code[RESULT_CODE_SIZE + 1];
};

struct Create_lobby {
	char result_code[RESULT_CODE_SIZE + 1];
	int id;
};

struct Get_lobby {
	char result_code[RESULT_CODE_SIZE + 1];
	Lobby lobbies[MAX_LOBBY];
	int size;
};

struct Join_lobby {
	char result_code[RESULT_CODE_SIZE + 1];
	int id;
	int ingame_id;
	int team_number;
	int team_players[MAX_NUM_PLAYER];
	Player players[MAX_NUM_PLAYER];

	//Extra info
	int player_number;
};

struct Ready{
	char result_code[RESULT_CODE_SIZE + 1];
};

struct Unready : public Join_lobby {
	char result_code[RESULT_CODE_SIZE + 1];
};

struct Change_team : public Join_lobby{
	char result_code[RESULT_CODE_SIZE + 1];
};


struct Quit_lobby {
	char result_code[RESULT_CODE_SIZE + 1];
};

struct Start_game {
	char result_code[RESULT_CODE_SIZE + 1];
};

struct Castle_question {
	int id;
	int castle_id;
	Question questions[MAX_QUESTION];
};

struct Mine_question {
	int id;
	int mine_id;
	int type;
	Question questions[MAX_QUESTION];
};