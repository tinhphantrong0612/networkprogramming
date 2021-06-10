#include "stdafx.h"
#include "team.h"

Team::Team() {

}
Team::Team(int id) :id{ id } {

}

Team::Team(int id, Player* players, int player_size) : id{ id }, player_size{ player_size } {
	for (int i = 0; i < player_size; i++) {
		this->players[i] = players[i];
	}
}

void Team::add_player(Player player) {
	players[this->player_size] = player;
	this->player_size++;
}

void Team::add_castle(Castle castle) {
	castles[this->castle_size] = castle;
	this->castle_size++;
}