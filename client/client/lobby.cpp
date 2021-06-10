#include "stdafx.h"
#include "lobby.h"
#include "response.h"
#include "util.h"

Lobby::Lobby() {
	printf("Chua co thong tin gi ca");
}

Lobby::Lobby(int id, int team_number) : id{ id }, team_number{team_number} {

}

Lobby::Lobby(int id) : id{id} {

}

Lobby::~Lobby() {

}


void Lobby::create_lobby_request(Socket& socket, int team_number) {
	// Send create lobby request
	char teamnum_str[TEAM_NUMBER_SIZE ];
	_itoa_s(team_number, teamnum_str, TEAM_NUMBER_SIZE, 10);
	socket.tcp_send(CREATE_LOBBY, teamnum_str);

}


void Lobby::get_lobby_request(Socket& socket) {
	socket.tcp_send(GET_LOBBY, "");
}

void Lobby::join_lobby_request(Socket& socket, char* game_id, char* team_id, Player& player) {
	char mess[BUFF_SIZE] = "";
	join_lobby_payload(game_id, team_id, mess);
	socket.tcp_send(JOIN_LOBBY, mess);

}


void Lobby::create_lobby_response(char* payload) {
	Create_lobby response = create_lobby_data(payload);
	if (!strcmp(response.result_code, CREATE_SUCCESS)){
		this->id = response.id;
		this->team_number = team_number;
	}
}

Lobby* get_lobby_response(char* payload) {
	//Receive lobby request
	Get_lobby response = get_lobby_data(payload);
	if (!strcmp(response.result_code, LOBBY_SUCCESS)) {
		return response.lobbies;
	}
	return NULL;
}

Player Lobby::join_lobby_response(char* payload) {
	//Receive lobby request
	Player player;
	Join_lobby response = join_lobby_data(payload);
	if (strcmp(response.result_code, JOIN_SUCCESS)) {
		player.id = response.ingame_id;
		player.game_id = response.id;
		player.team_id = response.team_players[player.game_id];
		player.state = UNREADY;


		// Cần team number
		this->id = response.id;
		this->state = WAITING;
		for (int i = 0; i < response.player_number; i++) {
			this->players[i] = response.players[i];
		}
		for (int i = 0; i < team_number * MAX_PLAYER_OF_TEAM; i++) {
			this->team_players[i] = response.team_players[i];
		}

	}

	return player;

}