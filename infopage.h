#ifndef INFOPAGE_H
#define INFOPAGE_H

#include "tabpage.h"
#include <QVBoxLayout>
#include <QTextBrowser>
#include <QWidget>
#include <QDesktopServices>

class InfoPage : public TabPage
{
    Q_OBJECT
public:
    InfoPage(QWidget* parent = nullptr);
};

#endif // INFOPAGE_H
