#ifndef SCROLLLISTCONTAINER_H
#define SCROLLLISTCONTAINER_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>
#include <QGraphicsOpacityEffect>
#include <QVector>
#include <QTimer>

class ScrollListContainer : public QWidget
{
    Q_OBJECT
public:
    explicit ScrollListContainer(QWidget *parent = nullptr);
    void AddWidget(QWidget* widget);
    void RemoveWidget(QWidget* widget = nullptr);
    void clear();
    //void RemoveWidget(QWidget* widget);

private:
    //QTimer* newWidgetFade;
    int spacing = 3;
    QVector<QWidget*> widgets;
    int size = 0;
    QVector<int> ys;

    void paintEvent(QPaintEvent* event);

signals:

private slots:

};

#endif // SCROLLLISTCONTAINER_H
