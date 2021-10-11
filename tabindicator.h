#ifndef TABINDICATOR_H
#define TABINDICATOR_H

#include <QWidget>
#include <QPainter>

class TabIndicator : public QWidget
{
    Q_OBJECT

protected:
    void paintEvent(QPaintEvent* event);

public:
    explicit TabIndicator(QWidget *parent = nullptr);
};

#endif // TABINDICATOR_H
