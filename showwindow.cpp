#include "showwindow.h"

ShowWindow::ShowWindow(QWidget *parent) : QMainWindow(parent)
{
    QFont Font;
    Font.setBold(true);
    Font.setFamily(QString::fromUtf8("Arial"));
    Font.setWeight(80);

    /*---------------------------------------创建分割器------------------------------------------*/
    MainSplitter = new QSplitter(this);
    //设置方向
    MainSplitter->setOrientation(Qt::Vertical);
    //设置宽度
    MainSplitter->setHandleWidth(6);
    //设置背景色
    MainSplitter->setStyleSheet("QSplitter::handle { background-color:rgb(215,215,215)}");
    //设置拉伸属性
    MainSplitter->setOpaqueResize(false);



    /*----------------------------------------参数配置界面---------------------------------------*/
    WidgetTop  = new QWidget(MainSplitter);

    AddressNameLabel = new QLabel(tr("Address:"),          WidgetTop);
    AddressTextEdit  = new QLineEdit(tr("0001"),           WidgetTop);
    AddressNameLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    AddressNameLabel->setGeometry(20, 20, 60, 22);
    AddressTextEdit->setGeometry(90, 20, 100, 22);
    AddressNameLabel->setFont(Font);
    AddressTextEdit->setFont(Font);

    LengthNameLabel  = new QLabel(tr("Length:"),           WidgetTop);
    LengthTextEdit   = new QLineEdit(tr("100"),            WidgetTop);
    LengthNameLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    LengthNameLabel->setGeometry(20, 60, 60, 22);
    LengthTextEdit->setGeometry(90, 60, 100, 22);
    LengthNameLabel->setFont(Font);
    LengthTextEdit->setFont(Font);

    IdNameLabel      = new QLabel(tr("Device id:"),        WidgetTop);
    IdTextEdit       = new QLineEdit(tr("1"),              WidgetTop);
    IdNameLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    IdNameLabel->setGeometry(200, 20, 120, 22);
    IdTextEdit->setGeometry(330, 20, 170, 22);
    IdNameLabel->setFont(Font);
    IdTextEdit->setFont(Font);

    TypeNameLabel    = new QLabel(tr("ModBus Point Type:"), WidgetTop);
    TypeComBox       = new QComboBox(WidgetTop);
    TypeNameLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    TypeNameLabel->setGeometry(200, 60, 120, 22);
    TypeComBox->setGeometry(330, 60, 170, 22);
    TypeNameLabel->setFont(Font);
    TypeComBox->setFont(Font);
    TypeComBox->addItem(tr("01:COIL    STATUS"));
    TypeComBox->addItem(tr("02:INPUT   STATUS"));
    TypeComBox->addItem(tr("03:HOLDING REGISTER"));
    TypeComBox->addItem(tr("04:INPUT   REGISTER"));

    NumPollNameLabel  = new QLabel(tr("Number of Poll:"),  WidgetTop);
    NumPollTextLabel  = new QLabel(tr("0"),                WidgetTop);
    NumPollNameLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    NumPollTextLabel->setFrameStyle(QFrame::Box | QFrame::Sunken);
    NumPollNameLabel->setGeometry(510, 20, 100, 22);
    NumPollTextLabel->setGeometry(620, 20, 100, 22);
    NumPollNameLabel->setFont(Font);
    NumPollTextLabel->setFont(Font);

    NumResponseNameLabel  = new QLabel(tr("Vaild Slave Responses:"), WidgetTop);
    NumResponseTextLabel  = new QLabel(tr("0"),                      WidgetTop);
    NumResponseNameLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    NumResponseTextLabel->setFrameStyle(QFrame::Box | QFrame::Sunken);
    NumResponseNameLabel->setGeometry(510, 60, 100, 22);
    NumResponseTextLabel->setGeometry(620, 60, 100, 22);
    NumResponseNameLabel->setFont(Font);
    NumResponseTextLabel->setFont(Font);

    ResetButton     = new QPushButton(tr("Reset Ctrs"),  WidgetTop);
    ResetButton->setGeometry(730, 60, 100, 22);
    ResetButton->setFont(Font);

    WidgetTop->resize(1000, 100);



    /*--------------------------------------数据显示界面------------------------------------*/
    TextBottom = new QTextEdit(MainSplitter);
    //设置背景色
    QPalette p = TextBottom->palette();
    p.setColor(QPalette::Base, QColor(200, 200, 200));
    TextBottom->setPalette(p);
    //设置属性
    //TextBottom->setReadOnly(true);
    TextBottom->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    TextBottom->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    TextBottom->setLineWrapMode(QTextEdit::NoWrap);
    //设置大小
    TextBottom->resize(1000, 200);
    //设置拉伸比例
    MainSplitter->setStretchFactor(1, 1);


    /*--------------------------------------设置分割器为主窗口----------------------------*/
    this->setCentralWidget(MainSplitter);
    this->resize(1000, 300);


    //显示数据
    ShowData(1, 100, 0, 0, false);
}



/*数据显示*/
void ShowWindow::ShowData(uint16_t addr, uint16_t length, uint8_t register_type, uint8_t data_format, bool connect_state)
{
    uint16_t        start_addr = 0, temp_addr = 0;
    uint16_t        i = 0, j = 0, temp_column = 0, temp_row = 0;
    QString         ConnectStateStr = "** Device NOT CONNECTED **\n";
    QString         temp_data_str   = "";
    QTextCharFormat Format;


    //TextEdit内容清空
    TextBottom->clear();


    //连接状态显示
    Format = TextBottom->currentCharFormat();
    Format.setFontPointSize(12);
    Format.setFontLetterSpacing(110);
    Format.setFontWeight(QFont::Bold);
    Format.setFontFamily(QString::fromUtf8("Arial"));
    Format.setForeground(QColor(255,0,0));
    TextBottom->mergeCurrentCharFormat(Format);
    if (!connect_state)
    {
       TextBottom->insertPlainText(ConnectStateStr);
//       QFontMetrics    FontMetrics(Format.font());
//       connect_str_height = FontMetrics.height();
    }



    //数据显示
    switch (register_type)
    {
        case COIL_STATUS:
            start_addr = 0+addr;
        break;

        case INPUT_STATUS:
            start_addr = 10000+addr;
        break;

        case HOLDING_REGISTER:
            start_addr = 40000+addr;
        break;

        case INPUT_REGISTER:
            start_addr = 30000+addr;
        break;
    }
    Format.setForeground(QColor(0,0,0));
    TextBottom->mergeCurrentCharFormat(Format);


    temp_row = TextBottom->geometry().height()/25;
    temp_column = length / temp_row;
    if (length % temp_row != 0)
    {
        temp_column++;
    }
    for (i=0; i<temp_row; i++)
    {
        temp_data_str = "";
        for (j=0; j<temp_column; j++)
        {
            temp_addr = start_addr + temp_row*j+i;
            if (temp_addr <= length)
            {
                temp_data_str += QString("%1").arg(temp_addr, 5, 10, QLatin1Char('0'));
                temp_data_str += tr(":  <");
                temp_data_str += QString("%1").arg(0, 1, 10, QLatin1Char('0'));
                temp_data_str += tr(">    ");
            }
        }
        TextBottom->insertPlainText(temp_data_str+"\n");
    }
}




/*虚函数重写*/
void ShowWindow::resizeEvent(QResizeEvent *event)
{


}
















