#pragma once
#include "constant.h"
#include "question.h"

class Mine {
public:
	int id;
	int type;
	int wood;
	int stone;
	int iron;
	Question question[TYPE_MINE_SIZE];

	Mine();
	Mine(int id, int type);
};
