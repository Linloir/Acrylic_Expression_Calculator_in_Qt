#ifndef HISTORYPAGE_H
#define HISTORYPAGE_H

#include "tabpage.h"
#include <QWidget>
#include <QDebug>
#include <QLabel>
#include <QVector2D>
#include <QVBoxLayout>
#include "scrollareacustom.h"

class HistoryPage : public TabPage
{
    Q_OBJECT

private:
    ScrollAreaCustom* scrollArea;

public:
    HistoryPage(QWidget* parent = nullptr);

private slots:
    void AddHistory(const QString & expStr, const QString & expStrHtml, const QString & resStrHtml);
};

#endif // HISTORYPAGE_H
