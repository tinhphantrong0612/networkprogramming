#pragma once

#include "constant.h"
#include "wall.h"
#include "question.h"

class Castle {
public:
    int id;
    Wall wall;
    int occupied_by;
    Question question;

    Castle();
    Castle(int id);
};
