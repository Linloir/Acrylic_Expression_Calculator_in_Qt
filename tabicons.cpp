#include "tabicons.h"

TabIcons::TabIcons(QWidget* parent): QPushButton(parent)
{
    this->setMouseTracking(true);
    QFont textFont;
    textFont.setFamily("FuturaNo2DMed");
    textFont.setPointSize(15);
    QFontMetrics fm(textFont);
    this->setMinimumSize(fm.boundingRect(this->text()).width() + 30, fm.ascent() - fm.descent() + fm.leading() + 20);
    this->resize(fm.boundingRect(this->text()).width() + 30, fm.ascent() - fm.descent() + fm.leading());

    this->setStyleSheet("background-color = background-color: rgba(255, 255, 255, 0);");
    this->setFlat(true);

    currentColor = defaultColorNotAtFocus;

    //QObject::connect(this, SIGNAL(clicked()), this, SLOT(on_clicked()));
}

TabIcons::TabIcons(const QString & name, QWidget* parent) : QPushButton(parent){
    this->setMouseTracking(true);
    this->setText(name);
    QFont textFont;
    textFont.setFamily("FuturaNo2DMed");
    textFont.setPointSize(15);
    QFontMetrics fm(textFont);
    this->setMinimumSize(fm.boundingRect(this->text()).width() + 30, fm.ascent() - fm.descent() + fm.leading() + 20);
    this->resize(fm.boundingRect(this->text()).width() + 30, fm.ascent() - fm.descent() + fm.leading() + 20);

    this->setStyleSheet("background-color = background-color: rgba(255, 255, 255, 0);");
    this->setFlat(true);

    currentColor = defaultColorNotAtFocus;
    //qDebug() << "init" << this->width() << "\n";

    //QObject::connect(this, SIGNAL(clicked()), this, SLOT(on_clicked()));
}

void TabIcons::paintEvent(QPaintEvent *event){
    QPainter textPainter(this);
    textPainter.setPen(currentColor);
    QFont textFont("FuturaNo2DMed", 15);
    textPainter.setFont(textFont);
    int widthOfText = textPainter.fontMetrics().size(Qt::TextSingleLine, this->text()).width();
    //qDebug()<<"icon!";
    //int heightOfText = textPainter.fontMetrics().ascent() - textPainter.fontMetrics().descent() + textPainter.fontMetrics().leading();
    //test.drawRect(this->width() / 2 - widthOfText / 2, this->height() / 2 - heightOfText / 2, widthOfText, heightOfText);
    textPainter.drawText(this->width() / 2 - widthOfText / 2, this->height() - 5, this->text());
    //qDebug() << "paint" << this->width() << "\n";
}

void TabIcons::enterEvent(QEnterEvent *event){
    currentColor = hoverColor;
    update();
}

void TabIcons::leaveEvent(QEvent *event){
    currentColor = atFocus ? defaultColorAtFocus : defaultColorNotAtFocus;
    update();
}

void TabIcons::mousePressEvent(QMouseEvent *event){
    currentColor = pressColor;
    update();
    emit SelectPage(this);
}

void TabIcons::mouseReleaseEvent(QMouseEvent *event){
    currentColor = atFocus ? defaultColorAtFocus : hoverColor;
    update();
}

void TabIcons::SetFocus(bool status){
    atFocus = status;
    currentColor = atFocus ? defaultColorAtFocus : defaultColorNotAtFocus;
    update();
}
