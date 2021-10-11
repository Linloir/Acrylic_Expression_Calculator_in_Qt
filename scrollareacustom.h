#ifndef SCROLLAREACUSTOM_H
#define SCROLLAREACUSTOM_H

#include <QWidget>
#include <QTimer>
#include <QVector>
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include "scrolllistcontainer.h"
#include "scrollindicator.h"
#include <QDebug>
#include <QQueue>

#define MAXSPEED 50

class ScrollAreaCustom : public QWidget
{
    Q_OBJECT

private:
    QTimer* getCord;
    QTimer* rfrshView;

    ScrollListContainer* container;
    ScrollIndicator* indicator;

    QPropertyAnimation* bounce;

    bool pressed = false;
    bool scrollDown = true;
    bool outOfEdge = false;

    int strtY;
    int lastY;
    int bfEdgeY;    //last y value before out of edge

    int curSpd = 0;
    int damp = 1;
    int moveStored = 0;
    int nextMove = 1;

    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);
    void bounceBack();


public:
    explicit ScrollAreaCustom(QWidget *parent = nullptr);
    void addWidget(QWidget* newWidget);
    void removeWidget(QWidget* w  = nullptr);
    void clear();

signals:

private slots:
    void scrollContainer();
    void updateSpd();
    void scrollIndicator(int dp);

};

#endif // SCROLLAREACUSTOM_H
