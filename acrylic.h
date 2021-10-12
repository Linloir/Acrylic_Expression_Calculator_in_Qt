#ifndef ACRYLIC_H
#define ACRYLIC_H

#include <QDialog>
#include <QKeyEvent>
#include "WindowCompositionAttribute.h"
#include "additiontabwidget.h"
#include "ConvertFunc.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Acrylic; }
QT_END_NAMESPACE

class Acrylic : public QDialog
{
    Q_OBJECT

public:
    Acrylic(QWidget *parent = nullptr);
    ~Acrylic();

private:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void leaveEvent(QEvent *event){this->setCursor(Qt::ArrowCursor); pressed = false; mouseState = 0;}
    void keyPressEvent(QKeyEvent* event);
    //void keyReleaseEvent(QKeyEvent* event);

private:

    //Variables of Acrylic | aero window
    /****************************************************************************/

    HWND hwnd;
    HMODULE huser;
    pfnSetWindowCompositionAttribute setWindowCompositionAttribute;
    AdditionTabWidget* tabPage;

    Ui::Acrylic *ui;
    QPoint mousePos_strt;
    QColor acryBackground;
    int acryOpacity;

    int _width;
    int _height;

    bool isMaximum = false;
    int lastWidth;
    int lastHeight;

    bool pressed = false;
    bool tabShown = false;
    int mouseState = 0; //0 for move, 1 for width, 2 for height, 3 for width and height

    /****************************************************************************/

    //Variables and functions for the calculator
    /****************************************************************************/
    Expression expr;
    void RfrInput();
    void RfrResult();
    void UpdStack(bool r = false);
    void UpdHistory();

signals:
    void addHistoryTerm(const QString &, const QString &, const QString &);
    void updateStackPage(const QString &, const QString &);

private slots:
    void windowMaximum();
    //void windowMinimum();

};
#endif // ACRYLIC_H
