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
	int player_id;
	int team_number;
	int team_id;
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


struct Update_lobby {
	char result_code[RESULT_CODE_SIZE + 1];
	int game_id;
	int team_number;
	int request_player_id;
	int team_players[MAX_NUM_PLAYER];
	Player players[MAX_NUM_PLAYER];

	//Extra info
	int player_number;
};

struct Update_game {
	char result_code[RESULT_CODE_SIZE + 1];
};

struct Update_question : public Update_game {
	int question_id;
	char question[QUESTION_LENGTH];
	char answer1[ANSWER_LENGTH];
	char answer2[ANSWER_LENGTH];
	char answer3[ANSWER_LENGTH];
	char answer4[ANSWER_LENGTH];
};

struct Update_castle_ques : public Update_question {
	int castle_id;
};

struct Update_mine_ques : public Update_question {
	int mine_id;
};

struct Castle_info {
	int occupied_by;	// team_id
	int wall_type;
	int wall_def;
};

struct Mine_info {
	int wood;
	int iron;
	int stone;
};

struct Update_resource : public Update_game {
	int request_player_id;
	int castle_id;
	Castle_info castle_info[MAX_CASTLE_OF_GAME];

};