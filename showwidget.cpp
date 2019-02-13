#include "showwidget.h"

ShowWidget::ShowWidget(QWidget *parent) : QSplitter(parent)
{
    /*上面widget----------------------------------------------------*/
    QWidget   *WidgetTop  = new QWidget(this);

    WidgetTop->resize(1000, 140);

    this->addWidget(WidgetTop);





    /*下面textedit-------------------------------------------------*/
    QTextEdit *TextBottom = new QTextEdit(this);

    //设置背景色
    QPalette p = TextBottom->palette();
    p.setColor(QPalette::Base, QColor(200, 200, 200));
    TextBottom->setPalette(p);

    //设置只读
    TextBottom->setReadOnly(true);

    //设置大小
    TextBottom->resize(1000, 160);

    this->addWidget(TextBottom);




    /*默认参数设置-------------------------------------------------*/
    this->setFixedSize(1000, 300);
    //设置方向
    this->setOrientation(Qt::Vertical);
    //设置宽度
    this->setHandleWidth(6);
    //设置背景色
    this->setStyleSheet("QSplitter::handle { background-color:rgb(215,215,215)}");
    //设置拉伸比例
    this->setStretchFactor(1, 1);
}
