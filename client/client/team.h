#pragma once
#include "player.h"
#include "constant.h"
#include "castle.h"
#include "weapon.h"

class Team {
	int id;
	Player players[MAX_PLAYER_OF_TEAM];
	Castle castles[MAX_CASTLE_OF_GAME];
	Weapon	weapon;
	Wall wall;
	int	gold;
	int	wood;
	int	stone;
	int	iron;
};