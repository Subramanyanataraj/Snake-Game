#include "StartDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>

StartDialog::StartDialog(QWidget* parent) : QDialog(parent) {
    setWindowTitle("Snake — Start");
    auto* layout = new QVBoxLayout(this);

    auto* nameRow = new QHBoxLayout();
    nameRow->addWidget(new QLabel("Player name:"));
    nameEdit_ = new QLineEdit(this);
    nameRow->addWidget(nameEdit_);
    layout->addLayout(nameRow);

    auto* diffRow = new QHBoxLayout();
    diffRow->addWidget(new QLabel("Difficulty:"));
    diffBox_ = new QComboBox(this);
    diffBox_->addItem("Easy", 1);
    diffBox_->addItem("Difficult", 2);
    diffRow->addWidget(diffBox_);
    layout->addLayout(diffRow);

    startBtn_ = new QPushButton("Start", this);
    layout->addWidget(startBtn_);
    connect(startBtn_, &QPushButton::clicked, this, &StartDialog::onAccept);

    resize(1000, 500);
}

QString StartDialog::playerName() const { return nameEdit_->text().trimmed(); }
int StartDialog::difficulty() const { return diffBox_->currentData().toInt(); }

void StartDialog::onAccept() {
    if (playerName().isEmpty()) { nameEdit_->setFocus(); return; }
    accept();
}
