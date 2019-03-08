#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //创建Actions
    CreatActions();

    //创建Menus
    CreatMenus();

    //创建ToolBars
    CreatToolBars();

    //创建主窗体
    CreatMainWindow();

}

MainWindow::~MainWindow()
{
    delete ui;
}



//创建Actions
void MainWindow::CreatActions()
{
    /*操作相关------------------------------------------------------------------------------------------*/
    //新建
    NewAction = new QAction(QIcon(":/image/new.png"), tr("New"), this);
    NewAction->setStatusTip(tr("Creat a new document"));
    connect(NewAction, SIGNAL(triggered()), this, SLOT(Slot_NewActionFun()));

    //打开
    OpenAction = new QAction(QIcon(":/image/open.png"), tr("Open"), this);
    OpenAction->setStatusTip(tr("Open an existing document"));
    connect(OpenAction, SIGNAL(triggered()), this, SLOT(Slot_OpenActonFun()));

    //保存
    SaveAction = new QAction(QIcon(":/image/save.png"), tr("Save"), this);
    SaveAction->setStatusTip(tr("Save the active document"));
    connect(SaveAction, SIGNAL(triggered()), this, SLOT(Slot_SaveActionFun()));




    //连接
    QuickConnectAction = new QAction(QIcon(":/image/connect.png"), tr("Qucik Connect"), this);
    QuickConnectAction->setStatusTip(tr("Connect to modbus using current settings"));

    //断开
    QuickDisConnectAction = new QAction(QIcon(":/image/disconnect.png"), tr("Quick Disconnect"), this);
    QuickDisConnectAction->setStatusTip(tr("Disconnect from modbus"));

    //组成Actions组
    QuickActionGroup = new QActionGroup(this);
    QuickActionGroup->addAction(QuickConnectAction);
    QuickConnectAction->setCheckable(true);
    QuickActionGroup->addAction(QuickDisConnectAction);
    QuickDisConnectAction->setCheckable(true);
    QuickDisConnectAction->setChecked(true);
    connect(QuickActionGroup, SIGNAL(triggered(QAction*)), this, SLOT(Slot_QuickActionFun(QAction*)));




    //默认数据
    DefineDataAction = new QAction(QIcon(":/image/definedata.png"), tr("Define Data"), this);
    DefineDataAction->setStatusTip(tr("Select modbus data"));
    connect(DefineDataAction, SIGNAL(triggered()), this, SLOT(Slot_DefineDataActionFun()));




    //显示数据
    ShowDataAction = new QAction(QIcon(":/image/showdata.png"), tr("Show Data"), this);
    ShowDataAction->setStatusTip(tr("Show modbus data"));

    //显示通信
    ShowTrafficAction = new QAction(QIcon(":/image/showtraffic.png"), tr("Show Traffic"), this);
    ShowTrafficAction->setStatusTip(tr("Show serial modbus"));

    //组成Action组
    ShowActionGroup = new QActionGroup(this);
    ShowActionGroup->addAction(ShowDataAction);
    ShowDataAction->setCheckable(true);
    ShowActionGroup->addAction(ShowTrafficAction);
    ShowTrafficAction->setCheckable(true);
    ShowDataAction->setChecked(true);
    connect(ShowActionGroup, SIGNAL(triggered(QAction*)), this, SLOT(Slot_ShowActionFun(QAction*)));




    //打印
    PrintAction = new QAction(QIcon(":/image/print.png"), tr("Print"), this);
    PrintAction->setStatusTip(tr("Print modbus data"));
    connect(PrintAction, SIGNAL(triggered()), this, SLOT(Slot_PrintActionFun()));

    //帮助
    HelpAction = new QAction(QIcon(":/image/help.png"), tr("Help"), this);
    HelpAction->setStatusTip(tr("Display help for modbus"));
    connect(HelpAction, SIGNAL(triggered()), this, SLOT(Slot_HelpActionFun()));

    //关于
    AboutAction = new QAction(QIcon(":/image/about.png"), tr("About Software"), this);
    AboutAction->setStatusTip(tr("About Software"));
    connect(AboutAction, SIGNAL(triggered()), this, SLOT(Slot_AboutActionFun()));



    /*数据显示模式相关------------------------------------------------------------------------------------*/
    DataTypeActionGroup = new QActionGroup(this);

    //将文字写在图片上
    QFont font;
    font.setBold(true);
    font.setFamily(QString::fromUtf8("Arial"));
    font.setWeight(40);
    font.setPixelSize(20);

    QPixmap pix(QSize(32, 32));
    pix.fill(QColor(Qt::white));

    QPainter painter(&pix);
    painter.begin(&pix);
    painter.setPen(Qt::black);
    painter.setFont(font);


    //二进制
    painter.drawText(pix.rect(), Qt::AlignCenter, tr("Bin"));
    BinaryAction = new QAction(QIcon(pix), tr("Binary"), DataTypeActionGroup);
    BinaryAction->setStatusTip(tr("Binary"));
    BinaryAction->setCheckable(true);

    //无符号整型
    pix.fill(QColor(Qt::white));
    painter.drawText(pix.rect(), Qt::AlignCenter, tr("Dec"));
    DecimalAction = new QAction(QIcon(pix), tr("Decimal"), DataTypeActionGroup);
    DecimalAction->setStatusTip(tr("Decimal"));
    DecimalAction->setCheckable(true);
    DecimalAction->setChecked(true);

    //有符号整形
    pix.fill(QColor(Qt::white));
    painter.drawText(pix.rect(), Qt::AlignCenter, tr("Int"));
    IntegerAction = new QAction(QIcon(pix), tr("Integer"), DataTypeActionGroup);
    IntegerAction->setStatusTip(tr("Integer"));
    IntegerAction->setCheckable(true);

    //16进制
    pix.fill(QColor(Qt::white));
    painter.drawText(pix.rect(), Qt::AlignCenter, tr("Hex"));
    HexAction = new QAction(QIcon(pix), tr("Hex"), DataTypeActionGroup);
    HexAction->setStatusTip(tr("Hex"));
    HexAction->setCheckable(true);

    //浮点数
    pix.fill(QColor(Qt::white));
    painter.drawText(pix.rect(), Qt::AlignCenter, tr("Flo"));
    FloatAction = new QAction(QIcon(pix), tr("Float"), DataTypeActionGroup);
    FloatAction->setStatusTip(tr("Float"));
    FloatAction->setCheckable(true);

    //反向浮点数
    pix.fill(QColor(Qt::white));
    painter.drawText(pix.rect(), Qt::AlignCenter, tr("Flo"));
    painter.setPen(Qt::red);

    painter.drawLine(QPoint(0, 27), QPoint(5, 27));
    painter.drawLine(QPoint(5, 27), QPoint(27, 5));
    painter.drawLine(QPoint(27, 5), QPoint(32, 5));
    painter.setPen(Qt::black);
    SwappedFloatAction = new QAction(QIcon(pix), tr("Swapped Float"), DataTypeActionGroup);
    SwappedFloatAction->setStatusTip(tr("Swapped Float"));
    SwappedFloatAction->setCheckable(true);

    //双精度浮点数
    pix.fill(QColor(Qt::white));
    painter.drawText(pix.rect(), Qt::AlignCenter, tr("Dou"));
    DoubleAction = new QAction(QIcon(pix), tr("Double"), DataTypeActionGroup);
    DoubleAction->setStatusTip(tr("Double"));
    DoubleAction->setCheckable(true);


    //反向双精度浮点数
    pix.fill(QColor(Qt::white));
    painter.drawText(pix.rect(), Qt::AlignCenter, tr("Dou"));
    painter.setPen(Qt::red);

    painter.drawLine(QPoint(0, 27), QPoint(5, 27));
    painter.drawLine(QPoint(5, 27), QPoint(27, 5));
    painter.drawLine(QPoint(27, 5), QPoint(32, 5));
    SwappedDoubleAction = new QAction(QIcon(pix), tr("Swapped Double"), DataTypeActionGroup);
    SwappedDoubleAction->setStatusTip(tr("Swapped Double"));
    SwappedDoubleAction->setCheckable(true);

    painter.end();

    connect(DataTypeActionGroup, SIGNAL(triggered(QAction*)), this, SLOT(Slot_DataTypeActionFun(QAction*)));
}



//创建Menus
void MainWindow::CreatMenus()
{
    //文件菜单
    FileMenu  = ui->menuBar->addMenu(tr("File"));


    //连接菜单
    ConnectionMenu = ui->menuBar->addMenu(tr("Connect"));


    //设置菜单
    SetupMenu = ui->menuBar->addMenu(tr("Setup"));


    //视图菜单
    ViewMenu  = ui->menuBar->addMenu(tr("View"));


    //窗体菜单
    ViewMenu  = ui->menuBar->addMenu(tr("Window"));


    //帮助菜单
    HelpMenu  = ui->menuBar->addMenu(tr("Help"));
}



//创建ToolBars
void MainWindow::CreatToolBars()
{
    /*功能操作相关-----------------------------------------------------------------------------------*/
    OperatorTool = ui->mainToolBar;
    OperatorTool->setToolTip(tr("Operator"));
    OperatorTool->setAllowedAreas(Qt::TopToolBarArea | Qt::LeftToolBarArea);
    //OperatorTool->setMovable(false);

    OperatorTool->addAction(NewAction);
    OperatorTool->addAction(OpenAction);
    OperatorTool->addAction(SaveAction);
    OperatorTool->addSeparator();

    OperatorTool->addAction(QuickConnectAction);
    OperatorTool->addAction(QuickDisConnectAction);
    OperatorTool->addSeparator();

    OperatorTool->addAction(DefineDataAction);
    OperatorTool->addAction(ShowDataAction);
    OperatorTool->addAction(ShowTrafficAction);
    OperatorTool->addSeparator();

    OperatorTool->addAction(PrintAction);
    OperatorTool->addAction(HelpAction);
    OperatorTool->addAction(AboutAction);

    //用于ToolBar分行
    this->addToolBarBreak();


    /*数据显示模型先关-------------------------------------------------------------------------------*/
    DataTypeTool = this->addToolBar(tr("Model"));
    DataTypeTool->setAllowedAreas(Qt::TopToolBarArea | Qt::LeftToolBarArea);

    DataTypeTool->addAction(BinaryAction);
    DataTypeTool->addAction(DecimalAction);
    DataTypeTool->addAction(IntegerAction);
    DataTypeTool->addAction(HexAction);
    DataTypeTool->addAction(FloatAction);
    DataTypeTool->addAction(SwappedFloatAction);
    DataTypeTool->addAction(DoubleAction);
    DataTypeTool->addAction(SwappedDoubleAction);
}



//创建主窗体
void MainWindow::CreatMainWindow()
{
    //设置中心体窗体属性
    this->resize(1100, 600);

    //状态栏设置
    PollStatusBarLabel.setFrameStyle(QFrame::Box | QFrame::Sunken);
    PollStatusBarLabel.setText(tr("Polls: 0"));
    ui->statusBar->addPermanentWidget(&PollStatusBarLabel);

    RspStatusBarLabel.setFrameStyle(QFrame::Box | QFrame::Sunken);
    RspStatusBarLabel.setText(tr("Resps: 0"));
    ui->statusBar->addPermanentWidget(&RspStatusBarLabel);


    //创建数据显示窗体
    ShowWindow *defaultShowWidget = new ShowWindow(this);
    ListShowWindow.append(defaultShowWidget);


    //设置子窗体属性,size改变属性，移动属性，size大小
    QMdiSubWindow *MidSubWindow;
    MidSubWindow = ui->mdiArea->addSubWindow(ListShowWindow.at(0));
    ListShowWindow.at(0)->show();
    MidSubWindow->setOption(QMdiSubWindow::RubberBandResize);
    MidSubWindow->setOption(QMdiSubWindow::RubberBandMove);
    MidSubWindow->resize(1000, 300);


    //显示版本号
    ui->statusBar->showMessage(tr("Author:bandaostart Version:V1.00"));
}















/*槽函数------------------------------------------------------------------------------------------*/
/*功能操作相关-----------------------------------------------------------------------*/
//新建
void MainWindow::Slot_NewActionFun()
{

}


//打开
void MainWindow::Slot_OpenActonFun()
{

}


//保存
void MainWindow::Slot_SaveActionFun()
{

}

//快速连接
void MainWindow::Slot_QuickActionFun(QAction *action)
{

}


//默认数据
void MainWindow::Slot_DefineDataActionFun()
{

}


//显示
void MainWindow::Slot_ShowActionFun(QAction *action)
{

}


//打印
void MainWindow::Slot_PrintActionFun()
{

}

//帮助
void MainWindow::Slot_HelpActionFun()
{

}

//关于
void MainWindow::Slot_AboutActionFun()
{

}


/*数据显示模型相关---------------------------------------------------------------------*/
void MainWindow::Slot_DataTypeActionFun(QAction *action)
{


}
























































































