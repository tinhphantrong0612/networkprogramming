#pragma once
#include "response.h"

void pack(char* code, char* payload, char* mess);

void auth_payload(char* username, char* password, char* mess);


Auth auth_data(char* payload);
Create_lobby create_lobby_data(char* payload);
Get_lobby get_lobby_data(char* payload);
Join_lobby join_lobby_data(char* payload);