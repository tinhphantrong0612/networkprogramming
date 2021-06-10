#include "stdafx.h"
#include "response.h"

Change_team::Change_team(Join_lobby& data) {
	this ->id = data.id;
	this->ingame_id = data.ingame_id;
	this->player_number = data.player_number;
	strcpy_s(this->result_code, CODE_SIZE + 1, data.result_code);
	this->team_number = data.team_number;
	for (int i = 0; i < this->team_number * MAX_PLAYER_OF_TEAM; i++) {
		this->team_players[i] = data.team_players[i]; 
	}

	for (int i = 0; i < data.player_number; i++) {
		this->players[i] = data.players[i];
	}
}

Ready::Ready(Join_lobby& data) {
	this->id = data.id;
	this->ingame_id = data.ingame_id;
	this->player_number = data.player_number;
	strcpy_s(this->result_code, CODE_SIZE + 1, data.result_code);
	this->team_number = data.team_number;
	for (int i = 0; i < this->team_number * MAX_PLAYER_OF_TEAM; i++) {
		this->team_players[i] = data.team_players[i];
	}

	for (int i = 0; i < data.player_number; i++) {
		this->players[i] = data.players[i];
	}
}

Unready::Unready(Join_lobby& data) {
	this->id = data.id;
	this->ingame_id = data.ingame_id;
	this->player_number = data.player_number;
	strcpy_s(this->result_code, CODE_SIZE + 1, data.result_code);
	this->team_number = data.team_number;
	for (int i = 0; i < this->team_number * MAX_PLAYER_OF_TEAM; i++) {
		this->team_players[i] = data.team_players[i];
	}

	for (int i = 0; i < data.player_number; i++) {
		this->players[i] = data.players[i];
	}
}

Quit_lobby::Quit_lobby(Join_lobby& data) {
	this->id = data.id;
	this->ingame_id = data.ingame_id;
	this->player_number = data.player_number;
	strcpy_s(this->result_code, CODE_SIZE + 1, data.result_code);
	this->team_number = data.team_number;
	for (int i = 0; i < this->team_number * MAX_PLAYER_OF_TEAM; i++) {
		this->team_players[i] = data.team_players[i];
	}

	for (int i = 0; i < data.player_number; i++) {
		this->players[i] = data.players[i];
	}
}