#pragma once
#include <QDialog>

class QPushButton;

class MainMenuDialog : public QDialog {
    Q_OBJECT
public:
    enum Choice { StartNewGame=1, History=2, HighScores=3, Exit=4 };
    explicit MainMenuDialog(QWidget* parent=nullptr);
    Choice choice() const { return choice_; }
private slots:
    void onStart(); void onHistory(); void onHigh(); void onExit();
private:
    Choice choice_{Exit};
};
