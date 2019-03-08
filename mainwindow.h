#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QList>
#include <QVector>
#include <QMdiSubWindow>

#include "showwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    //操作工具栏相关
    QAction  *NewAction;
    QAction  *OpenAction;
    QAction  *SaveAction;
    QAction  *QuickConnectAction;
    QAction  *QuickDisConnectAction;
    QAction  *DefineDataAction;
    QAction  *ShowDataAction;
    QAction  *ShowTrafficAction;
    QAction  *PrintAction;
    QAction  *HelpAction;
    QAction  *AboutAction;

    QActionGroup *QuickActionGroup;
    QActionGroup *ShowActionGroup;

    //数据显示相关
    QAction *BinaryAction;
    QAction *DecimalAction;
    QAction *IntegerAction;
    QAction *HexAction;
    QAction *FloatAction;
    QAction *SwappedFloatAction;
    QAction *DoubleAction;
    QAction *SwappedDoubleAction;

    QActionGroup *DataTypeActionGroup;


    QMenu    *FileMenu;
    QMenu    *ConnectionMenu;
    QMenu    *SetupMenu;
    QMenu    *ViewMenu;
    QMenu    *WindowMenu;
    QMenu    *HelpMenu;

    QToolBar *OperatorTool;
    QToolBar *DataTypeTool;

    QLabel   PollStatusBarLabel;
    QLabel   RspStatusBarLabel;


    //数据显示窗体
    QList<ShowWindow *> ListShowWindow;


private:
    void     CreatActions();
    void     CreatMenus();
    void     CreatToolBars();
    void     CreatMainWindow();

private slots:
    void     Slot_NewActionFun();
    void     Slot_OpenActonFun();
    void     Slot_SaveActionFun();
    void     Slot_QuickActionFun(QAction *action);
    void     Slot_DefineDataActionFun();
    void     Slot_ShowActionFun(QAction *action);
    void     Slot_PrintActionFun();
    void     Slot_HelpActionFun();
    void     Slot_AboutActionFun();

    void     Slot_DataTypeActionFun(QAction *action);


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
