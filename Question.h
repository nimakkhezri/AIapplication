#ifndef QUESTION_H
#define QUESTION_H

#include <iostream>
#include <vector>
#include "Category.h"

class Question {
private:
    std::string type, difficulty, question, correct_answer;
    std::vector <std::string> incorrect_answers;
    Category category;
public:
    Question(std::string type, const Category& category, std::string difficulty, std::string question, std::string correct_answer, std::vector<std::string> incorrect_answers) {
        this->type = type;
        this->category = category;
        this->difficulty = difficulty;
        this->question = question;
        this->correct_answer = correct_answer;
        this->incorrect_answers = incorrect_answers;
    }
    Question() {}

    std::string get_type() const;
    Category get_category() const;
    std::string get_difficulty() const;
    std::string get_question() const;
    std::string get_correct_answer() const;
    std::vector<std::string> get_incorrect_answers() const;

    void set_type(const std::string& type);
    void set_category(const Category& category);
    void set_difficulty(const std::string& difficulty);
    void set_question(const std::string& question);
    void set_correct_answer(const std::string& correct_answer);
    void set_incorrect_answers(const std::vector<std::string>& incorrect_answers);

};

#endif
