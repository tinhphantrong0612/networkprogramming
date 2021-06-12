#pragma once

#include "constant.h"
#include "wall.h"

class Castle {
public:
	int id;
	Wall wall;
	int team_id;
	int game_id;

	Castle();
	Castle(int id, int game_id);

};