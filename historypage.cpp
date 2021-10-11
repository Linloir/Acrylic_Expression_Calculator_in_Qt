#include "historypage.h"

HistoryPage::HistoryPage(QWidget* parent) : TabPage(parent)
{
    this->setMouseTracking(true);
    QVBoxLayout* pageLayout = new QVBoxLayout;
    pageLayout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(pageLayout);
    scrollArea = new ScrollAreaCustom(this);
    pageLayout->addWidget(scrollArea);
}

void HistoryPage::AddHistory(const QString & expStr, const QString & expStrHtml, const QString & resStrHtml){
    QWidget* newHistoryTerm = new QWidget(this);
    //newHistoryTerm->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
    QVBoxLayout* newLayout = new QVBoxLayout;
    newHistoryTerm->setLayout(newLayout);
    QLabel* expLabel = new QLabel(newHistoryTerm);
    expLabel->setTextFormat(Qt::RichText);
    expLabel->setAlignment(Qt::AlignRight | Qt::AlignBottom);
    expLabel->setFont(QFont("DengXian", 10));
    expLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
    QString expStrCpy = expStrHtml;
    expLabel->setText(expStrCpy.append('='));
    QLabel* resLabel = new QLabel(newHistoryTerm);
    //resLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    resLabel->setTextFormat(Qt::RichText);
    resLabel->setAlignment(Qt::AlignRight | Qt::AlignBottom);
    resLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
    QFont font("DengXian", 20);
    font.setBold(true);
    resLabel->setFont(font);
    resLabel->setText(resStrHtml);
    newHistoryTerm->resize(newHistoryTerm->width(), expLabel->height() + resLabel->height() + 20);
    newLayout->addWidget(expLabel);
    newLayout->addWidget(resLabel);
    scrollArea->addWidget(newHistoryTerm);
}
