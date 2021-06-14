#pragma once
#include "constant.h"

#define NO_WALL_NAME "Naked castle"
#define FENCE_NAME "Fence Wall"
#define WOOD_WALL_NAME "Wood wall"
#define STONE_WALL_NAME "Stone Wall"
#define LEGEND_WALL_NAME "Legendary Wall"

class Wall {
public:
	int	defense;
	char name[NAME_LENGTH + 1];
	int	wood;
	int	stone;
	int	iron;

	Wall();
	Wall(int defense, char* name, int wood, int stone, int iron);
};

Wall get_wall(int type);