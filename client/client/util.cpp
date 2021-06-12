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

void auth_payload(char* username, char* password, char* payload) {
	strcat_s(payload, PAYLOAD_SIZE + 1, username);
	strcat_s(payload, PAYLOAD_SIZE + 1, DELIM_REQ_RES);
	strcat_s(payload, PAYLOAD_SIZE + 1, password);
}

void join_lobby_payload(char* game_id, char* team_id, char* payload) {
	strcat_s(payload, PAYLOAD_SIZE + 1, game_id);
	strcat_s(payload, PAYLOAD_SIZE + 1, DELIM_REQ_RES);
	strcat_s(payload, PAYLOAD_SIZE + 1, team_id);
}

void attack_castle_payload(char* castle_id, char* question_id, char* answer_id, char* payload) {
	strcat_s(payload, PAYLOAD_SIZE + 1, castle_id);
	strcat_s(payload, PAYLOAD_SIZE + 1, DELIM_REQ_RES);
	strcat_s(payload, PAYLOAD_SIZE + 1, question_id);
	strcat_s(payload, PAYLOAD_SIZE + 1, DELIM_REQ_RES);
	strcat_s(payload, PAYLOAD_SIZE + 1, answer_id);
}

void attack_mine_payload(char* mine_id, char* type, char* question_id, char* answer_id, char* payload) {
	strcat_s(payload, PAYLOAD_SIZE + 1, mine_id);
	strcat_s(payload, PAYLOAD_SIZE + 1, DELIM_REQ_RES);
	strcat_s(payload, PAYLOAD_SIZE + 1, type);
	strcat_s(payload, PAYLOAD_SIZE + 1, DELIM_REQ_RES);
	strcat_s(payload, PAYLOAD_SIZE + 1, question_id);
	strcat_s(payload, PAYLOAD_SIZE + 1, DELIM_REQ_RES);
	strcat_s(payload, PAYLOAD_SIZE + 1, answer_id);
}

Auth auth_data(char* payload) {
	Auth result;
	strcpy_s(result.result_code, RESULT_CODE_SIZE + 1, payload);
	return result;
}

Create_lobby create_lobby_data(char* payload) {
	Create_lobby result;
	char *next_token;
	char* token = strtok_s(payload, DELIM_REQ_RES, &next_token);
	strcpy_s(result.result_code, RESULT_CODE_SIZE + 1, token);
	result.id = atoi(strtok_s(NULL, DELIM_REQ_RES, &next_token));
	return result;
}

Get_lobby get_lobby_data(char* payload) {
	Get_lobby result;
	char *next_token;

	// Get result code
	char* token = strtok_s(payload, DELIM_REQ_RES, &next_token);
	strcpy_s(result.result_code, RESULT_CODE_SIZE + 1, token);
	int id;
	int team_number;
	char team_players[TEAM_PLAYER_NUM_STR];

	// Get list lobby 
	int i = 0;
	while (token) {
		// Get lobby id
		token = strtok_s(NULL, DELIM_REQ_RES, &next_token);
		id = atoi(token);

		// Get team number
		token = strtok_s(NULL, DELIM_REQ_RES, &next_token);
		team_number = atoi(token);

		// Get team player
		token = strtok_s(NULL, DELIM_REQ_RES, &next_token);
		strcpy_s(team_players, TEAM_PLAYER_NUM_STR, token);

		Lobby lobby{ id, team_number };
		resolve_team_player_str(team_players, lobby.team_number, lobby.team_players);
		result.lobbies[i] = lobby;

		i++;
	}
	result.size = i;

	return result;
}

Join_lobby join_lobby_data(char* payload) {
	Join_lobby result;
	char *next_token;

	//Get result code
	char* token = strtok_s(payload, DELIM_REQ_RES, &next_token);
	strcpy_s(result.result_code, RESULT_CODE_SIZE + 1, token);

	// Get game id of this client
	token = strtok_s(NULL, DELIM_REQ_RES, &next_token);
	result.id = atoi(token);

	// Get team number
	token = strtok_s(NULL, DELIM_REQ_RES, &next_token);
	result.team_number = atoi(token);

	// Get player id of this client
	token = strtok_s(NULL, DELIM_REQ_RES, &next_token);
	result.player_id = atoi(token);

	// Get team_id of the player
	token = strtok_s(NULL, DELIM_REQ_RES, &next_token);
	result.team_id = atoi(token);
		
	return result;
}


Change_team change_team_data(char* payload) {
	Change_team result;
	char *next_token;

	//Get result code
	char* token = strtok_s(payload, DELIM_REQ_RES, &next_token);
	strcpy_s(result.result_code, RESULT_CODE_SIZE + 1, token);
	return result;
}

Ready ready_data(char* payload) {
	Ready result;
	char *next_token;

	//Get result code
	char* token = strtok_s(payload, DELIM_REQ_RES, &next_token);
	strcpy_s(result.result_code, RESULT_CODE_SIZE + 1, token);
	return result;
}

Unready unready_data(char* payload) {
	Unready result;
	char *next_token;

	//Get result code
	char* token = strtok_s(payload, DELIM_REQ_RES, &next_token);
	strcpy_s(result.result_code, RESULT_CODE_SIZE + 1, token);
	return result;
}

Quit_lobby quit_lobby_data(char* payload) {
	Quit_lobby result;
	char *next_token;

	//Get result code
	char* token = strtok_s(payload, DELIM_REQ_RES, &next_token);
	strcpy_s(result.result_code, RESULT_CODE_SIZE + 1, token);
	return result;
}

Start_game start_game_data(char* payload) {
	Start_game result;
	char *next_token;

	//Get result code
	char* token = strtok_s(payload, DELIM_REQ_RES, &next_token);
	strcpy_s(result.result_code, RESULT_CODE_SIZE + 1, token);
	return result;
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


Update_lobby update_lobby_data(char* payload) {
	Update_lobby result;
	char* next_token;
	// Get result code
	char* token = strtok_s(payload, DELIM_REQ_RES, &next_token);
	strcpy_s(result.result_code, RESULT_CODE_SIZE + 1, token);

	// Get result code
	token = strtok_s(payload, DELIM_REQ_RES, &next_token);
	result.game_id = atoi(token);

	// Get team number
	token = strtok_s(NULL, DELIM_REQ_RES, &next_token);
	result.team_number = atoi(token);

	// Get request player id
	token = strtok_s(NULL, DELIM_REQ_RES, &next_token);
	result.request_player_id = atoi(token);

	// Get team player str
	token = strtok_s(NULL, DELIM_REQ_RES, &next_token);
	resolve_team_player_str(token, result.team_number, result.team_players);

	int player_ingame_id;
	char player_name[USERNAME_LEN];
	int player_state;
	int i = 0;

	// Get player detail info
	while (token) {
		token = strtok_s(NULL, DELIM_REQ_RES, &next_token);
		player_ingame_id = atoi(token);
		token = strtok_s(NULL, DELIM_REQ_RES, &next_token);
		strcpy_s(player_name, USERNAME_LEN, token);
		token = strtok_s(NULL, DELIM_REQ_RES, &next_token);
		player_state = atoi(token);
		result.players[i] = Player{ player_ingame_id, player_name, result.game_id, result.team_players[player_ingame_id], player_state };
		i++;
	}

	result.player_number = i;

	return result;
}


Update_timely update_timely_data(char* payload) {
	Update_timely result;
	char* next_token;
	char* token = strtok_s(payload, DELIM_REQ_RES, &next_token);

	// Get castle info
	for (int i = 0; i < MAX_CASTLE_OF_GAME; i++) {
		result.occupied[i] = atoi(token);
		token = strtok_s(NULL, DELIM_REQ_RES, &next_token);
		result.wall_type[i] = atoi(token);
		token = strtok_s(NULL, DELIM_REQ_RES, &next_token);
		result.wall_def[i] = atoi(token);
		token = strtok_s(NULL, DELIM_REQ_RES, &next_token);
	}

	// Get mine info
	for (int i = 0; i < MAX_MINE_OF_GAME; i++) {
		result.wood_mine[i] = atoi(token);
		token = strtok_s(NULL, DELIM_REQ_RES, &next_token);
		result.stone_mine[i] = atoi(token);
		token = strtok_s(NULL, DELIM_REQ_RES, &next_token);
		result.iron_mine[i] = atoi(token);
		token = strtok_s(NULL, DELIM_REQ_RES, &next_token);
	}

	// Get team info
	for (int i = 0; i < MAX_TEAM_OF_GAME; i++) {
		result.weapon_type[i] = atoi(token);
		token = strtok_s(NULL, DELIM_REQ_RES, &next_token);
		result.weapon_atk[i] = atoi(token);
		token = strtok_s(NULL, DELIM_REQ_RES, &next_token);
		result.gold_team[i] = atoi(token);
		token = strtok_s(NULL, DELIM_REQ_RES, &next_token);
		result.wood_team[i] = atoi(token);
		token = strtok_s(NULL, DELIM_REQ_RES, &next_token);
		result.stone_team[i] = atoi(token);
		token = strtok_s(NULL, DELIM_REQ_RES, &next_token);
		result.iron_team[i] = atoi(token);
		token = strtok_s(NULL, DELIM_REQ_RES, &next_token);
		if (!token)
			break;
	}

	return result;

}
