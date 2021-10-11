#ifndef SCROLLCONTAINER_H
#define SCROLLCONTAINER_H

#include <QWidget>
#include <QDebug>
#include <QWheelEvent>

class ScrollContainer : public QWidget
{
    Q_OBJECT
public:
    explicit ScrollContainer(QWidget *parent = nullptr);
signals:

};

#endif // SCROLLCONTAINER_H
