#ifndef TABICONS_H
#define TABICONS_H

#include <QPushButton>
#include <QWidget>
#include <QPainter>
#include <QDebug>

class TabIcons : public QPushButton
{
    Q_OBJECT

private:
    bool atFocus = false;

    QColor currentColor;
    QColor defaultColorAtFocus = QColor(0, 0, 0, 255);
    QColor defaultColorNotAtFocus = QColor(100, 100, 100, 180);
    QColor hoverColor = QColor(50, 50, 50, 230);
    QColor pressColor = QColor(20, 20, 20, 230);

    void paintEvent(QPaintEvent* event);
    void enterEvent(QEnterEvent* event);
    void leaveEvent(QEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

public:
    TabIcons(QWidget* parent = nullptr);
    TabIcons(const QString & name, QWidget* parent = nullptr);
    void SetFocus(bool status);

signals:
    void SelectPage(TabIcons* icon);

private slots:
    void on_clicked(){emit SelectPage(this);}
};

#endif // TABICONS_H
