#include "scrollareacustom.h"

ScrollAreaCustom::ScrollAreaCustom(QWidget *parent) : QWidget(parent)
{
    //initialize list container and timer
    container = new ScrollListContainer(this);
    container->move(0, 0);
    container->resize(this->width(), 3);
    //container->setMinimumWidth(this->width());
    //container->setMaximumWidth(this->width());
    getCord = new QTimer;
    getCord->setSingleShot(true);
    rfrshView = new QTimer;
    getCord->setSingleShot(true);

    indicator = new ScrollIndicator(this);
    indicator->resize(indicator->width(), (int)((double)this->height() * this->height() / (double)container->height()));
    indicator->move(this->width() - indicator->width() - 3, 0);

    this->setMouseTracking(true);
    container->setMouseTracking(true);
    indicator->setMouseTracking(true);

    bounce = new QPropertyAnimation(container, "pos");

    QObject::connect(getCord, SIGNAL(timeout()), this, SLOT(updateSpd()));
    QObject::connect(rfrshView, SIGNAL(timeout()), this, SLOT(scrollContainer()));
    QObject::connect(indicator, SIGNAL(scrollPage(int)), this, SLOT(scrollIndicator(int)));
}

void ScrollAreaCustom::paintEvent(QPaintEvent *event){
    //keep container the same size as parent widget
    //qDebug() << "scrollAreaWidth:[" << this->x() << "," << this->y() << "," << this->width() << "," << this->height() << "]\n";
    //qDebug() << "containerWidth:[" << container->x() << "," << container->y() << "," << container->width() << "," << container->height() << "]\n";
    //qDebug() << "speed:" << curSpd << "\n";
    //container->setMinimumWidth(this->width());
    //container->setMaximumWidth(this->width());
    container->resize(this->width(), container->height());
    if(container->height() > this->height() && container->y() < this->height() - container->height() && curSpd == 0 && bounce->state() == QAbstractAnimation::Stopped)
        container->move(container->x(), this->height() - container->height());
    if(container->height() <= this->height()){
        container->move(container->x(), 0);
        indicator->hide();
    }
    else{
        indicator->show();
    }
    indicator->resize(indicator->width(), (int)((double)this->height() * this->height() / (double)container->height()));
    indicator->move(this->width() - indicator->width() - 3, -container->y() * this->height() / container->height());
}

void ScrollAreaCustom::mousePressEvent(QMouseEvent *event){
    if(container->height() > this->height()){
        if(container->y() <= 0 && container->y() + container->height() >= this->height())
            pressed = true;
        lastY = event->pos().y();
    }
    getCord->stop();
    rfrshView->stop();
    curSpd = 0;
    outOfEdge = false;
    moveStored = 0;
    nextMove = 1;
}

void ScrollAreaCustom::mouseMoveEvent(QMouseEvent *event){
    setCursor(Qt::ArrowCursor);
    if(pressed){
        //qDebug() << "move\n";
        //start scroll
        if(!getCord->isActive() && event->pos().y() - lastY != 0){
            //start 30ms timer
            //qDebug() << "timer Start\n";
            getCord->start(30);
            strtY = event->pos().y();
        }
        if(container->y() <= 0 && container->y() + container->height() >= this->height()){
            //qDebug() << "in\n" ;
            container->move(container->x(), container->y() + event->pos().y() - lastY);
            //qDebug() << -container->y() * this->height() / container->height() << "\n";
        }
        else{
            //qDebug() << "outOfEdge\n";
            //qDebug() << event->pos().y() << "\n";
            //qDebug() << "nextMove:" << nextMove << "Stored: " << moveStored << "\n";
            if(!outOfEdge){
                bfEdgeY = event->pos().y();
                container->move(container->x(), container->y() + event->pos().y() - lastY);
                outOfEdge = true;
            }
            else{
                //qDebug() << "Damp\n" << "bfEdgeY: " << bfEdgeY << "\n";
                int pos = container->y() >= 0 ? 1 : -1;
                //qDebug() << "pos:" << pos << "\n";
                int dp = event->pos().y() - bfEdgeY;
                if(dp == 0){
                    outOfEdge = false;
                    nextMove = 1;
                    moveStored = 0;
                    if(container->y() >= 0)
                        container->move(container->x(), 0);
                    else
                        container->move(container->x(), this->height() - container->height());
                }
                else if(dp / abs(dp) != pos){
                    //qDebug() << "X";
                    outOfEdge = false;

                    container->move(container->x(), this->y() + event->pos().y() - bfEdgeY);
                    nextMove = 1;
                    moveStored = 0;
                }
                else{
                    while(abs(moveStored) + nextMove <= abs(event->pos().y() - bfEdgeY)){
                        //qDebug() << "add\n";
                        moveStored += nextMove * pos;
                        container->move(container->x(), container->y() + pos);
                        nextMove++;
                    }
                    while(nextMove > 1 && abs(moveStored) > abs(event->pos().y() - bfEdgeY)){
                        //qDebug() << "dec\n";
                        nextMove--;
                        moveStored -= nextMove * pos;
                        container->move(container->x(), container->y() - pos);
                    }
                    if(moveStored == 0){
                        outOfEdge = false;
                        if(container->y() >= 0)
                            container->move(container->x(), 0);
                        else
                            container->move(container->x(), this->height() - container->height());
                        nextMove = 1;
                        moveStored = 0;
                    }
                }
            }
        }
        lastY = event->pos().y();
    }
}

void ScrollAreaCustom::mouseReleaseEvent(QMouseEvent *event){
    //start scrolling
    //qDebug() << "mouseRelease\n";
    if(container->y() > 0 || container->y() + container->height() < this->height())
        bounceBack();
    else
        rfrshView->start(30);
    pressed = false;
}

void ScrollAreaCustom::bounceBack(){
    rfrshView->stop();
    getCord->stop();
    bounce->setDuration(500);
    bounce->setStartValue(container->pos());
    if(container->y() > 0)
        bounce->setEndValue(QPoint(container->x(), 0));
    else
        bounce->setEndValue(QPoint(container->x(), this->height() - container->height()));
    bounce->setEasingCurve(QEasingCurve::OutQuad);
    bounce->start();
}

void ScrollAreaCustom::scrollContainer(){
    //scroll
    if(curSpd > 0){
        if(curSpd > MAXSPEED)
            curSpd = MAXSPEED;
        int dp = scrollDown ? curSpd : -curSpd;
        container->move(container->x(), container->y() + dp);
    }
    else
        return;
    if(container->y() <= 0 && container->y() + container->height() >= this->height()){
        curSpd -= damp;
        curSpd = curSpd < 0 ? 0 : curSpd;
    }
    else
        curSpd /= 2;
    if(curSpd == 0 && (container->y() > 0 || container->y() + container->height() < this->height()))
        bounceBack();
    else
        rfrshView->start(30);

    //qDebug() << "spd2:" << curSpd << "\n";
}

void ScrollAreaCustom::updateSpd(){
    int spd = lastY - strtY;
    //qDebug() << "spd:" << spd << "\n";
    scrollDown = spd >= 0;
    strtY = lastY;
    curSpd = abs(spd);
}

void ScrollAreaCustom::addWidget(QWidget *newWidget){
    newWidget->setParent(container);
    container->AddWidget(newWidget);
}

void ScrollAreaCustom::removeWidget(QWidget *w){
    //container->layout()->removeWidget(w);

    //qDebug() << "good\n";
    container->RemoveWidget(w);
}

void ScrollAreaCustom::clear(){
    container->clear();
}

void ScrollAreaCustom::scrollIndicator(int dp){
    //qDebug() << "dp=" << dp << "\n";
    int newY = container->y() - dp * container->height() / this->height();
    if(newY > 0)
        newY = 0;
    else if(newY < this->height() - container->height())
        newY = this->height() - container->height();
    container->move(container->x(), newY);
    update();
}

void ScrollAreaCustom::wheelEvent(QWheelEvent *event){
    //qDebug() << "wheel" << event->angleDelta().y() * 100 / 360 << "\n";
    //int newY = container->y() + event->angleDelta().y() * 100 / 360 * container->height() / this->height();
    //if(newY > 0)
    //    newY = 0;
    //else if(newY < this->height() - container->height())
    //    newY = this->height() - container->height();
    //container->move(container->x(), newY);
    if(container->y() > 0 || container->y() + container->height() < this->height())
        return;
    curSpd += 5;
    bool newDirection = event->angleDelta().y() > 0;
    if(newDirection != scrollDown)
        curSpd = 5;
    if(curSpd > MAXSPEED)
        curSpd = MAXSPEED;
    scrollDown = newDirection;
    if(!rfrshView->isActive())
        rfrshView->start(30);
    update();
}
