#ifndef QTRANSPARENTBUTTON_H
#define QTRANSPARENTBUTTON_H

#include <QPushButton>
#include <QObject>
#include <QString>
#include <QPainter>
#include <QMouseEvent>

class QTransparentButton : public QPushButton
{
    Q_OBJECT

protected:
    void paintEvent(QPaintEvent* event);
    void enterEvent(QEnterEvent *event);
    void leaveEvent(QEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

private:
    QString buttonText;
    QColor bgColor;
    QColor bgColor_default = QColor(255, 255, 255, 220);
    QColor bgColor_Hover = QColor(190, 190, 190, 70);
    QColor bgColor_Clicked = QColor(170, 170, 170, 70);

public:
    QTransparentButton(QWidget* parent = nullptr);
    void setColor(QColor c);
    void setClickedColor(QColor c);
    void setHoverColor(QColor c);
};

#endif // QTRANSPARENTBUTTON_H
