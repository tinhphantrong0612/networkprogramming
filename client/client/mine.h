#pragma once
#include "constant.h"

class Mine {
public:
	int id;
	int type;
	int amount;
	Mine();
	Mine(int id, int type, int amount);
};
