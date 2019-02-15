#include "showwidget.h"

ShowWidget::ShowWidget(QWidget *parent) : QSplitter(parent)
{
    /*上面widget----------------------------------------------------*/
    WidgetTop  = new QWidget(this);

    AddressNameLabel = new QLabel(tr("Address:"),          WidgetTop);
    AddressTextLabel = new QLabel(tr("0001:"),             WidgetTop);

    LengthNameLabel  = new QLabel(tr("Length:"),           WidgetTop);
    LengthTextLabel  = new QLabel(tr("100"),               WidgetTop);

    IdNameLabel      = new QLabel(tr("Device id:"),        WidgetTop);
    IdTextLabel      = new QLabel(tr("1"),                 WidgetTop);

    TypeNameLabel    = new QLabel(tr("ModBus Point Type"), WidgetTop);
    TypeComBox       = new QComboBox(WidgetTop);
    TypeComBox->addItem(tr("01:COIL    STATUS"));
    TypeComBox->addItem(tr("02:INPUT   STATUS"));
    TypeComBox->addItem(tr("03:HOLDING REGISTER"));
    TypeComBox->addItem(tr("04:INPUT   REGISTER"));

    ResetNameLabel  = new QLabel(tr("Number of Poll: 0\nVaild Slave Responses:0"), WidgetTop);
    ResetButton     = new QPushButton(tr("Reset Ctrs"), WidgetTop);

    WidgetGridLayout = new QGridLayout(WidgetTop);
    WidgetGridLayout->addWidget(AddressNameLabel, 0, 0);
    WidgetGridLayout->addWidget(AddressTextLabel, 0, 1);

    WidgetGridLayout->addWidget(LengthNameLabel, 1, 0);
    WidgetGridLayout->addWidget(LengthTextLabel, 1, 1);

    WidgetGridLayout->addWidget(IdNameLabel, 0, 2);
    WidgetGridLayout->addWidget(IdTextLabel, 0, 3);

    WidgetGridLayout->addWidget(TypeNameLabel, 1, 2);
    WidgetGridLayout->addWidget(TypeComBox, 1, 3);

    WidgetGridLayout->addWidget(ResetNameLabel, 0, 4);
    WidgetGridLayout->addWidget(ResetButton, 0, 5);

    WidgetTop->resize(1000, 140);

    this->addWidget(WidgetTop);





    /*下面textedit-------------------------------------------------*/
    TextBottom = new QTextEdit(this);

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
    this->resize(1000, 300);
    //设置方向
    this->setOrientation(Qt::Vertical);
    //设置宽度
    this->setHandleWidth(6);
    //设置背景色
    this->setStyleSheet("QSplitter::handle { background-color:rgb(215,215,215)}");
    //设置拉伸比例
    this->setStretchFactor(1, 1);
}
