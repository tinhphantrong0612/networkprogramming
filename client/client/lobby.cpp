#include "stdafx.h"
#include "lobby.h"
#include "response.h"
#include "util.h"

Lobby::Lobby() {

}

Lobby::Lobby(int id, int team_number) : id{ id }, team_number{team_number} {

}

Lobby::Lobby(int id) : id{id} {

}

Lobby::~Lobby() {

}

// All request param is input

void Lobby::create_lobby_request(Socket& socket, int team_number) {
	// Send create lobby request
	char teamnum_str[TEAM_NUM_SIZE + 1];
	_itoa_s(team_number, teamnum_str, TEAM_NUM_SIZE + 1, 10);
	socket.tcp_send(CREATE_LOBBY, teamnum_str);

}


// Input param: payload, username
Player Lobby::create_lobby_response(char* payload, char* username) {
	Create_lobby response = create_lobby_data(payload);
	if (!strcmp(response.result_code, CREATE_SUCCESS)){
		this->id = response.id;
		this->team_number = team_number;
		this->state = WAITING;
		return Player(0, username, this->id, 0, UNREADY);
	}
	else if (!strcmp(response.result_code, CREATE_E_INVALIDTEAM)) {
		printf("Max team number of a game is 4\n");	// Dòng này thay thế bằng thông báo UI
	}
	else {
		printf("Invalid operation\n");	// Dòng này thay thế bằng thông báo UI
	}
}


void Lobby::get_lobby_request(Socket& socket) {
	socket.tcp_send(GET_LOBBY, "");
}

// Input is payload
// Output is lobbies and size of the lobby
void Lobby::get_lobby_response(char* payload, Lobby* lobbies, int& size) {
	//Receive lobby request
	Get_lobby response = get_lobby_data(payload);
	if (!strcmp(response.result_code, LOBBY_SUCCESS)) {
		size = response.size;
		for (int i = 0; i < response.size; i++) {
			lobbies[i] = response.lobbies[i];
		}
	}
	else {
		printf("Invalid operation\n");	// Dòng này thay thế bằng thông báo UI
	}
}

void Lobby::join_lobby_request(Socket& socket, int game_id, int team_id) {
	char game_id_str[GAME_ID_SIZE + 1];
	char team_id_str[TEAM_ID_SIZE + 1];
	_itoa_s(game_id, game_id_str, GAME_ID_SIZE + 1, 10);
	_itoa_s(team_id, team_id_str, TEAM_ID_SIZE + 1, 10);

	char payload[PAYLOAD_SIZE + 1] = "";
	join_lobby_payload(game_id_str, team_id_str, payload);
	socket.tcp_send(JOIN_LOBBY, payload);

}

// Input param: payload, username
Player Lobby::join_lobby_response(char* payload, char* username) {
	//Receive lobby request
	Join_lobby response = join_lobby_data(payload);
	if (!strcmp(response.result_code, JOIN_SUCCESS)) {
		this->id = response.id;
		this->team_number = response.team_number;
		return Player(response.player_id, username, response.id, response.team_id, UNREADY);
	}
	else if (!strcmp(response.result_code, JOIN_E_PLAYING) || !strcmp(response.result_code, JOIN_E_FULLTEAM)) {
		printf("This lobby is already full or ingame\n"); // Dòng này thay thế bằng thông báo UI
	}
	return Player();

}

void Lobby::start_game_request(Socket& socket) {
	socket.tcp_send(START_GAME, "");
}

void Lobby::start_game_response(char* payload) {
	Start_game response = start_game_data(payload);

	if (!strcmp(response.result_code, START_SUCCESS)) {
		printf("Gogogogogo");	// Dòng này chuyển UI vào game
	}
}

void Lobby::quit_lobby_request(Socket& socket) {
	socket.tcp_send(QUIT_LOBBY, "");
}

void Lobby::quit_lobby_response(char* payload) {
	Quit_lobby response = quit_lobby_data(payload);
	if (!strcmp(response.result_code, QUIT_SUCCESS)) {
		printf("Quit success\n");	//Dòng này thay bằng thông báo UI chuyển sang phòng chờ
	}
}

void Lobby::update_lobby_response(char* payload) {
	Update_lobby response = update_lobby_data(payload);
	this->id = response.game_id; // Response chua co game_id
	this->team_number = response.team_number;
	this->player_size = response.player_number;
	if (!strcmp(response.result_code, UPDATE_LOBBY_JOIN)) {
		this->state = WAITING;
		// Update team and player
		for (int i = 0; i < response.player_number; i++) {
			this->players[i] = response.players[i];
		}
		for (int i = 0; i < team_number * MAX_PLAYER_OF_TEAM; i++) {
			this->team_players[i] = response.team_players[i];
		}
	}
	else if (!strcmp(response.result_code, UPDATE_LOBBY_QUIT)) {
		// Update team and player
		for (int i = 0; i < response.player_number; i++) {
			this->players[i] = response.players[i];
		}
		for (int i = 0; i < team_number * MAX_PLAYER_OF_TEAM; i++) {
			this->team_players[i] = response.team_players[i];
		}
	}
	else if (!strcmp(response.result_code, UPDATE_LOBBY_READY)) {
		// Update player
		for (int i = 0; i < response.player_number; i++) {
			this->players[i] = response.players[i];
		}
	}
	else if (!strcmp(response.result_code, UPDATE_LOBBY_UNREADY)) {
		// Update player
		for (int i = 0; i < response.player_number; i++) {
			this->players[i] = response.players[i];
		}
	}
	else if (!strcmp(response.result_code, UPDATE_LOBBY_CHANGETEAM)) {
		// Update team and player
		for (int i = 0; i < response.player_number; i++) {
			this->players[i] = response.players[i];
		}
		for (int i = 0; i < team_number * MAX_PLAYER_OF_TEAM; i++) {
			this->team_players[i] = response.team_players[i];
		}
	}

}

