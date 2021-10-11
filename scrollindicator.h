#ifndef SCROLLINDICATOR_H
#define SCROLLINDICATOR_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QTimer>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

class ScrollIndicator : public QWidget
{
    Q_OBJECT

private:
    QColor curColor;
    QColor defaultColor = QColor(100, 100, 100, 130);
    QColor hoverColor = QColor(70, 70, 70, 150);
    QColor pressColor = QColor(50, 50, 50, 170);

    QTimer* hovTimer;
    QTimer* aniPause;

    int lastY;

    int defaultWidth = 2;
    int defaultWidthAtFocus = 9;
    int margin = 3;

    bool pressed = false;

public:
    explicit ScrollIndicator(QWidget *parent = nullptr);

private:
    void paintEvent(QPaintEvent* event);
    void enterEvent(QEnterEvent* event);
    void leaveEvent(QEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

signals:
    void scrollPage(int);

private slots:
    void setHoverActive();

};

#endif // SCROLLINDICATOR_H
