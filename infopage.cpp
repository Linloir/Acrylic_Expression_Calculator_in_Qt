#include "infopage.h"

InfoPage::InfoPage(QWidget* parent) : TabPage(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(mainLayout);
    //mainLayout->setAlignment(Qt::AlignCenter);

    QFile htmlPage(":/html/info.html");
    QString html;
    if (htmlPage.open(QIODevice::ReadOnly | QIODevice::Text)){
        while (!htmlPage.atEnd()){
            QByteArray line = htmlPage.readLine();
            QString str(line);
            html.append(str);
        }
        htmlPage.close();
    }
    else{
        html.append("<h2>\
    <span style=\"font-size:14px;\"><strong><span style=\"font-size:16px;\">About This Application:</span></strong></span>\
</h2>\
<p>\
    <span style=\"font-size:14px;\"><strong>Author:</strong> <span style=\"color:#337FE5;\">Jonathan Zhang ( Linloir )</span></span> \
</p>\
<p>\
    <span style=\"font-size:14px;color:#000000;\"><span style=\"color:#000000;\"><strong>Version: </strong><span style=\"color:#337FE5;\">1.0</span></span></span>\
</p>\
<p>\
    <span><span style=\"font-size:14px;color:#000000;\"><strong>GitHub:&nbsp;</strong><span style=\"color:#337FE5;\"><a href=\"https://github.com/Linloir\" target=\"_blank\">https://github.com/Linloir</a></span></span></span>\
</p>\
<p>\
    <br />\
</p>");
    }

    QTextBrowser* InfoBrowser = new QTextBrowser;
    InfoBrowser->setHtml(html);
    InfoBrowser->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    InfoBrowser->setOpenExternalLinks(true);
    InfoBrowser->resize(InfoBrowser->width(), 800);
    //InfoBrowser->setAttribute(Qt::WA_TransparentForMouseEvents);

    ScrollAreaCustom* scrollarea = new ScrollAreaCustom(this);
    mainLayout->addWidget(scrollarea);
    scrollarea->addWidget(InfoBrowser);
}
