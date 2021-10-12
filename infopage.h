#ifndef INFOPAGE_H
#define INFOPAGE_H

#include "tabpage.h"
#include "scrollareacustom.h"
#include <QVBoxLayout>
#include <QTextBrowser>
#include <QWidget>
#include <QDesktopServices>
#include <QFile>
#include <QApplication>
#include <QDir>

class InfoPage : public TabPage
{
    Q_OBJECT
public:
    InfoPage(QWidget* parent = nullptr);
};

#endif // INFOPAGE_H
