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

