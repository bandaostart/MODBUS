#ifndef SHOWWINDOW_H
#define SHOWWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QSplitter>
#include <QTextEdit>
#include <QLineEdit>
#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QGridLayout>
#include <QSplitter>
#include <QIntValidator>
#include "showtext.h"
#include <QDebug>





class ShowWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit ShowWindow(QWidget *parent = 0);

    void Creat_ParaArea(void);
    void Creat_ShowArea(void);
    void Creat_MainArea(void);

public slots:
    void Reg_AddressChange(QString str);
    void Reg_LengthChange(QString str);
    void Reg_TypeChange(int num);
    void Reg_FormatChange(int num);


public:
    QSplitter      *MainSplitter;

    QWidget        *WidgetTop;
    QLabel         *AddressNameLabel;
    QLineEdit      *AddressTextEdit;
    QLabel         *LengthNameLabel;
    QLineEdit      *LengthTextEdit;
    QLabel         *IdNameLabel;
    QLineEdit      *IdTextEdit;
    QLabel         *TypeNameLabel;
    QComboBox      *TypeComBox;

    QLabel         *NumPollNameLabel;
    QLabel         *NumPollTextLabel;
    QLabel         *NumResponseNameLabel;
    QLabel         *NumResponseTextLabel;
    QPushButton    *ResetButton;

    QIntValidator *validator_address;
    QIntValidator *validator_length;
    QIntValidator *validator_modbusid;

    ShowText       *TextBottom;
};

#endif // SHOWWINDOW_H
