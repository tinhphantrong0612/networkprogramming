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
			return Wall(type, FENCE_DEF, FENCE_NAME, FENCE_WOOD, FENCE_STONE, FENCE_IRON);

		case WOOD_WALL:
			return Wall(type, WOOD_WALL_DEF, WOOD_WALL_NAME, WOOD_WALL_WOOD, WOOD_WALL_STONE, WOOD_WALL_IRON);

		case STONE_WALL:
			return Wall(type, STONE_WALL_DEF, STONE_WALL_NAME, STONE_WALL_WOOD, STONE_WALL_STONE, STONE_WALL_IRON);

		case LEGEND_WALL:
			return Wall(type, LEGEND_WALL_DEF, LEGEND_WALL_NAME, LEGEND_WALL_WOOD, LEGEND_WALL_STONE, LEGEND_WALL_IRON);
	}
}