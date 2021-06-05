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


Lobby Lobby::create_lobby(Socket& socket, int team_number) {
	// Send create lobby request
	char teamnum_str[TEAM_NUMBER_SIZE ];
	_itoa_s(team_number, teamnum_str, TEAM_NUMBER_SIZE, 10);
	socket.tcp_send(CREATE_LOBBY, teamnum_str);

	//Receive lobby request
	char code[CODE_SIZE + 1];
	char payload[PAYLOAD_SIZE + 1];
	socket.tcp_receive(code, payload);

	if (!strcmp(code, CREATE_LOBBY)) {
		Create_lobby response = create_lobby_data(payload);
		if (!strcmp(response.result_code, CREATE_SUCCESS)){
			return Lobby(response.id, team_number);
		}
	}
	return Lobby();

}


Lobby* Lobby::get_lobby(Socket& socket) {
	socket.tcp_send(GET_LOBBY, "");

	//Receive lobby request
	char code[CODE_SIZE + 1];
	char payload[PAYLOAD_SIZE + 1];
	socket.tcp_receive(code, payload);

	if (!strcmp(code, GET_LOBBY)) {
		Get_lobby response = get_lobby_data(payload);
		if (!strcmp(response.result_code, LOBBY_SUCCESS)) {
			return response.lobbies;
		}
	}
	return NULL;
}

Lobby Lobby::join_lobby(Socket& socket, char* game_id, char* team_id, Player& player) {
	char mess[BUFF_SIZE] = "";
	join_lobby_payload(game_id, team_id, mess);
	socket.tcp_send(JOIN_LOBBY, mess);

	//Receive lobby request
	char code[CODE_SIZE + 1];
	char payload[PAYLOAD_SIZE + 1];
	socket.tcp_receive(code, payload);

	if (!strcmp(code, JOIN_LOBBY)) {
		Join_lobby response = join_lobby_data(payload);
		if (strcmp(response.result_code, JOIN_SUCCESS)) {
			player.id = response.ingame_id;
			player.game_id = atoi(game_id);
			player.team_id = response.team_players[player.game_id];
			player.state = UNREADY;
			Lobby lobby = Lobby{ response.id };
			lobby.state = INGAME;
			// Cần team number
			return Lobby{};
		}
	}
	return Lobby{};
}
