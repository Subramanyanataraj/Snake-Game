#include "MainMenuDialog.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

MainMenuDialog::MainMenuDialog(QWidget* parent): QDialog(parent) {
    setWindowTitle("Snake — Menu");
    auto* layout = new QVBoxLayout(this);
    // layout->addWidget(new QLabel("======= SNAKE GAME MENU ======="));
    auto* b1 = new QPushButton("1. Start New Game", this);
    auto* b2 = new QPushButton("2. Show Game History", this);
    auto* b3 = new QPushButton("3. View Top 10 High Scores", this);
    auto* b4 = new QPushButton("4. Exit", this);
    layout->addWidget(b1); layout->addWidget(b2); layout->addWidget(b3); layout->addWidget(b4);
    connect(b1,&QPushButton::clicked,this,&MainMenuDialog::onStart);
    connect(b2,&QPushButton::clicked,this,&MainMenuDialog::onHistory);
    connect(b3,&QPushButton::clicked,this,&MainMenuDialog::onHigh);
    connect(b4,&QPushButton::clicked,this,&MainMenuDialog::onExit);
    resize(1000, 520);
}
void MainMenuDialog::onStart(){ choice_=StartNewGame; accept(); }
void MainMenuDialog::onHistory(){ choice_=History; accept(); }
void MainMenuDialog::onHigh(){ choice_=HighScores; accept(); }
void MainMenuDialog::onExit(){ choice_=Exit; accept(); }
