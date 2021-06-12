#pragma once
#include "constant.h"

#define NO_WEAPON_NAME "Egg fights rock"
#define BALISTA_NAME "Balista Sword"
#define CATAPULT_NAME "Big Catapult"
#define CANNON_NAME "Super Dupper Gaint Cannon"

class Weapon {
public:
	char name[NAME_LENGTH + 1];
	int	attack;
	int	wood;
	int	stone;
	int	iron;

	Weapon();
	Weapon(int attack, char* name, int wood, int stone, int iron);

};

Weapon get_weapon(int type);
