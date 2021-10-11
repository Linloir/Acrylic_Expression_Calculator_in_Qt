#include "qtransparentbutton.h"

QTransparentButton::QTransparentButton(QWidget* parent) : QPushButton(parent)
{
    bgColor = bgColor_default;
    buttonText = this->text();
}

void QTransparentButton::paintEvent(QPaintEvent *event){
    QPainter bgPainter(this);
    bgPainter.setPen(Qt::NoPen);
    bgPainter.setBrush(bgColor);
    bgPainter.drawRect(this->rect());
    buttonText = this->text();


    //QPainter test(this);
    //test.setPen(Qt::SolidLine);
    //test.setBrush(Qt::NoBrush);

    QPainter textPainter(this);
    QFont textFont("FuturaNo2D", 14);
    textPainter.setFont(textFont);
    int widthOfText = textPainter.fontMetrics().size(Qt::TextSingleLine, buttonText).width();
    int heightOfText = textPainter.fontMetrics().ascent() - textPainter.fontMetrics().descent() + textPainter.fontMetrics().leading();
    //test.drawRect(this->width() / 2 - widthOfText / 2, this->height() / 2 - heightOfText / 2, widthOfText, heightOfText);
    textPainter.drawText(this->width() / 2 - widthOfText / 2, this->height() / 2 + heightOfText / 2, buttonText);
}

void QTransparentButton::enterEvent(QEnterEvent *event){
    bgColor = bgColor_Hover;
    update();
}

void QTransparentButton::leaveEvent(QEvent *event){
    bgColor = bgColor_default;
    update();
}

void QTransparentButton::mousePressEvent(QMouseEvent *event){
    emit clicked();
    bgColor = bgColor_Clicked;
    update();
}

void QTransparentButton::mouseReleaseEvent(QMouseEvent *event){
    bgColor = bgColor_Hover;
    update();
}

void QTransparentButton::setColor(QColor c){
    bgColor_default = c;
    bgColor = bgColor_default;
}

void QTransparentButton::setHoverColor(QColor c){
    bgColor_Hover = c;
}

void QTransparentButton::setClickedColor(QColor c){
    bgColor_Clicked = c;
}
