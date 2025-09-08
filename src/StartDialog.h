#pragma once
#include <QDialog>
#include <QString>

class QLineEdit; class QComboBox; class QPushButton;

class StartDialog : public QDialog {
    Q_OBJECT
public:
    explicit StartDialog(QWidget* parent = nullptr);
    QString playerName() const;
    int difficulty() const; // 1=Easy, 2=Difficult
private slots:
    void onAccept();
private:
    QLineEdit* nameEdit_{};
    QComboBox* diffBox_{};
    QPushButton* startBtn_{};
};
