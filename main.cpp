#include "acrylic.h"

#include <QApplication>

HashMap opMap;

int main(int argc, char *argv[])
{
    //QApplication::setQuitOnLastWindowClosed(true);
    QApplication a(argc, argv);
    Acrylic* w = new Acrylic;
    w->setWindowFlags(Qt::FramelessWindowHint);
    w->setAttribute(Qt::WA_TranslucentBackground);
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();
    return a.exec();
}
