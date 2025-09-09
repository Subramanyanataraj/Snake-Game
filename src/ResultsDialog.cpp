#include "ResultsDialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

ResultsDialog::ResultsDialog(int score, int size, QWidget* parent)
: QDialog(parent) {
    setWindowTitle("Game Over");
    auto* layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel(QString("Score: %1").arg(score)));
    layout->addWidget(new QLabel(QString("Size: %1").arg(size)));
    auto* ok = new QPushButton("OK", this);
    layout->addWidget(ok);
    connect(ok, &QPushButton::clicked, this, &QDialog::accept);
    resize(1000, 500);
}
