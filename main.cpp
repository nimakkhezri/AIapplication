#include <QApplication>
#include "TriviaAPI.h"
#include <vector>
#include <string>
#include <iostream>
#include <QMainWindow>
#include <QLabel>
#include <QRadioButton>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

using namespace std;

class TriviaWindow : public QMainWindow {
private:
    QLabel *questionLabel;
    vector<QRadioButton *> answerRadioButtons;
    QPushButton *nextButton;
    QPushButton *finishButton;
    int currentQuestionIndex;
    int score;

public:
    TriviaWindow() {
        // Initialize variables
        currentQuestionIndex = 0;
        score = 0;

        // Create main window layout
        QWidget *centralWidget = new QWidget;
        setCentralWidget(centralWidget);
        QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

        // Create question label
        questionLabel = new QLabel;
        questionLabel->setFont(QFont("Arial", 16));
        mainLayout->addWidget(questionLabel);

        // Create answer radio buttons
        answerRadioButtons.resize(4);
        for (int i = 0; i < 4; i++) {
            answerRadioButtons[i] = new QRadioButton;
            answerRadioButtons[i]->setFont(QFont("Arial", 12));
            mainLayout->addWidget(answerRadioButtons[i]);
        }

        // Create next button
        nextButton = new QPushButton("Next");
        connect(nextButton, &QPushButton::clicked, this, &TriviaWindow::nextQuestion);
        mainLayout->addWidget(nextButton);

        // Create finish button (initially disabled)
        finishButton = new QPushButton("Finish");
        finishButton->setDisabled(true);
        connect(finishButton, &QPushButton::clicked, this, &TriviaWindow::finishGame);
        mainLayout->addWidget(finishButton);
    }

    void showStartMenu() {
        // Create start menu layout
        QWidget *startMenuWidget = new QWidget;
        QVBoxLayout *startMenuLayout = new QVBoxLayout(startMenuWidget);

        // Create PVP button
        QPushButton *pvpButton = new QPushButton("PVP");
        connect(pvpButton, &QPushButton::clicked, this, &TriviaWindow::startPVP);
        startMenuLayout->addWidget(pvpButton);

        // Create Survival button (not implemented yet)
        QPushButton *survivalButton = new QPushButton("Survival (Coming Soon)");
        survivalButton->setDisabled(true);
        startMenuLayout->addWidget(survivalButton);

        // Set start menu widget as central widget
        setCentralWidget(startMenuWidget);
    }

    void startPVP() {
        // Fetch questions from TriviaAPI
        TriviaAPI api;
        std::vector<Question> questions = api.get_questions();

        // Display first question
        displayQuestion(questions[0]);

        // Enable next button
        nextButton->setEnabled(true);
    }

    void displayQuestion(const Question &question) {
        // Set question label text
        questionLabel->setText(question.get_question().c_str());

        // Set answer radio button texts and group answers
        for (int i = 0; i < 4; i++) {
            answerRadioButtons[i]->setText(question.get_incorrect_answers()[i].c_str());
            answerRadioButtons[i]->setGroup("answers");
        }

        // Uncheck all radio buttons
        for (QRadioButton *radioButton : answerRadioButtons) {
            radioButton->setChecked(false);
        }
    }

    void checkAnswer() {
        // Get selected answer
        int selectedAnswerIndex = -1;
        for (int i = 0; i < 4; i++) {
            if (answerRadioButtons[i]->isChecked()) {
                selectedAnswerIndex = i;
                break;
            }
        }

        // Check if selected answer is correct
        if (selectedAnswerIndex == -1) {
            // No answer selected
            return;
        }

        const Question &currentQuestion = questions[currentQuestionIndex];
        if (selectedAnswerIndex == currentQuestion.get_correct_answer_index()) {
            // Correct answer
            score++;
        }
    }

    void nextQuestion() {
        // Check answer
        checkAnswer();

        // Increment question index
        currentQuestionIndex++;

        // Check if all questions have been answered
        if (currentQuestionIndex >= questions.size()) {
            // Game over
            finishGame();
            return;
        }

        // Display next question
        displayQuestion(questions[currentQuestionIndex]);
    }

    void finishGame() {
        // Disable next button
        nextButton->setDisabled(true);

        // Enable finish button
        finishButton->setEnabled(true);

        // Show game over message
        QMessageBox::information(this, "Game Over",
                                 "You finished the game with a score of " + QString::number(score) + " out of 5!");
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    TriviaWindow window;
    window.showStartMenu();

    return app.exec();
}
