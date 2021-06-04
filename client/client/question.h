#pragma once
#include "constant.h"

class Question {
public:
	int id;
	char question[QUESTION_LENGTH];
	char answer1[ANSWER_LENGTH];
	char answer2[ANSWER_LENGTH];
	char answer3[ANSWER_LENGTH];
	char answer4[ANSWER_LENGTH];
};