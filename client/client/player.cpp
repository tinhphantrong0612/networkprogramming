#include "stdafx.h"
#include <stdlib.h>
#include <string.h>
#include "player.h"
#include "stream.h"
#include "util.h"

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

void Player::attack_castle_request(Socket& socket, int castle_id, int question_id, int answer_id) {
	char payload[PAYLOAD_SIZE + 1] = "";
	char castle_id_str[CASTLE_ID_SIZE + 1];
	char question_id_str[QUESTION_ID_SIZE + 1];
	char answer_id_str[ANSWER_ID_SIZE + 1];
	_itoa_s(castle_id, castle_id_str, CASTLE_ID_SIZE + 1, 10);
	_itoa_s(question_id, question_id_str, QUESTION_ID_SIZE + 1, 10);
	_itoa_s(answer_id, answer_id_str, ANSWER_ID_SIZE + 1, 10);
	attack_castle_payload(castle_id_str, question_id_str, answer_id_str, payload);

	socket.tcp_send(ATTACK_CASTLE, payload);
	
}
