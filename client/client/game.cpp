#include "stdafx.h"
#include "game.h"
#include "response.h"
#include "util.h"
#include <algorithm>

Game::Game(){

}


Game::Game(int id, int team_number, Player* players, int player_number){
	init_game(id, team_number, players, player_number);
}

void Game::init_game(int id, int team_number, Player* players, int player_number) {
	this->id = id;
	this->team_number = team_number;
	for (int i = 0; i < this->team_number; i++) {
		teams[i] = Team(i);
	}

	for (int i = 0; i < player_number; i++) {
		int team_id = players[i].team_id;
		teams[team_id].add_player(players[i]);
	}

	for (int i = 0; i < MAX_MINE_OF_GAME; i++) {
		int type = i / 2;
		mines[i] = Mine(i, type);
	}

	for (int i = 0; i < MAX_CASTLE_OF_GAME; i++) {
		castles[i] = Castle(i);
	}
}


void Game::update_timely_response(char* payload) {
	Update_timely response = update_timely_data(payload);
	for (int i = 0; i < MAX_CASTLE_OF_GAME; i++) {
		this->castles[i].occupied_by = response.occupied[i];
		this->castles[i].wall = get_wall(response.wall_type[i]);
		this->castles[i].wall.defense = response.wall_def[i];
	}

	for (int i = 0; i < MAX_MINE_OF_GAME; i++) {
		this->mines[i].wood = response.wood_mine[i];
		this->mines[i].stone = response.stone_mine[i];
		this->mines[i].iron = response.iron_mine[i];
	}

	for (int i = 0; i < team_number; i++) {
		this->teams[i].weapon = get_weapon(response.weapon_type[i]);
		this->teams[i].weapon.attack = response.weapon_atk[i];
		this->teams[i].gold = response.gold_team[i];
		this->teams[i].wood = response.wood_team[i];
		this->teams[i].stone = response.stone_team[i];
		this->teams[i].iron = response.iron_team[i];
	}
}

void Game::update_game_response(char* payload, Lobby& lobby) {
	Update_game response = update_game_data(payload);
	if (!strcmp(response.result_code, UPDATE_GAME_START)) {
		this->init_game(lobby.id, lobby.team_number, lobby.players, lobby.player_number);
		printf("Let's go baby");	// This line switch to game UI
	}
	else if (!strcmp(response.result_code, UPDATE_GAME_CSTQUEST)) {
		Update_castle_ques res = update_castle_ques_data(payload);
		this->castles[res.castle_id].question = Question(res.question_id, res.question, res.answer1, res.answer2, res.answer3, res.answer4);
	}
	else if (!strcmp(response.result_code, UPDATE_GAME_CSTQUEST)) {
		Update_mine_ques res = update_mine_ques_data(payload);
		this->mines[res.mine_id].question[res.type] = Question(res.question_id, res.question, res.answer1, res.answer2, res.answer3, res.answer4);
	}
	else if (!strcmp(response.result_code, UPDATE_GAME_ATK_CST_W) || !strcmp(response.result_code, UPDATE_GAME_ATK_CST_R)) {
		Update_castle_attack res = update_castle_attack_data(payload);
		int castle_id = res.castle_id;
		int player_id = res.player_id;
		int team_id = res.team_id;
		Castle& castle = this->castles[castle_id];
		Team& team = this->teams[team_id];
		if (!strcmp(response.result_code, UPDATE_GAME_ATK_CST_W)) {
			if (player_id != player.id) {
				printf("The player: %d of team %d has taken castle %d but fail\n",
					player_id, team_id, castle_id);	// This line replace by UI notification
				if (castle.wall.defense > res.wall_def && castle.occupied_by != 4) {
					printf("The weapon not strong enough");		// This line replace by UI notification
				}
			}
		}
		else {
			if (player_id != player.id) {
				printf("The player: %d of team %d has taken successfully castle %d\n",
					player_id, team_id, castle_id);	// This line replace by UI notification
			}
			castle.occupied_by = team_id;
		}
		castle.wall = get_wall(res.wall_type_id);
		castle.wall.defense = res.wall_def;

		team.add_castle(castle);
		team.weapon = get_weapon(res.weapon_type_id);
		team.weapon.attack = res.weapon_atk;

		castle.question = Question(res.question_id, res.question, res.answer1, res.answer2, res.answer3, res.answer4);
	}
	else if (!strcmp(response.result_code, UPDATE_GAME_ATK_MINE_W) || !strcmp(response.result_code, UPDATE_GAME_ATK_MINE_R)) {
		Update_mine_attack res = update_mine_attack_data(payload);
		int mine_id = res.mine_id;
		int player_id = res.player_id;
		int team_id = res.team_id;
		Mine& mine = this->mines[mine_id];
		Team& team = this->teams[team_id];
		if (!strcmp(response.result_code, UPDATE_GAME_ATK_MINE_R)) {
			printf("The player: %d of team %d has exploited successfully mine %d \n", player_id, team_id, mine_id);	// This line replace by UI notification
			switch (res.type) {
				case WOOD:
					team.wood += res.resource;
					break;
				case STONE:
					team.stone += res.resource;
					break;
				case IRON:
					team.iron += res.resource;
					break;
			}
		}

		mine.question[res.type] = Question(res.question_id, res.question, res.answer1, res.answer2, res.answer3, res.answer4);
	}
	else if (!strcmp(response.result_code, UPDATE_GAME_BUY_WPN)) {
		Update_buy_weapon res = update_buy_weapon_data(payload);
		if (player.id != res.player_id) {
			printf("Player %d of team %d has bought weapon %d", res.player_id, res.team_id, res.weapon_type_id);	// This line replace by UI notification
		}
		Team& team = this->teams[res.team_id];
		team.weapon = get_weapon(res.weapon_type_id);
		team.wood -= team.weapon.wood;
		team.stone -= team.weapon.stone;
		team.iron -= team.weapon.iron;
	}
	else if (!strcmp(response.result_code, UPDATE_GAME_BUY_WALL)) {
		Update_buy_wall res = update_buy_wall_data(payload);
		if (player.id != res.player_id) {
			printf("Player %d of team %d has bought wall %d", res.player_id, res.team_id, res.wall_type_id);	// This line replace by UI notification
		}

		Team& team = this->teams[res.team_id];
		Castle& castle = this->castles[res.castle_id];
		team.wall = get_wall(res.wall_type_id);
		castle.wall = get_wall(res.wall_type_id);
		team.wood -= team.wall.wood;
		team.stone -= team.wall.stone;
		team.iron -= team.wall.iron;
	}
	else if (!strcmp(response.result_code, UPDATE_GAME_CHEAT)) {
		Update_cheat res = update_cheat_data(payload);
		printf("Player % of team %d has cheated", res.request_player_id, res.team_id);	// This line replace by UI notification
	}
	else if (!strcmp(response.result_code, UPDATE_GAME_OVER)) {
		printf("It's over baby");	// Show end game UI
		std::sort(this->teams, this->teams + this->team_number, rank_sort);		// Rank each team, the first team is the best, last team is the worst
		// Switch to lobby view
	}

}