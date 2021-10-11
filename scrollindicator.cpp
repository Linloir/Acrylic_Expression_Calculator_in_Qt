#include "scrollindicator.h"

ScrollIndicator::ScrollIndicator(QWidget *parent) : QWidget(parent)
{
    this->resize(defaultWidth, 0);
    hovTimer = new QTimer(this);
    hovTimer->setSingleShot(true);
    aniPause = new QTimer(this);
    aniPause->setSingleShot(true);
    QObject::connect(hovTimer, SIGNAL(timeout()), this, SLOT(setHoverActive()));
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->curColor = defaultColor;

    this->setMouseTracking(true);
}

void ScrollIndicator::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(curColor);
    painter.drawRect(this->rect());
}

void ScrollIndicator::enterEvent(QEnterEvent *event){
    if(!pressed){
        hovTimer->start(100);
        curColor = hoverColor;
        update();
    }
}

void ScrollIndicator::leaveEvent(QEvent *event){
    //qDebug() << "leave";
    hovTimer->stop();
    curColor = defaultColor;
    QPropertyAnimation* narrow = new QPropertyAnimation(this, "geometry");
    narrow->setDuration(300);
    narrow->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
    narrow->setEndValue(QRect(this->parentWidget()->width() - margin - defaultWidth, this->y(), defaultWidth, this->height()));
    narrow->setEasingCurve(QEasingCurve::InOutQuad);
    narrow->start(QAbstractAnimation::DeleteWhenStopped);
    aniPause->start(300);
    update();
}

void ScrollIndicator::mousePressEvent(QMouseEvent *event){
    //qDebug() << "press\n";
    curColor = pressColor;
    pressed = true;
    lastY = event->globalPos().y();
    update();
}

void ScrollIndicator::mouseMoveEvent(QMouseEvent *event){
    if(pressed && !aniPause->isActive()){
        int dp = event->globalPos().y() - lastY;
        emit scrollPage(dp);
        lastY = event->globalPos().y();
    }
}

void ScrollIndicator::mouseReleaseEvent(QMouseEvent *event){
    pressed = false;
    curColor = hoverColor;
    update();
}

void ScrollIndicator::setHoverActive(){
    QPropertyAnimation* widen = new QPropertyAnimation(this, "geometry");
    widen->setDuration(300);
    widen->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
    widen->setEndValue(QRect(this->parentWidget()->width() - margin - defaultWidthAtFocus, this->y(), defaultWidthAtFocus, this->height()));
    widen->setEasingCurve(QEasingCurve::InOutQuad);
    widen->start(QAbstractAnimation::DeleteWhenStopped);
    aniPause->start(300);
}
