#include "stdafx.h"
#include "mine.h"

Mine::Mine(): id{ 0 }, type{ WOOD }, amount{0} {

}

Mine::Mine(int id, int type, int amount) : id{ id }, type{ type }, amount{ amount } {

}