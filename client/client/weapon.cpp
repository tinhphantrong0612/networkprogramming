#include "stdafx.h"
#include "weapon.h"
#include "string.h"

Weapon::Weapon(): Weapon(NO_WEAPON_ATK, NO_WEAPON_NAME, NO_WEAPON_WOOD, NO_WEAPON_STONE, NO_WEAPON_IRON) {

}

Weapon::Weapon(int attack, char* name, int wood, int stone, int iron) : attack{ attack }, wood{ wood }, stone{ stone }, iron{iron} {
	strcpy_s(this->name, NAME_LENGTH, name);
}

Weapon get_weapon(int type) {
	switch (type) {
		case BALLISTA:
			return Weapon(BALLISTA_ATK, BALISTA_NAME, BALLISTA_WOOD, BALLISTA_STONE, BALLISTA_IRON);
		case CATAPULT:
			return Weapon(CATAPULT_ATK, CATAPULT_NAME, CATAPULT_WOOD, CATAPULT_STONE, CATAPULT_IRON);
		case CANNON:
			return Weapon(CANNON_ATK, CANNON_NAME, CANNON_WOOD, CANNON_STONE, CANNON_IRON);
	}

	return Weapon();
}