#include "tabindicator.h"

TabIndicator::TabIndicator(QWidget *parent) : QWidget(parent)
{
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    this->setMouseTracking(true);
}

void TabIndicator::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setPen(QColor(0, 120, 215, 200));
    painter.setBrush(QColor(0, 120, 215, 200));
    painter.drawRect(this->rect());
}
