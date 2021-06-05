#include "stdafx.h"
#include "lobby.h"
#include "response.h"
#include "util.h"

Lobby::Lobby() {
	printf("Chua co thong tin gi ca");
}

Lobby::Lobby(int id, int team_number) : id{ id }, team_number{team_number} {

}

Lobby::~Lobby() {

}

Lobby Lobby::create_lobby(Socket& socket, int team_number) {
	// Send create lobby request
	char teamnum_str[TEAM_NUMBER_SIZE ];
	_itoa_s(team_number, teamnum_str, TEAM_NUMBER_SIZE, 10);
	socket.tcp_send(CREATE_LOBBY, teamnum_str);

	//Receive lobby request
	char code[CODE_SIZE];
	char payload[PAYLOAD_SIZE];
	socket.tcp_receive(code, payload);

	if (!strcmp(code, CREATE_LOBBY)) {
		Create_lobby response = create_lobby_data(payload);
		if (response.request_code == OK) {
			return Lobby(response.id, team_number);
		}
	}
	return Lobby();

}


void Lobby::get_lobby(Socket& socket, Lobby lobbies[MAX_LOBBY]) {
	socket.tcp_send(GET_LOBBY, "");

	//Receive lobby request
	char code[CODE_SIZE];
	char payload[PAYLOAD_SIZE];
	socket.tcp_receive(code, payload);

	if (!strcmp(code, GET_LOBBY)) {
		Get_lobby respone = get_lobby_data();
	}

}

void Lobby::join_lobby(Socket& socket, char* id) {
	socket.tcp_send(CREATE_GAME, id);

	//Receive lobby request
	char code[CODE_SIZE];
	char payload[PAYLOAD_SIZE];
	socket.tcp_receive(code, payload);

	if (!strcmp(code, CREATE_GAME)) {
		Join_lobby response = join_lobby_data(payload);
		if (response.request_code == OK) {
			return Lobby(response.id, team_number);
		}
	}
	return Lobby();

}