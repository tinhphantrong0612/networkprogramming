#include "stdafx.h"
#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "constant.h"
#include "lobby.h"
#include "player.h"


void pack(char* code, char* payload, char* mess) {

	// Cast payload length -> string
	char payload_len[PAYLOAD_LEN_SIZE + 1];
	int len = strlen(payload);
	int first_byte = len / 256;
	int second_byte = len % 256;
	payload_len[0] = first_byte;
	payload_len[1] = second_byte;

	// Pack as 1 request
	strcat_s(mess, BUFF_SIZE, code);
	strcat_s(mess, BUFF_SIZE, payload_len);
	strcat_s(mess, BUFF_SIZE, payload);

}

void auth_payload(char* username, char* password, char* mess) {
	strcat_s(mess, PAYLOAD_SIZE, username);
	strcat_s(mess, PAYLOAD_SIZE, " ");
	strcat_s(mess, PAYLOAD_SIZE, password);
}

void join_lobby_payload(char* game_id, char* team_id, char* mess) {
	strcat_s(mess, PAYLOAD_SIZE, game_id);
	strcat_s(mess, PAYLOAD_SIZE, " ");
	strcat_s(mess, PAYLOAD_SIZE, team_id);
}


Auth auth_data(char* payload) {
	return Auth{payload};
}

Create_lobby create_lobby_data(char* payload) {
	char *next_token;
	char* result_code = strtok_s(payload, DELIM_RESPONSE, &next_token);
	int id = atoi(strtok_s(NULL, DELIM_RESPONSE, &next_token));
	return Create_lobby{ result_code, id };
}




Get_lobby get_lobby_data(char* payload) {
	Get_lobby result;
	char *next_token;

	// Get result code
	char* token = strtok_s(payload, DELIM_RESPONSE, &next_token);
	strcpy_s(result.result_code, CODE_SIZE + 1, token);
	int id;
	int team_number;
	char team_players[TEAM_PLAYER_NUM_STR];

	// Get list lobby 
	int i = 0;
	while (token) {
		// Get lobby id
		token = strtok_s(NULL, DELIM_RESPONSE, &next_token);
		id = atoi(token);

		// Get team number
		token = strtok_s(NULL, DELIM_RESPONSE, &next_token);
		team_number = atoi(token);

		// Get team player
		token = strtok_s(NULL, DELIM_RESPONSE, &next_token);
		strcpy_s(team_players, TEAM_PLAYER_NUM_STR, token);

		Lobby lobby{ id, team_number };
		resolve_team_player_str(team_players, lobby.team_number, lobby.team_players);
		result.lobbies[i] = lobby;

		i++;
	}

	return result;
}

Join_lobby join_lobby_data(char* payload) {
	Join_lobby result;
	char *next_token;

	//Get result code
	char* token = strtok_s(payload, DELIM_RESPONSE, &next_token);
	strcpy_s(result.result_code, CODE_SIZE + 1, token);

	// Get game id of this client
	token = strtok_s(NULL, DELIM_RESPONSE, &next_token);
	if (!token) {
		return result;
	}
	result.id = atoi(token);

	// Get team number
	token = strtok_s(NULL, DELIM_RESPONSE, &next_token);
	result.team_number = atoi(token);

	// Get team memeber string
	token = strtok_s(NULL, DELIM_RESPONSE, &next_token);
	int team_players[MAX_NUM_PLAYER];
	resolve_team_player_str(token, result.team_number, team_players);

	int player_ingame_id;
	char player_name[USERNAME_LEN];
	int player_state;
	int i = 0;

	// Get player detail info
	while (token) {
		token = strtok_s(NULL, DELIM_RESPONSE, &next_token);
		player_ingame_id = atoi(token);
		token = strtok_s(NULL, DELIM_RESPONSE, &next_token);
		strcpy_s(player_name, USERNAME_LEN, token);
		token = strtok_s(NULL, DELIM_RESPONSE, &next_token);
		player_state = atoi(token);
		result.players[i] = Player{ player_ingame_id, player_name, result.id, team_players[player_ingame_id], player_state };

		i++;
	}
	result.player_number = i;

	return result;
}


Change_team change_team_data(char* payload) {
	return Change_team(join_lobby_data(payload));
}

Ready ready_data(char* payload) {
	return Ready(join_lobby_data(payload));
}

Unready unready_data(char* payload) {
	return Unready(join_lobby_data(payload));
}

Quit_lobby quit_lobby_data(char* payload) {
	return Quit_lobby(join_lobby_data(payload));
}

Start_game start_game_data(char* payload) {
	char* next_token;
	// Get result code
	char result_code[CODE_SIZE + 1];
	char* token = strtok_s(payload, DELIM_RESPONSE, &next_token);
	strcpy_s(result_code, CODE_SIZE + 1, token);
	// Get game id
	token = strtok_s(NULL, DELIM_RESPONSE, &next_token);
	int game_id = atoi(token);
	return Start_game{ result_code, game_id };
}

void resolve_team_player_str(char* string, int team_number, int* member_team) {
	for (int i = 0; i < team_number * MAX_PLAYER_OF_TEAM; i++) {
		if (string[i] == 'x') {
			member_team[i] = -1;
		}
		else {
			member_team[i] = string[i] - '0';
		}
	}
}