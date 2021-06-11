#pragma once
#include "response.h"

void pack(char* code, char* payload, char* mess);

// Payload
void auth_payload(char* username, char* password, char* payload);
void join_lobby_payload(char* game_id, char* team_id, char* payload);
void attack_castle_payload(char* castle_id, char* question_id, char* answer_id, char* payload);
void attack_mine_payload(char* mine_id, char* type, char* question_id, char* answer_id, char* payload);

// For login and signup
Auth auth_data(char* payload);

// Lobby activities
Create_lobby create_lobby_data(char* payload);
Get_lobby get_lobby_data(char* payload);
Join_lobby join_lobby_data(char* payload);
Change_team change_team_data(char* payload);
Ready ready_data(char* payload);
Unready unready_data(char* payload);
Quit_lobby quit_lobby_data(char* payload);
Start_game start_game_data(char* payload);

void resolve_team_player_str(char* string, int team_number, int team_player[]);

Update_lobby update_lobby_data(char* payload);


// Get question
Castle_question castle_question_data(char* payload);
Mine_question mine_question_data(char* payload);