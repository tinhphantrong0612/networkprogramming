#include "stdafx.h"
#include <stdlib.h>
#include <string.h>
#include "player.h"
#include "stream.h"
#include "util.h"

Player::Player() : id{ 0 }, team_id{ 0 }, state{ UNREADY } {
	strcpy_s(username, USERNAME_LEN, DEFAULT_USRNAME);

};


Player::Player(int id, char* username, int team_id, int state) : id{ id }, team_id{ team_id }, state{ state } {
	strcpy_s(this->username, USERNAME_LEN, username);
}

Player::~Player() {

}

void Player::ready_request(Socket& socket) {
	socket.tcp_send(READY_PLAY, "");
}

void Player::ready_response(char* payload) {
	Ready response = ready_data(payload);
	if (!strcmp(response.result_code, READY_SUCCESS)) {
		this->state = READY;
	}
	else if (!strcmp(response.result_code, READY_E_ALREADY)) {
		printf("You're already ready");		// This line replace by UI notification
	}
	else {
		printf("Invalid operation\n");		// This line replace by UI notification
	}

}

void Player::unready_request(Socket& socket) {
	socket.tcp_send(READY_PLAY, "");
}

void Player::unready_response(char* payload) {
	Player player;
	Unready response = unready_data(payload);
	if (!strcmp(response.result_code, UNREADY_SUCCESS)) {
		player.state = UNREADY;
	}
	else if (!strcmp(response.result_code, READY_E_ALREADY)) {
		printf("You're already ready");		// This line replace by UI notification
	}
	else {
		printf("Invalid operation\n");		// This line replace by UI notification
	}
}

void Player::change_team_request(Socket& socket, int team_id) {
	// Send team id
	char team_id_str[2];
	_itoa_s(team_id, team_id_str, 2, 10);
	socket.tcp_send(CHANGE_TEAM, team_id_str);
}

// Input param: payload, team_id
void Player::change_team_response(char* payload, int& team_id) {
	Player player;
	Change_team response = change_team_data(payload);
	if (!strcmp(response.result_code, JOIN_SUCCESS)) {
		player.team_id = team_id;
	}
	else if (!strcmp(response.result_code, CHANGE_E_CURRENTTEAM)) {
		printf("You're already at this team");		// This line replace by UI notification
	}
	else if (!strcmp(response.result_code, CHANGE_E_FULL)) {
		printf("The team you want to change is full");		// This line replace by UI notification
	}
	else if (!strcmp(response.result_code, CHANGE_E_READY)) {
		printf("You can't change team while you're ready");		// This line replace by UI notification
	}
	else if (!strcmp(response.result_code, CHANGE_E_UNKNOWNTEAM)) {
		printf("Invalid team");		// This line replace by UI notification
	}
	else {
		printf("Invalid operation\n");		// This line replace by UI notification
	}
}


void Player::attack_castle_request(Socket& socket, int castle_id, int question_id, int answer_id) {
	// Cast int to string
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


void Player::attack_mine_request(Socket& socket, int mine_id, int type, int question_id, int answer_id) {
	// Cast int to string
	char payload[PAYLOAD_SIZE + 1] = "";
	char mine_id_str[MINE_ID_SIZE + 1];
	char type_str[TYPE_SIZE + 1];
	char question_id_str[QUESTION_ID_SIZE + 1];
	char answer_id_str[ANSWER_ID_SIZE + 1];
	_itoa_s(mine_id, mine_id_str, MINE_ID_SIZE + 1, 10);
	_itoa_s(type, type_str, TYPE_SIZE + 1, 10);
	_itoa_s(question_id, question_id_str, QUESTION_ID_SIZE + 1, 10);
	_itoa_s(answer_id, answer_id_str, ANSWER_ID_SIZE + 1, 10);

	attack_mine_payload(mine_id_str, type_str, question_id_str, answer_id_str, payload);

	socket.tcp_send(ATTACK_MINE, payload);

}

void Player::buy_weapon_request(Socket& socket, int weapon_id) {
	char payload[PAYLOAD_SIZE + 1] = "";
	char weapon_id_str[WEAPON_ID_SIZE + 1];
	_itoa_s(weapon_id, weapon_id_str, WEAPON_ID_SIZE + 1, 10);
	strcpy_s(payload, PAYLOAD_SIZE + 1, weapon_id_str);
	socket.tcp_send(BUY_WEAPON, payload);
}

void Player::buy_wall_request(Socket& socket, int wall_id) {
	char payload[PAYLOAD_SIZE + 1] = "";
	char wall_id_str[WALL_ID_SIZE + 1];
	_itoa_s(wall_id, wall_id_str, WALL_ID_SIZE + 1, 10);
	strcpy_s(payload, PAYLOAD_SIZE + 1, wall_id_str);
	socket.tcp_send(BUY_WALL, payload);
}