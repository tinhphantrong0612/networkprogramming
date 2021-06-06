#pragma once
#include "response.h"

void pack(char* code, char* payload, char* mess);

void auth_payload(char* username, char* password, char* mess);
void join_lobby_payload(char* game_id, char* team_id, char* mess);

// For login and signup
Auth auth_data(char* payload);

// Lobby activities
Create_lobby create_lobby_data(char* payload);
Get_lobby get_lobby_data(char* payload);
Join_lobby join_lobby_data(char* payload);

Change_team change_team_data(char* payload);
void resolve_team_player_str(char* string, int team_number, int team_player[]);