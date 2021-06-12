#include "stdafx.h"
#include "wall.h"
#include "string.h"

Wall::Wall() {

}

Wall::Wall(int defense, char* name, int wood, int stone, int iron) : defense{ defense }, wood{ wood }, stone{ stone }, iron{ iron } {
	strcpy_s(this->name, USERNAME_LEN, name);
}

Wall get_wall(int type) {
	switch (type) {
		case FENCE:
			return Wall()
	}
}