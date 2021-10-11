#ifndef STACKPAGE_H
#define STACKPAGE_H

#include "tabpage.h"
#include <QWidget>
#include <QDebug>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextStream>
#include "scrollareacustom.h"
#include "qtransparentbutton.h"

class StackPage : public TabPage
{
    Q_OBJECT
public:
    StackPage(QWidget* parent = nullptr);

private:
    ScrollAreaCustom* numStackScrollArea;
    ScrollAreaCustom* opStackScrollArea;

    void paintEvent(QPaintEvent* event);

private slots:
    void RfrStack(const QString &, const QString &);
};

#endif // STACKPAGE_H
