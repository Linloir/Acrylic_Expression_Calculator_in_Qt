#include "acrylic.h"

#include <QApplication>

HashMap opMap;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Acrylic w;
    w.setWindowFlags(Qt::FramelessWindowHint);
    w.setAttribute(Qt::WA_TranslucentBackground);
    w.show();
    return a.exec();
}
