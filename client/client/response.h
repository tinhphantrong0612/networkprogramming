#pragma once

#include "auth.h"
#include "lobby.h"
#include "player.h"
#include "question.h"

struct Response {
	char result_code[RESULT_CODE_SIZE + 1];
};

struct Auth: public Response {
};

struct Create_lobby : public Response  {
	int id;
};

struct Get_lobby : public Response {
	Lobby lobbies[MAX_LOBBY];
	int size;
};

struct Join_lobby : public Response  {
	int id;
	int player_id;
	int team_number;
	int team_id;
};

struct Ready : public Response {
};

struct Unready : public Response{
};

struct Change_team : public Response {
};


struct Quit_lobby : public Response  {
};

struct Start_game : public Response  {

};

struct Update_lobby : public Response  {
	int game_id;
	int team_number;
	int request_player_id;
	int team_players[MAX_NUM_PLAYER];
	Player players[MAX_NUM_PLAYER];

	//Extra info
	int player_number;
};


struct Buy_wall : public Response{

};

struct Buy_weapon : public Response {

};

struct Attack_castle : public Response {

};

struct Attack_mine : public Response {

};

struct Update_game : public Response  {
};

struct Update_question : public Update_game {
	int question_id;
	char question[QUESTION_LENGTH + 1];
	char answer1[ANSWER_LENGTH + 1];
	char answer2[ANSWER_LENGTH + 1];
	char answer3[ANSWER_LENGTH + 1];
	char answer4[ANSWER_LENGTH + 1];
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

struct Update_timely{
	// Castle info
	int occupied[MAX_CASTLE_OF_GAME];
	int wall_type[MAX_CASTLE_OF_GAME];
	int wall_def[MAX_CASTLE_OF_GAME];

	// Mine info
	int wood_mine[MAX_MINE_OF_GAME];
	int stone_mine[MAX_MINE_OF_GAME];
	int iron_mine[MAX_MINE_OF_GAME];

	// Team info
	int weapon_type[MAX_TEAM_OF_GAME];
	int weapon_atk[MAX_TEAM_OF_GAME];
	int gold_team[MAX_TEAM_OF_GAME];
	int wood_team[MAX_TEAM_OF_GAME];
	int stone_team[MAX_TEAM_OF_GAME];
	int iron_team[MAX_TEAM_OF_GAME];
};