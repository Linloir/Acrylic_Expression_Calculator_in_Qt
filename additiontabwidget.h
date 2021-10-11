/* A simple tab widget written by Jonathan Zhang
 * Github: haven't uploaded yet
 *
 * About this widget:
 * A simple controller for different pages
 * containing a tab bar to choose and a tiny indicator XD
 * ALSO HAS ANIMATIONS! yes!
 */

#ifndef ADDITIONTABWIDGET_H
#define ADDITIONTABWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPainter>
#include "tabicons.h"
#include "tabindicator.h"
#include "tabpage.h"
#include "historypage.h"
#include "stackpage.h"
#include "infopage.h"
#include <QVector>
#include <QPropertyAnimation>
#include <QPauseAnimation>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>
#include <QGraphicsOpacityEffect>

class AdditionTabWidget : public QWidget
{
    Q_OBJECT

private:
    QVBoxLayout* widgetLayout;
    //QWidget* tabBar;
    QWidget* iconContents;
    TabIndicator* indicator;
    QWidget* pageContainer;
    QVector<TabIcons*> tabButtons;
    QVector<TabPage*> pages;
    int currentPageIndex = -1;

    void paintEvent(QPaintEvent* event);

public:
    explicit AdditionTabWidget(QWidget *parent = nullptr);

signals:
    /* Add Signals for pages here
     * E.g.
     * void YourSignal();
     */
    void sig_AddHistory(const QString &, const QString &, const QString &);
    void sig_UpdateStackPage(const QString &, const QString &);

private slots:
    void ShiftPage(TabIcons* sel);

    /* Add Slots for pages here
     *
     * These slots are used for receiving msg from outside this controller
     * Remember to emit a signal from main dialog!
     *
     * REMEMBER TO CHECK THIS CONTROLLER'S PARENT IS SET TO YOUR SIGNAL WIDGET
     */
    void Controller_AddHistoryTerm(const QString & expStr, const QString & expStrHtml, const QString & resStrHtml){emit sig_AddHistory(expStr, expStrHtml, resStrHtml);}
    void Controller_UpdateStackPage(const QString & numDif, const QString & opDif){emit sig_UpdateStackPage(numDif, opDif);}
};

#endif // ADDITIONTABWIDGET_H
