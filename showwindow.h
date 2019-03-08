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
#include <QDebug>


#define  COIL_STATUS                    0
#define  INPUT_STATUS                   1
#define  HOLDING_REGISTER               2
#define  INPUT_REGISTER                 3


class ShowWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit ShowWindow(QWidget *parent = 0);

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

    QTextEdit      *TextBottom;

signals:

public slots:

public:
    void ShowData(uint16_t addr, uint16_t length, uint8_t register_type, uint8_t data_format, bool connect_state);
    void resizeEvent(QResizeEvent *event);


};

#endif // SHOWWINDOW_H
