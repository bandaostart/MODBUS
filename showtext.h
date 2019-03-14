#ifndef SHOWTEXT_H
#define SHOWTEXT_H

#include <QObject>
#include <QTextEdit>
#include <QMouseEvent>
#include <QMessageBox>

#define  COIL_STATUS                    0
#define  INPUT_STATUS                   1
#define  HOLDING_REGISTER               2
#define  INPUT_REGISTER                 3

#define  BINARY_FORMAT                  0
#define  DECIMAL_FORMAT                 1
#define  INTEGER_FORMAT                 2
#define  HEX_FORMAT                     3
#define  FLOAT_FORMAT                   4
#define  SWAPPED_FLOAT_FORMAT           5
#define  DOUBLE_FORMAT                  6
#define  SWAPPED_DOUBLE_FORMAT          7




class ShowText : public QTextEdit
{
    Q_OBJECT

public:
    uint16_t Reg_Address;
    uint16_t Reg_Length;
    uint8_t  Reg_Type;
    uint8_t  Reg_DataFormat;
    bool     Reg_ConnectState;

    uint16_t Row_Num;
    uint16_t Column_Num;
    uint16_t Str_Height;
    uint16_t Str_Width;


public:
    explicit ShowText(QWidget *parent = 0);
    void SetRegAddress(uint16_t addr);
    void SetRegLength(uint16_t length);
    void SetRegType(uint8_t register_type);
    void SetRegDataFormat(uint8_t data_format);
    void SetRegConnectState(bool connect_state);
    void ShowData(uint16_t addr, uint16_t length, uint8_t register_type, uint8_t data_format, bool connect_state);

    void resizeEvent(QResizeEvent *event);                                    //窗体大小改变事件
    void mousePressEvent(QMouseEvent *event);                                 //鼠标按下事件
    void mouseDoubleClickEvent(QMouseEvent *event);                           //鼠标双击事件
};

#endif // SHOWTEXT_H
