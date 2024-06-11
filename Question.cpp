#include "Question.h"


//getter funcs
std::string Question::get_type() const {
    return type;
}


Category Question::get_category() const {
    return category;
}

std::string Question::get_difficulty() const {
    return difficulty;
}

std::string Question::get_question() const {
    return question;
}

std::string Question::get_correct_answer() const {
    return correct_answer;
}

std::vector<std::string> Question::get_incorrect_answers() const {
    return incorrect_answers;
}


//setter funcs
void Question::set_type(const std::string& type) {
    this->type = type;
}

void Question::set_category(const Category& category) {
    this->category = category;
}

void Question::set_difficulty(const std::string& difficulty) {
    this->difficulty = difficulty;
}

void Question::set_question(const std::string& question) {
    this->question = question;
}

void Question::set_correct_answer(const std::string& correct_answer) {
    this->correct_answer = correct_answer;
}

void Question::set_incorrect_answers(const std::vector<std::string>& incorrect_answers) {
    this->incorrect_answers = incorrect_answers;
}
