#pragma once
#include "constant.h"

class Wall {
	int	defense;
	char name[NAME_LENGTH];
	int	wood;
	int	stone;
	int	iron;

	Wall();
	Wall(int defense, char* name, int wood, int stone, int iron);

	static Wall get_wall(int type);

};