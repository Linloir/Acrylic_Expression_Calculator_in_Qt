#include "scrolllistcontainer.h"

ScrollListContainer::ScrollListContainer(QWidget *parent) : QWidget(parent)
{
    //QVBoxLayout* mainLayout = new QVBoxLayout;
    //this->setLayout(mainLayout);
    //mainLayout->setContentsMargins(0, 0, 0, 0);
    //this->setLayout(nullptr);
    //newWidgetFade = new QTimer(this);
    //newWidgetFade->setSingleShot(true);
    //QObject::connect(newWidgetFade, SIGNAL(timsout()), this, SLOT(fadeIn()));
    //QWidget* nullWidget = new QWidget(this);
    //ys.push_back(1);
    //widgets.push_back(nullWidget);
    //nullWidget->resize(this->width(), 1);
}

void ScrollListContainer::paintEvent(QPaintEvent *event){
    for(int i = 0; i < widgets.size(); i++){
        widgets[i]->resize(this->width(), widgets[i]->height());
    }
}

void ScrollListContainer::AddWidget(QWidget *widget){
    //Add animation for all widgets current

    //qDebug() << "Adding2" << "\n";
    this->resize(this->width(), this->height() + widget->height() + spacing);
    //qDebug() << "containerHeight:" << this->height() << "\n";
    widgets.push_back(widget);
    size++;
    //qDebug() << "current widgets size (i): " << widgets.size() << "\n";
    ys.push_back(0);
    //qDebug() << "Widget wh" << widget->width() << "," << widget->height() << "\n";
    //qDebug() << "Widget xy" << widget->x() << "," << widget->y() << "\n";
    //widget->setParent(this);
    widget->resize(this->width(), widget->height());
    widget->show();
    QGraphicsOpacityEffect* widgetOpac = new QGraphicsOpacityEffect(widget);
    widgetOpac->setOpacity(0);
    widget->setGraphicsEffect(widgetOpac);
    //this->layout()->addWidget(widget);
    QParallelAnimationGroup* dpGroup = new QParallelAnimationGroup;
    QSequentialAnimationGroup* newWidgetFadeIn = new QSequentialAnimationGroup;
    //for(int i = 0; i < widgets.size() - 1; i++){
    for(int i = 0; i < size - 1; i++){
        ys[i] += widget->height() + spacing;
        QPropertyAnimation* move = new QPropertyAnimation(widgets[i], "pos");
        move->setDuration(750);
        move->setStartValue(widgets[i]->pos());
        move->setEndValue(QPoint(widgets[i]->x(), ys[i]));
        move->setEasingCurve(QEasingCurve::InOutQuart);
        dpGroup->addAnimation(move);
    }
    newWidgetFadeIn->addPause(300);
    QPropertyAnimation* fade = new QPropertyAnimation(widgetOpac, "opacity", widget);
    fade->setDuration(300);
    fade->setStartValue(0);
    fade->setEndValue(1);
    newWidgetFadeIn->addAnimation(fade);
    dpGroup->addAnimation(newWidgetFadeIn);
    dpGroup->start();
    connect(dpGroup, &QPropertyAnimation::stateChanged, [=](){
        if(dpGroup->state() == QAbstractAnimation::Stopped){
            if(widgetOpac->opacity() != 1){
                fade->start(QAbstractAnimation::DeleteWhenStopped);
                connect(fade,&QPropertyAnimation::finished,[=](){widgetOpac->deleteLater();});
                //qDebug() << "paused\n";
            }
            else{
                dpGroup->deleteLater();
                widgetOpac->deleteLater();
            }
        }
    });

}

void ScrollListContainer::RemoveWidget(QWidget *widget){
    int index;
    if(widget == nullptr){
        index = size - 1;
        if(index != -1)
            widget = widgets[index];
    }
    else
        index = widgets.indexOf(widget);
    if(index == -1 || widget == nullptr){
        //qDebug() << "returnning";
        return;
    }
    //qDebug() << "deleting index:" << index << "\n";
//    QGraphicsOpacityEffect* widgetOpac = new QGraphicsOpacityEffect(widget);
//    widgetOpac->setOpacity(1);
//    widget->setGraphicsEffect(widgetOpac);
    //this->layout()->addWidget(widget);
    this->resize(this->width(), this->height() - widget->height() - spacing);
    this->parentWidget()->update();
    widget->hide();
    widget->setParent(nullptr);
//    widget->deleteLater();
    QParallelAnimationGroup* dpGroup = new QParallelAnimationGroup;
//    QSequentialAnimationGroup* oldWidgetFadeOut = new QSequentialAnimationGroup;
    for(int i = index - 1; i >= 0; i--){
        //qDebug() << "adding Posani to index:" << i << "\n";
        ys[i] -= (widget->height() + spacing);
        QPropertyAnimation* move = new QPropertyAnimation(widgets[i], "pos");
        move->setDuration(750);
        move->setStartValue(widgets[i]->pos());
        move->setEndValue(QPoint(widgets[i]->x(), ys[i]));
        move->setEasingCurve(QEasingCurve::InOutQuart);
        dpGroup->addAnimation(move);
    }
//    oldWidgetFadeOut->addPause(300);
//    QPropertyAnimation* fade = new QPropertyAnimation(widgetOpac, "opacity", widget);
//    fade->setDuration(300);
//    fade->setStartValue(1);
//    fade->setEndValue(0);
//    oldWidgetFadeOut->addAnimation(fade);
//    dpGroup->addAnimation(oldWidgetFadeOut);
    dpGroup->start(QAbstractAnimation::DeleteWhenStopped);
    widgets.remove(index);
    size--;
//    qDebug() << "current widgets size (o): " << widgets.size() << "\n";
    ys.remove(index);
    //qDebug() << "[f]size: " << size << "\n";
//    connect(dpGroup, &QPropertyAnimation::stateChanged, [=](){
//        if(dpGroup->state() == QAbstractAnimation::Stopped){
//            if(widgetOpac->opacity() != 0){
//                fade->start(QAbstractAnimation::DeleteWhenStopped);
//                connect(fade,&QPropertyAnimation::finished,[=](){
//                    widgetOpac->deleteLater();
//                    dpGroup->deleteLater();
//                    widget->setParent(nullptr);
//                    widget->deleteLater();});
//                //qDebug() << "paused\n";
//            }
//            else{
//                dpGroup->deleteLater();
//                widgetOpac->deleteLater();
//                widget->setParent(nullptr);
//                widget->deleteLater();
//            }
//        }
//    });
}

void ScrollListContainer::clear(){
    //qDebug() << "size:" << size << "\n";
    int n = size;
    for(int i = 0; i < n; i++){
        //qDebug() << "[D]size:" << size << "\n";
        RemoveWidget();
    }
}
