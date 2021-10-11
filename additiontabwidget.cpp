#include "additiontabwidget.h"

AdditionTabWidget::AdditionTabWidget(QWidget *parent) : QWidget(parent)
{
    this->setMouseTracking(true);
    //this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    //initialize main layout
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(15);
    this->setLayout(mainLayout);

        //initialize tab bar
    //tabBar = new QWidget(this);
    //QVBoxLayout* tabBarVLayout = new QVBoxLayout;
    //tabBarVLayout->setContentsMargins(5, 5, 5, 5);
    //tabBar->setLayout(tabBarVLayout);
    iconContents = new QWidget(this);
    QHBoxLayout* iconHLayout = new QHBoxLayout;
    iconHLayout->setContentsMargins(0, 0, 0, 0);
    iconHLayout->setSpacing(0);
    iconHLayout->setAlignment(Qt::AlignLeft);
    iconContents->setLayout(iconHLayout);
    iconContents->setMouseTracking(true);
    //tabBarVLayout->addWidget(iconContents);

            //initialize indicator
    indicator = new TabIndicator(this);
    indicator->resize(0, 3);
    //indicator->move(-indicator->x(), iconContents->height() + 10);
    //tabBarVLayout->addWidget(indicator);

        //initialize page container
    pageContainer = new QWidget(this);
    //QGridLayout* pageLayout = new QGridLayout;
    //pageLayout->setContentsMargins(0, 0, 0, 0);
    //pageContainer->setLayout(pageLayout);
    pageContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    pageContainer->setMouseTracking(true);

    mainLayout->addWidget(iconContents);
    mainLayout->addWidget(pageContainer);

    /*********************************************************/

    /* Add your pages here
     * Remember to add icon in addition to pages
     *
     * Add a page like this:
     * ------------------------------------------------------------------
     * YourPage* newPage = new YourPage(pageContainer);
     * TabIcons* newPageLabel = new TabIcons("YourPageName", iconContents);
     * pages.push_back(newPage);
     * tabButtons.push_back(newPageLabel);
     *
     * QObject::connect() if you need
     * ------------------------------------------------------------------
     * And everything else just leave for the controller XD
     *
     */

    HistoryPage* historyPg = new HistoryPage(pageContainer);
    TabIcons* hisIcon = new TabIcons("History", iconContents);
    pages.push_back(historyPg);
    tabButtons.push_back(hisIcon);
    //iconHLayout->addWidget(hisIcon);
    //QObject::connect(hisIcon, SIGNAL(SelectPage(TabIcons*)), this, SLOT(ShiftPage(TabIcons*)));
    QObject::connect(this, SIGNAL(sig_AddHistory(const QString &, const QString &, const QString &)), historyPg, SLOT(AddHistory(const QString &, const QString &, const QString &)));

    StackPage* stackPg = new StackPage(pageContainer);
    TabIcons* stckIcon = new TabIcons("Stacks", iconContents);
    pages.push_back(stackPg);
    tabButtons.push_back(stckIcon);
     //iconHLayout->addWidget(stckIcon);
     //QObject::connect(stckIcon, SIGNAL(SelectPage(TabIcons*)), this, SLOT(ShiftPage(TabIcons*)));
    QObject::connect(this, SIGNAL(sig_UpdateStackPage(const QString &, const QString &)), stackPg, SLOT(RfrStack(const QString &, const QString &)));

    InfoPage* infoPg = new InfoPage(pageContainer);
    TabIcons* infoIcon = new TabIcons("About", iconContents);
    pages.push_back(infoPg);
    tabButtons.push_back(infoIcon);

    //StackPage* stackPg2 = new StackPage(pageContainer);
    //TabIcons* stckIcon2 = new TabIcons("Stack2", iconContents);
    //pages.push_back(stackPg2);
    //tabButtons.push_back(stckIcon2);

    /*********************************************************/

    //Initialize all pages
    for(int i = 0; i < pages.size(); i++){
        pages[i]->move(0, 0);
        pages[i]->resize(pageContainer->size());
        pages[i]->hide();
    }

    for(int i = 0; i < tabButtons.size(); i++){
        iconHLayout->addWidget(tabButtons[i]);
        QObject::connect(tabButtons[i], SIGNAL(SelectPage(TabIcons*)), this, SLOT(ShiftPage(TabIcons*)));
    }

    //Initialize default shown page and indicator
    pages[0]->show();
    tabButtons[0]->SetFocus(true);
    indicator->resize(tabButtons[0]->size().width() - 30, 3);
    indicator->move(15, iconContents->height() + 10);
    indicator->raise();
    currentPageIndex = 0;

}

void AdditionTabWidget::paintEvent(QPaintEvent *event){
    if(currentPageIndex != -1){
        //qDebug() << "resizing" << currentPageIndex << "\n";
        //qDebug() << "Page container:[" << pageContainer->x() << "," << pageContainer->y() << "," << pageContainer->width() << "," << pageContainer->height() << "]\n";
        //qDebug() << "this Page:[" << pages[currentPageIndex]->x() << "," << pages[currentPageIndex]->y() << "," << pages[currentPageIndex]->width() << "," << pages[currentPageIndex]->height() << "]\n";
        pages[currentPageIndex]->resize(pageContainer->size());
        //pages[currentPageIndex]->setMinimumWidth(pageContainer->width());
        //pages[currentPageIndex]->setMaximumSize(pageContainer->size());
    }

}

void AdditionTabWidget::ShiftPage(TabIcons* sel){
    //get index
    int index = tabButtons.indexOf(sel);
    if(index == currentPageIndex)
        return;

    //choose new page and Add to page container
    TabPage* newPage = pages[index];
    TabPage* curPage = pages[currentPageIndex];

    //prepare for animation
    QGraphicsOpacityEffect* newPageOpac = new QGraphicsOpacityEffect;
    QGraphicsOpacityEffect* curPageOpac = new QGraphicsOpacityEffect;
    newPageOpac->setOpacity(0);
    curPageOpac->setOpacity(1);
    newPage->setGraphicsEffect(newPageOpac);
    curPage->setGraphicsEffect(curPageOpac);
    newPage->show();
    newPage->raise();
    indicator->raise();
    QParallelAnimationGroup* switchPages = new QParallelAnimationGroup(pageContainer);
    QSequentialAnimationGroup* FadeIn = new QSequentialAnimationGroup(pageContainer);
    QPropertyAnimation* newPageFadeIn = new QPropertyAnimation(newPageOpac, "opacity", newPage);
    QPropertyAnimation* newPageMove = new QPropertyAnimation(newPage, "pos");
    QPropertyAnimation* curPageFadeOut = new QPropertyAnimation(curPageOpac, "opacity", curPage);
    QPropertyAnimation* curPageMove = new QPropertyAnimation(curPage, "pos");
    QPropertyAnimation* indicatorScale = new QPropertyAnimation(indicator, "geometry");
    if(currentPageIndex < index){
        //newPage->raise();
        newPageFadeIn->setDuration(600);
        newPageFadeIn->setStartValue(0);
        newPageFadeIn->setEndValue(1);
        newPageFadeIn->setEasingCurve(QEasingCurve::Linear);
        FadeIn->addPause(300);
        FadeIn->addAnimation(newPageFadeIn);
        newPageMove->setDuration(1200);
        newPageMove->setStartValue(QPoint(50, newPage->y()));
        newPageMove->setEndValue(QPoint(0, newPage->y()));
        newPageMove->setEasingCurve(QEasingCurve::InOutQuad);
        curPageFadeOut->setDuration(500);
        curPageFadeOut->setStartValue(1);
        curPageFadeOut->setEndValue(0);
        curPageFadeOut->setEasingCurve(QEasingCurve::Linear);
        curPageMove->setDuration(800);
        curPageMove->setStartValue(QPoint(0, curPage->y()));
        curPageMove->setEndValue(QPoint(-30, curPage->y()));
        curPageMove->setEasingCurve(QEasingCurve::InOutQuad);
        indicatorScale->setDuration(800);
        indicatorScale->setStartValue(QRect(indicator->x(), indicator->y(), indicator->width(), indicator->height()));
        indicatorScale->setEndValue(QRect(tabButtons[index]->x() + 15, indicator->y(), tabButtons[index]->size().width() - 30, indicator->height()));
        indicatorScale->setEasingCurve(QEasingCurve::InOutQuad);
    }
    else{
        //curPage->raise();
        newPageFadeIn->setDuration(600);
        newPageFadeIn->setStartValue(0);
        newPageFadeIn->setEndValue(1);
        newPageFadeIn->setEasingCurve(QEasingCurve::Linear);
        FadeIn->addPause(300);
        FadeIn->addAnimation(newPageFadeIn);
        newPageMove->setDuration(1200);
        newPageMove->setStartValue(QPoint(-50, newPage->y()));
        newPageMove->setEndValue(QPoint(0, newPage->y()));
        newPageMove->setEasingCurve(QEasingCurve::InOutQuad);
        curPageFadeOut->setDuration(500);
        curPageFadeOut->setStartValue(1);
        curPageFadeOut->setEndValue(0);
        curPageFadeOut->setEasingCurve(QEasingCurve::Linear);
        curPageMove->setDuration(800);
        curPageMove->setStartValue(QPoint(0, curPage->y()));
        curPageMove->setEndValue(QPoint(50, curPage->y()));
        curPageMove->setEasingCurve(QEasingCurve::InOutQuad);
        indicatorScale->setDuration(800);
        indicatorScale->setStartValue(QRect(indicator->x(), indicator->y(), indicator->width(), indicator->height()));
        indicatorScale->setEndValue(QRect(tabButtons[index]->x() + 15, indicator->y(), tabButtons[index]->size().width() - 30, indicator->height()));
        indicatorScale->setEasingCurve(QEasingCurve::InOutQuad);
    }
    switchPages->addAnimation(FadeIn);
    switchPages->addAnimation(newPageMove);
    switchPages->addAnimation(curPageFadeOut);
    switchPages->addAnimation(curPageMove);
    switchPages->addAnimation(indicatorScale);

    //start animation
    switchPages->start();
    connect(switchPages,&QPropertyAnimation::finished,[=](){newPageOpac->deleteLater();});
    //indicator->resize(tabButtons[index]->size().width() - 30, indicator->height());
    tabButtons[currentPageIndex]->SetFocus(false);
    currentPageIndex = index;
    tabButtons[index]->SetFocus(true);
    update();
}
