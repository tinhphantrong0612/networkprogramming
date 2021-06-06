#include "stdafx.h"
#include <stdlib.h>
#include <string.h>
#include "player.h"
#include "stream.h"

Player::Player() {

};

Player::Player(char* username) {
	strcpy_s(this->username, USERNAME_LEN, username);
}

Player::Player(int id, char* username, int game_id, int team_id, int state) : id{ id }, game_id{game_id}, team_id{ team_id }, state{ state } {
	strcpy_s(this->username, USERNAME_LEN, username);
}

Player::~Player() {

}

void Player::change_team_request(Socket& socket, int team_id) {
	// Send team id
	char team_id_str[2];
	_itoa_s(team_id, team_id_str, 2, 10);
	socket.tcp_send(CHANGE_TEAM, team_id_str);
}

void Player::change_team_response(char* payload) {

}