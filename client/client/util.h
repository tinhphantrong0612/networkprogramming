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
Quit_lobby quit_lobby_data(char* payload);
Start_game start_game_data(char* payload);
Kick kick_data(char* payload);

void resolve_team_player_str(char* string, int team_number, int team_player[]);

Update_lobby update_lobby_data(char* payload);

// Player update
Change_team change_team_data(char* payload);
Ready ready_data(char* payload);
Unready unready_data(char* payload);
Buy_weapon buy_weapon_data(char* payload);
Buy_wall buy_wall_data(char* payload);
Attack_castle attack_castle_data(char* payload);
Attack_mine attack_mine_data(char* payload);
Cheat cheat_data(char* payload);

// Update game
Update_game update_game_data(char* payload);
Update_castle_ques update_castle_ques_data(char* payload);
Update_mine_ques update_mine_ques_data(char* payload);
Update_castle_attack update_castle_attack_data(char* payload);
Update_mine_attack update_mine_attack_data(char* payload);
Update_buy_weapon update_buy_weapon_data(char* payload);
Update_buy_wall update_buy_wall_data(char* payload);
Update_cheat update_cheat_data(char* payload);

Update_timely update_timely_data(char* payload);