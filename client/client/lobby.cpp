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
	char teamnum_str[TEAM_NUMBER_SIZE + 1];
	_itoa_s(team_number, teamnum_str, TEAM_NUMBER_SIZE + 1, 10);
	socket.tcp_send(CREATE_GAME, teamnum_str);

	//Receive lobby request
	char code[CODE_SIZE + 1];
	char payload[PAYLOAD_SIZE + 1];
	socket.tcp_receive(code, payload);

	if (!strcmp(code, CREATE_GAME)) {
		Create_lobby response = lobby_data(payload);
		if (response.request_code == OK) {
			return Lobby(response.id, team_number);
		}
	}
	return Lobby();

}

void Lobby::join_lobby(Socket& socket, char* id) {
	socket.tcp_send(CREATE_GAME, id);
}