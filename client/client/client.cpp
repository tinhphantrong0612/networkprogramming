// client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stream.h"


void receive_data(Socket& socket);


int main(int argc, char* argv[])
{
	//Get port number and address
	int port_number = atoi(argv[2]);
	char* ip_address = argv[1];

	return 0;
}

void receive_data(Socket& socket) {
	//Receive response
	char code[CODE_SIZE + 1];
	char payload[PAYLOAD_SIZE + 1];
	socket.tcp_receive(code, payload);
	if (!strcmp(code, LOGIN)) {
		// User goi login_response
	}
	else if (!strcmp(code, SIGNUP)) {
		// User goi signup_response
	}
	else if (!strcmp(code, LOGOUT)) {
		// User goi logout_response
	}
	else if (!strcmp(code, CREATE_LOBBY)) {
		// Lobby goi create_lobby_response
		// Khi nhan tao phong
	}
	else if (!strcmp(code, GET_LOBBY)) {
		// Lobby goi get_lobby_response
		// Khi nhan tim phong 
	}
	else if (!strcmp(code, JOIN_LOBBY)) {
		// Lobby goi join_lobby_response
		// Hien thi thong tin phong choi
	}
	else if (!strcmp(code, CHANGE_TEAM)) {
		// Lobby goi change_team_response
	}
	else if (!strcmp(code, READY_PLAY)) {
		// Lobby goi ready_response
	}
	else if (!strcmp(code, UNREADY_PLAY)) {
		// Lobby goi unready_response
	}
	else if (!strcmp(code, QUIT_LOBBY)) {
		// Lobby goi quit_lobby_response
		// Thoat game vao man hinh chinh
	}
	else if (!strcmp(code, START_GAME)) {
		// Lobby goi start_game_response
		// Chuyen sang trang thai vao game
	}
	/**
	else if (!strcmp(code, UPDATE_CASTLE_QUESTION)) {
		// Question goi update_castle_question
	}
	else if (!strcmp(code, UPDATE_CASTLE_QUESTION)) {
		// Question goi update_mine_question
	}
	**/

}