#pragma once
#include "player.h"
#include "constant.h"
#include "castle.h"
#include "weapon.h"

class Team {
public:
	int id;
	int player_size;
	Player players[MAX_PLAYER_OF_TEAM];

	int castle_size;
	Castle castles[MAX_CASTLE_OF_GAME];
	Weapon	weapon;
	Wall wall;
	int	gold;
	int	wood;
	int	stone;
	int	iron;

	Team();
	Team(int id);
	Team(int id, Player* players, int player_size);
	void add_player(Player player);
	void add_castle(Castle castle);

};