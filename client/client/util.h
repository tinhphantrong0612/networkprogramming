#pragma once
#include "response.h"

void pack(char* code, char* payload, char* mess);

void auth_payload(char* username, char* password, char* mess);


Auth auth_data(char* payload);
Create_lobby lobby_data(char* payload);