#pragma once

#include "constant.h"
#include "wall.h"

class Castle {
public:
	int id;
	Wall wall;
	int occupied_by;

	Castle();
	Castle(int id);

};