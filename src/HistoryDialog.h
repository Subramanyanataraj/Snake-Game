
#pragma once
#include <QDialog>
#include <vector>
#include <QString>

class QTableWidget;

class HistoryDialog : public QDialog {
    Q_OBJECT
public:
    // topOnly=true => show top 10 scores; otherwise show full history
    explicit HistoryDialog(const QString& filePath, bool topOnly, QWidget* parent=nullptr);
private:
    struct Rec { QString name; int score; int size; QString dt; };
    static std::vector<Rec> readCsv(const QString& path);
    static std::vector<Rec> top10(std::vector<Rec> v);
    void populate(const std::vector<Rec>& recs);
    QTableWidget* table_{};
};
