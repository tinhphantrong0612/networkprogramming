#include "stdafx.h"
#include "question.h"
#include "util.h"
#include "response.h"


Question::Question() {

}

Question::Question(int id, char* question, char* answer1, char* answer2, char* answer3, char* answer4): id{id}{
	strcpy_s(this->question, QUESTION_LENGTH + 1, question);
	strcpy_s(this->answer1, ANSWER_LENGTH + 1, answer1);
	strcpy_s(this->answer2, ANSWER_LENGTH + 1, answer2);
	strcpy_s(this->answer3, ANSWER_LENGTH + 1, answer3);
	strcpy_s(this->answer4, ANSWER_LENGTH + 1, answer4);
}

Question* Question::update_castle_question(char* payload) {
	Castle_question response = castle_question_data(payload);
	return response.questions;
}

Question* Question::update_mine_question(char* payload) {
	Mine_question response = mine_question_data(payload);
	return response.questions;
}
