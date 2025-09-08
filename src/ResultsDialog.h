#pragma once
#include <QDialog>

class QLabel; class QPushButton;

class ResultsDialog : public QDialog {
    Q_OBJECT
public:
    ResultsDialog(int score, int size, QWidget* parent = nullptr);
};
