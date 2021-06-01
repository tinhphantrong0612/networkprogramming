#include "stdafx.h"
#include "stream.h"

void create_lobby(Socket& socket, int team_number) {
	char teamnum_str[TEAM_NUMBER_SIZE + 1];
	_itoa_s(team_number, teamnum_str, TEAM_NUMBER_SIZE + 1, 10);
	socket.tcp_send(CREATE_LOBBY, 0, teamnum_str);
}

void join_lobby(Socket& socket, int id) {
	socket.tcp_send(JOIN_LOBBY, id, "");
}