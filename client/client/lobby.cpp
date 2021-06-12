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
		printf("Max team number of a game is 4\n");	// This line replace by UI notification
	}
	else {
		printf("Invalid operation\n");	// This line replace by UI notification
	}
	return Player();
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
		printf("Invalid operation\n");	// This line replace by UI notification
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
	else if (!strcmp(response.result_code, JOIN_E_FORMAT)
		|| !strcmp(response.result_code, JOIN_E_NOGAME)
		|| !strcmp(response.result_code, JOIN_E_NOTEAM)) {
		printf("Wrong game id or team id\n");	// This line replace by UI notification
	}
	else if (!strcmp(response.result_code, JOIN_E_PLAYING) || !strcmp(response.result_code, JOIN_E_FULLTEAM)) {
		printf("This lobby is already full or ingame\n"); // This line replace by UI notification
	}
	else {
		printf("Invalid operation\n");	 // This line replace by UI notification
	}

	return Player();
}

void Lobby::start_game_request(Socket& socket) {
	socket.tcp_send(START_GAME, "");
}

Game Lobby::start_game_response(char* payload) {
	Start_game response = start_game_data(payload);

	if (!strcmp(response.result_code, START_SUCCESS)) {
		this->state = INGAME;
		printf("Gogogogogo");	// This line switch to game UI
		return Game(this->id, this->team_number, this->players, this->player_size);
	}
	else if (!strcmp(response.result_code, START_E_NOTHOST)) {
		printf("You are not the host");		// This line replace by UI notification
	}
	else {
		printf("Invalid operation\n");		// This line replace by UI notification
	}
	return Game();
}

void Lobby::quit_lobby_request(Socket& socket) {
	socket.tcp_send(QUIT_LOBBY, "");
}

void Lobby::quit_lobby_response(char* payload) {
	Quit_lobby response = quit_lobby_data(payload);
	if (!strcmp(response.result_code, QUIT_SUCCESS)) {
		printf("Quit success\n");	/// This line replace by UI notification and go to waiting room
	}
	else if (!strcmp(response.result_code, QUIT_E_READY)) {
		printf("All players are not ready");	// This line replace by UI notification
	}
	else {
		printf("Invalid operation\n");		// This line replace by UI notification
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

