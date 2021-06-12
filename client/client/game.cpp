#include "stdafx.h"
#include "game.h"

Game::Game(){

}

Game::Game(int id, int team_number, Player* players, int player_number) : id{ id }, team_number{ team_number } {
	for (int i = 0; i < this->team_number; i++) {
		teams[i] = Team(i);
	}

	for (int i = 0; i < player_number; i++) {
		int team_id = players[i].team_id;
		teams[team_id].add_player(players[i]);
	}

	for (int i = 0; i < MAX_MINE_OF_GAME; i++) {
		int type = i / 2;
		mines[i] = Mine(i, this->id, type, 0);
	}

	for (int i = 0; i < MAX_CASTLE_OF_GAME; i++) {
		castles[i] = Castle(i, this->id);
	}
}
