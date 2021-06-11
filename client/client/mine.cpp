#include "stdafx.h"
#include "mine.h"

Mine::Mine(): id{ 0 }, game_id{ 0 }, type{ WOOD }, amount{0} {

}

Mine::Mine(int id, int game_id, int type, int amount) : id{ id }, game_id{ game_id }, type{ type }, amount{ amount } {

}