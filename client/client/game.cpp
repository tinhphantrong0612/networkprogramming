#include "stdafx.h"
#include "game.h"

Game::Game(){

}

Game::Game(Lobby& lobby) {
	this->id = lobby.id;
	this->state = INGAME;
	this->team_number = lobby.team_number;
	for (int i = 0; i < this->team_number; i++) {
		team[i] = Team(i);
	}
	for (int i = 0; i < lobby.player_size; i++) {
		int team_id = lobby.players[i].team_id;
		team[team_id].add_player(lobby.players[i]);
	}
}
