#include "stdafx.h"
#include <stdlib.h>
#include <string.h>
#include "player.h"
#include "stream.h"
#include "util.h"

Player::Player() : id{ 0 }, team_id{ 0 }, state{ UNREADY } {
	strcpy_s(username, USERNAME_LEN, DEFAULT_USRNAME);

};


<<<<<<< HEAD
Player::Player(int id, char* username, int team_id, int state) : id{ id }, team_id{ team_id }, state{ state } {
=======
Player::Player(int id, char* username, unsigned long long game_id, int team_id, int state) : id{ id }, game_id{ game_id }, team_id{ team_id }, state{ state } {
>>>>>>> 9a6400dd80bd5ef61e072bc57dbee08e6c1349ab
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

void attack_castle_response(char* payload) {
	Attack_castle response = attack_castle_data(payload);
	if (!strcmp(response.result_code, ATK_CST_SUCCESS)) {
		printf("Now this castle is yours, congratulation");		// This line replace by UI notification
	}
	else if (!strcmp(response.result_code, ATK_CST_E_TOOLATE)) {
		printf("Your answer was too late");		// This line replace by UI notification
	}
	else if (!strcmp(response.result_code, ATK_CST_E_WRONG)) {
		printf("Your answer was wrong, now get the punishment, hahaha");	// This line replace by UI notification
	}
	else if (!strcmp(response.result_code, ATK_CST_E_TOOWEAK)) {
		printf("Enermy has a stronger wall, go farm and get a stronger weapon you fool");	// This line replace by UI notification
	}
	else {
		printf("Invalid operation\n");		// This line replace by UI notification
	}
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

void attack_mine_response(char* payload) {
	Attack_mine response = attack_mine_data(payload);
	if (!strcmp(response.result_code, ATK_MINE_SUCCESS)) {
		printf("Get your reward and go away");		// This line replace by UI notification
	}
	else if (!strcmp(response.result_code, ATK_MINE_E_TOOLATE)) {
		printf("This mine has been already taken by other team, answer the question faster idiot");		// This line replace by UI notification
	}
	else if (!strcmp(response.result_code, ATK_CST_E_WRONG)) {
		printf("Your answer was wrong, go with empty hand, hahaha");	// This line replace by UI notification
	}
	else {
		printf("Invalid operation\n");		// This line replace by UI notification
	}
}


void Player::buy_weapon_request(Socket& socket, int weapon_id) {
	char payload[PAYLOAD_SIZE + 1] = "";
	char weapon_id_str[WEAPON_ID_SIZE + 1];
	_itoa_s(weapon_id, weapon_id_str, WEAPON_ID_SIZE + 1, 10);
	strcpy_s(payload, PAYLOAD_SIZE + 1, weapon_id_str);
	socket.tcp_send(BUY_WEAPON, payload);
}

void Player::buy_weapon_response(char* payload) {
	Buy_weapon response = buy_weapon_data(payload);
	if (!strcmp(response.result_code, BUY_WEAPON_SUCCESS)) {
		printf("Now take the castle with this big boy");	// This line replace by UI notification
	}
	else if (!strcmp(response.result_code, BUY_WEAPON_E_NOTENOUGH)) {
		printf("Not enough resource to buy this weapon");	// This line replace by UI notification
	}
	else if (!strcmp(response.result_code, BUY_WEAPON_E_WEAKER)) {
		printf("You're already have a stronger weapon, use it");	// This line replace by UI notification
	}
	else {
		printf("Invalid operation\n");		// This line replace by UI notification
	}
}

void Player::buy_wall_request(Socket& socket, int wall_id) {
	char payload[PAYLOAD_SIZE + 1] = "";
	char wall_id_str[WALL_ID_SIZE + 1];
	_itoa_s(wall_id, wall_id_str, WALL_ID_SIZE + 1, 10);
	strcpy_s(payload, PAYLOAD_SIZE + 1, wall_id_str);
	socket.tcp_send(BUY_WALL, payload);
}

void Player::buy_wall_response(char* payload) {
	Buy_wall response = buy_wall_data(payload);
	if (!strcmp(response.result_code, BUY_WALL_SUCCESS)) {
		printf("All these enermyies will be afraid of this");	// This line replace by UI notification
	}
	else if (!strcmp(response.result_code, BUY_WALL_E_NOTENOUGH)) {
		printf("Not enough resource to buy this wall");	// This line replace by UI notification
	}
	else if (!strcmp(response.result_code, BUY_WALL_E_WEAKER)) {
		printf("You're already have a stronger wall, use it");	// This line replace by UI notification
	}
	else if (!strcmp(response.result_code, BUY_WALL_E_GONE)) {
		printf("Your team haven't occupied any castle");	// This line replace by UI notification
	}
	else {
		printf("Invalid operation\n");		// This line replace by UI notification
	}

}