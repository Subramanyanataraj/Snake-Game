#include "HistoryDialog.h"
#include <QTableWidget>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QFile>
#include <QTextStream>
#include <algorithm>

HistoryDialog::HistoryDialog(const QString& filePath, bool topOnly, QWidget* parent)
: QDialog(parent) {
    setWindowTitle(topOnly ? "Top 10 High Scores" : "Game History");
    auto recs = readCsv(filePath);
    if (topOnly) recs = top10(std::move(recs));

    auto* layout = new QVBoxLayout(this);
    table_ = new QTableWidget(this);
    table_->verticalHeader()->setVisible(false);       // hide row-number gutter
    table_->setCornerButtonEnabled(false);             // hide top-left corner square
    table_->horizontalHeader()->setStretchLastSection(true); // keep width clean

    if (topOnly) {
        table_->setColumnCount(4);
        table_->setHorizontalHeaderLabels(QStringList{"Rank","Name","Score","Date & Time"});
    } else {
        table_->setColumnCount(4);
        table_->setHorizontalHeaderLabels(QStringList{"Name","Score","Size","Date & Time"});
    }

    table_->horizontalHeader()->setStretchLastSection(true);
    layout->addWidget(table_);
    populate(recs);
    resize(1000, 500);
}


std::vector<HistoryDialog::Rec> HistoryDialog::readCsv(const QString& path){
    std::vector<Rec> out;
    QFile f(path);
    if(!f.open(QIODevice::ReadOnly|QIODevice::Text)) return out;
    QTextStream ts(&f);
    while(!ts.atEnd()){
        const auto line = ts.readLine();
        const auto parts = line.split(',');
        if (parts.size() < 4) continue;
        Rec r; r.name=parts[0]; r.score=parts[1].toInt(); r.size=parts[2].toInt(); r.dt=parts[3];
        out.push_back(r);
    }
    return out;
}
std::vector<HistoryDialog::Rec> HistoryDialog::top10(std::vector<Rec> v){
    std::sort(v.begin(), v.end(), [](const Rec& a, const Rec& b){ return a.score>b.score; });
    if (v.size()>10) v.resize(10);
    return v;
}
void HistoryDialog::populate(const std::vector<Rec>& recs) {
    bool topOnly = (table_->horizontalHeaderItem(0)->text() == "Rank");
    table_->setRowCount(static_cast<int>(recs.size()));
    for (int i = 0; i < (int)recs.size(); ++i) {
        int col = 0;
        if (topOnly) table_->setItem(i, col++, new QTableWidgetItem(QString::number(i+1)));
        table_->setItem(i, col++, new QTableWidgetItem(recs[i].name));
        table_->setItem(i, col++, new QTableWidgetItem(QString::number(recs[i].score)));
        if (!topOnly) table_->setItem(i, col++, new QTableWidgetItem(QString::number(recs[i].size)));
        table_->setItem(i, col++, new QTableWidgetItem(recs[i].dt));
    }
    table_->resizeColumnsToContents();
}
