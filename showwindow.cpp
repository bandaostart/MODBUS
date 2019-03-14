#include "showwindow.h"

ShowWindow::ShowWindow(QWidget *parent) : QMainWindow(parent)
{
    Creat_ParaArea();

    Creat_ShowArea();

    Creat_MainArea();
}



/*创建参数配置区域------------------------------------------------------------------------------*/
void ShowWindow::Creat_ParaArea(void)
{
    QFont Font;
    Font.setBold(true);
    Font.setFamily(QString::fromUtf8("Arial"));
    Font.setWeight(80);

    validator_address  = new QIntValidator(1, 65534, this);
    validator_length   = new QIntValidator(1, 128, this);
    validator_modbusid = new QIntValidator(0, 255, this);

    WidgetTop  = new QWidget(this);

    AddressNameLabel = new QLabel(tr("Address:"),          WidgetTop);
    AddressTextEdit  = new QLineEdit(tr("0001"),           WidgetTop);
    AddressTextEdit->setValidator(validator_address);
    AddressTextEdit->setMaxLength(5);

    AddressNameLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    AddressNameLabel->setGeometry(20, 20, 60, 22);
    AddressTextEdit->setGeometry(90, 20, 100, 22);
    AddressNameLabel->setFont(Font);
    AddressTextEdit->setFont(Font);




    LengthNameLabel  = new QLabel(tr("Length:"),           WidgetTop);
    LengthTextEdit   = new QLineEdit(tr("100"),            WidgetTop);
    LengthTextEdit->setValidator(validator_length);
    LengthTextEdit->setMaxLength(3);

    LengthNameLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    LengthNameLabel->setGeometry(20, 60, 60, 22);
    LengthTextEdit->setGeometry(90, 60, 100, 22);
    LengthNameLabel->setFont(Font);
    LengthTextEdit->setFont(Font);





    IdNameLabel      = new QLabel(tr("Device id:"),        WidgetTop);
    IdTextEdit       = new QLineEdit(tr("1"),              WidgetTop);
    IdTextEdit->setValidator(validator_modbusid);
    IdTextEdit->setMaxLength(3);

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



    connect(this->AddressTextEdit, SIGNAL(textChanged(QString)), this, SLOT(Reg_AddressChange(QString)));
    connect(this->LengthTextEdit,  SIGNAL(textChanged(QString)), this, SLOT(Reg_LengthChange(QString)));
    connect(this->TypeComBox,      SIGNAL(currentIndexChanged(int)), this, SLOT(Reg_TypeChange(int)));
}



/*创建数据显示区域------------------------------------------------------------------------------*/
void ShowWindow::Creat_ShowArea(void)
{
    TextBottom = new ShowText(this);
    TextBottom->resize(1000, 100);
}



/*创建主显示区域-------------------------------------------------------------------------------*/
void ShowWindow::Creat_MainArea(void)
{
    MainSplitter = new QSplitter(this);

    //设置方向
    MainSplitter->setOrientation(Qt::Vertical);

    //设置宽度
    MainSplitter->setHandleWidth(6);

    //设置背景色
    MainSplitter->setStyleSheet("QSplitter::handle { background-color:rgb(215,215,215)}");

    //设置拉伸透明属性
    MainSplitter->setOpaqueResize(false);

    //添加窗体
    MainSplitter->addWidget(WidgetTop);
    MainSplitter->addWidget(TextBottom);
    MainSplitter->setStretchFactor(1, 1);


    //设置分割器为主窗体
    this->setCentralWidget(MainSplitter);
}





/*槽函数-----------------------------------------------------------------------------------*/
//更新寄存器地址长度
void ShowWindow::Reg_AddressChange(QString str)
{
    uint16_t num = 0;

    num = str.toInt();
    num = (num == 0) ? (1) : (num);

    TextBottom->SetRegAddress(num);
}

/*更改寄存器显示长度*/
void ShowWindow::Reg_LengthChange(QString str)
{
    uint16_t num = 0;

    num = str.toInt();
    num = (num == 0) ? (1) : (num);

    TextBottom->SetRegLength(num);
}

/*更改寄存器显示类型*/
void ShowWindow::Reg_TypeChange(int num)
{
    TextBottom->SetRegType(num);
}

/*更改寄存器显示格式*/
void ShowWindow::Reg_FormatChange(int num)
{
    TextBottom->SetRegDataFormat(num);
}












