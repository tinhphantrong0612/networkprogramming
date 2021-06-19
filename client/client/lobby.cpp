#include "stdafx.h"
#include "lobby.h"
#include "response.h"
#include "util.h"

Lobby::Lobby() :id{ 0 }, host{ 0 }, team_number{ 0 }, player_number{ 0 }, state{EMPTY} {
	for (int i = 0; i < MAX_NUM_PLAYER; i++) {
		team_players[i] = MAX_TEAM_OF_GAME;
	}
	for (int i = 0; i < MAX_NUM_PLAYER; i++) {
		players[i] = Player();
	}

}

Lobby::Lobby(unsigned long long id, int team_number, int state) : id{ id }, team_number{ team_number }, state{state} {
}

Lobby::Lobby(unsigned long long id) : id{ id } {

}

Lobby::~Lobby() {

}

// All request param is input

void Lobby::create_lobby_request(Socket& socket, int team_number) {
	// Send create lobby request
	char teamnum_str[TEAM_NUM_SIZE + 1];
	_itoa_s(team_number, teamnum_str, TEAM_NUM_SIZE + 1, 10);
	socket.tcp_send(CREATE_LOBBY, teamnum_str);
	this->team_number = team_number;
}


// Input param: payload, username
Player Lobby::create_lobby_response(char* payload, char* username) {
	Create_lobby response = create_lobby_data(payload);
	if (!strcmp(response.result_code, CREATE_SUCCESS)){
		this->id = response.id;
		this->host = 0;
		this->state = WAITING;
		this->player_number++;
		this->team_players[0] = 0;
		this->players[0] = Player(0, username, 0, UNREADY);
		return players[0];
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
	Get_lobby response = get_lobby_data(payload);	// Need state
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

void Lobby::join_lobby_request(Socket& socket, unsigned long long game_id, int team_id) {
	char game_id_str[GAME_ID_SIZE + 1];
	char team_id_str[TEAM_ID_SIZE + 1];
	_i64toa_s(game_id, game_id_str, GAME_ID_SIZE + 1, 10);
	_itoa_s(team_id, team_id_str, TEAM_ID_SIZE + 1, 10);

	char payload[PAYLOAD_SIZE + 1] = "";
	join_lobby_payload(game_id_str, team_id_str, payload);
	socket.tcp_send(JOIN_LOBBY, payload);

}

// Input param: payload, username, team_id and team_number from the lobby list
Player Lobby::join_lobby_response(char* payload, char* username, int& game_id, int& team_id, int& team_number) {
	//Receive lobby request
	Join_lobby response = join_lobby_data(payload);
	if (!strcmp(response.result_code, JOIN_SUCCESS)) {
		this->team_number = team_number;
		this->id = game_id;
		return Player(response.player_id, username, team_id, UNREADY);
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

void Lobby::start_game_response(char* payload) {
	Start_game response = start_game_data(payload);

	if (!strcmp(response.result_code, START_SUCCESS)) {
		this->state = INGAME;
		printf("Wating to create game"); // This line replace by UI notification
	}
	else if (!strcmp(response.result_code, START_E_NOTHOST)) {
		printf("You are not the host");		// This line replace by UI notification
	}
	else {
		printf("Invalid operation\n");		// This line replace by UI notification
	}
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

void Lobby::kick_request(Socket& socket, int player_id) {
	char payload[PAYLOAD_SIZE + 1] = "";
	char player_id_str[PLAYER_ID_SIZE + 1];
	_itoa_s(player_id, player_id_str, PLAYER_ID_SIZE + 1, 10);
	strcat_s(payload, PAYLOAD_SIZE, player_id_str);
	socket.tcp_send(KICK, payload);

}

void Lobby::kick_response(char* payload, int player_id) {
	Kick response = kick_data(payload);
	if (!strcmp(response.result_code, KICK_SUCCESS)) {
		if (this->host == player_id) {
			printf("Kick player successful"); // This line replace by UI notification
		}
	}
	else if (!strcmp(response.result_code, KICK_E_NOTHOST)) {
		printf("You're not host");	// This line replace by UI notification
	}
	else if (!strcmp(response.result_code, KICK_E_YOURSELF)) {
		printf("You can't kick yourself");	// This line replace by UI notification
	}
	else {
		printf("Invalid operation\n");		// This line replace by UI notification
	}
}


void Lobby::update_lobby_response(char* payload) {
	Update_lobby response = update_lobby_data(payload);
	this->team_number = response.team_number;
	this->player_number = response.player_number;
	this->host = response.host;

	for (int i = 0; i < response.player_number; i++) {
		this->players[i] = response.players[i];
	}

}

