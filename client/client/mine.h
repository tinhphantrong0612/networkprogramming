#pragma once
#include "constant.h"

class Mine {
public:
	int id;
	int type;
	int wood;
	int stone;
	int iron;
	Mine();
	Mine(int id, int type);
};
