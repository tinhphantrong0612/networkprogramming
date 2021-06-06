#pragma once

#include "team.h"
#include "mine.h"

class Game {
	int id;
	int start_at;
	int state;
	int team_number;
	Team team[MAX_TEAM_OF_GAME];
	Mine mines[MAX_MINE_OF_GAME];
	Castle castles[MAX_CASTLE_OF_GAME];
};