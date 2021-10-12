#include "stackpage.h"

StackPage::StackPage(QWidget* parent) : TabPage(parent)
{
    this->setMouseTracking(true);
    //this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(mainLayout);

    QVBoxLayout* numLayout = new QVBoxLayout;
    numLayout->setContentsMargins(0, 0, 0, 0);
    QLabel* labNum = new QLabel;
    QFont labFont("DengXian", 13);
    labFont.setBold(true);
    labNum->setText("Num Stack");
    labNum->setFont(labFont);
    labNum->setAlignment(Qt::AlignRight | Qt::AlignTop);
    labNum->setStyleSheet("color:#E75E5E5E;");
    labNum->setMaximumHeight(20);
    numLayout->addWidget(labNum);

    numStackScrollArea = new ScrollAreaCustom(this);
    numLayout->addWidget(numStackScrollArea);

    QVBoxLayout* opLayout = new QVBoxLayout;
    opLayout->setContentsMargins(0, 0, 0, 0);
    QLabel* labOp = new QLabel;
    labFont.setBold(true);
    labOp->setText("Op Stack");
    labOp->setFont(labFont);
    labOp->setAlignment(Qt::AlignRight | Qt::AlignTop);
    labOp->setStyleSheet("color:#E75E5E5E;");
    labOp->setMaximumHeight(20);
    opLayout->addWidget(labOp);

    opStackScrollArea = new ScrollAreaCustom(this);
    opLayout->addWidget(opStackScrollArea);

    mainLayout->addLayout(opLayout);
    mainLayout->addLayout(numLayout);

    //qDebug() << "StackPageWidth:[" << this->x() << "," << this->y() << "," << this->width() << "," << this->height() << "]\n";
}

void StackPage::RfrStack(const QString & numDif, const QString & opDif){
    //qDebug() << "Rfr p1\n";
    QString numDifCpy = numDif;
    if(!numDif.isEmpty()){
        QTextStream numStream(&numDifCpy);
        if(numDif[0] == 'r'){
            numStackScrollArea->clear();
            numDifCpy.remove(0, 1);
        }
        while(!numStream.atEnd()){
            char op;
            numStream >> op;
            if(op == 'o'){
                numStackScrollArea->removeWidget();
            }
            else if(op == 'i'){
                double num;
                numStream >> num;
                QLabel* newNum = new QLabel;
                QFont font("DengXian", 20);
                font.setBold(true);
                newNum->setFont(font);
                newNum->setAlignment(Qt::AlignRight);
                newNum->resize(newNum->width(), 30);
                newNum->setText(QString::asprintf("%g", num));
                numStackScrollArea->addWidget(newNum);
            }
        }
    }
    QString opDifCpy = opDif;
    opDifCpy.replace('*', "×").replace('/', "÷");
    if(!opDif.isEmpty()){
        QTextStream opStream(&opDifCpy);
        if(opDif[0] == 'r'){
            opStackScrollArea->clear();
            opDifCpy.remove(0, 1);
        }
        while(!opStream.atEnd()){
            //qDebug() << "opStream" << "\n";
            char op;
            opStream >> op;
            //qDebug() << "op = " << op << "\n";
            if(op == 'o'){
                opStackScrollArea->removeWidget();
            }
            else if(op == 'i'){
                char c;
                opStream >> c;
                //qDebug() << c << "\n";
                QLabel* newChar = new QLabel;
                QFont font("DengXian", 20);
                font.setBold(false);
                newChar->setFont(font);
                newChar->setAlignment(Qt::AlignRight);
                newChar->resize(newChar->width(), 30);
                newChar->setText(QString::asprintf("%c%s", c, c == '(' ? " " : ""));
                opStackScrollArea->addWidget(newChar);
            }
        }
    }
}

void StackPage::paintEvent(QPaintEvent *event){
    //newScrollArea->setMinimumWidth(this->width());
    //newScrollArea->setMinimumHeight(this->height());
    //newScrollArea->resize(this->size());
}
