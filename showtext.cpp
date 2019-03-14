#include "showtext.h"

ShowText::ShowText(QWidget *parent) : QTextEdit(parent)
{
    //默认参数初始化
    Reg_Address       = 1;
    Reg_Length        = 100;
    Reg_Type          = COIL_STATUS;
    Reg_DataFormat    = DECIMAL_FORMAT;
    Reg_ConnectState  = false;


    //设置背景色
    QPalette p = this->palette();
    p.setColor(QPalette::Base, QColor(200, 200, 200));
    this->setPalette(p);

    //设置属性
    this->setReadOnly(true);                                        //只读模式
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);     //禁止自动滚屏
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setLineWrapMode(QTextEdit::NoWrap);                       //禁止自动换行
    this->viewport()->setProperty("cursor", QVariant(QCursor(Qt::ArrowCursor)));
    //this->setFocusPolicy(Qt::NoFocus);



    //设置大小
    this->resize(1000, 200);
}


/*设置寄存器地址----------------------------------------------------------------------------------------*/
void ShowText::SetRegAddress(uint16_t addr)
{
    Reg_Address = addr;
    this->ShowData(Reg_Address, Reg_Length, Reg_Type, Reg_DataFormat, Reg_ConnectState);
}

/*设置寄存器长度---------------------------------------------------------------------------------------*/
void ShowText::SetRegLength(uint16_t length)
{
    Reg_Length = length;
    this->ShowData(Reg_Address, Reg_Length, Reg_Type, Reg_DataFormat, Reg_ConnectState);
}

/*设置寄存器类型--------------------------------------------------------------------------------------*/
void ShowText::SetRegType(uint8_t register_type)
{
    Reg_Type = register_type;
    this->ShowData(Reg_Address, Reg_Length, Reg_Type, Reg_DataFormat, Reg_ConnectState);
}

/*设置数据格式----------------------------------------------------------------------------------------*/
void ShowText::SetRegDataFormat(uint8_t data_format)
{
    Reg_DataFormat = data_format;
    this->ShowData(Reg_Address, Reg_Length, Reg_Type, Reg_DataFormat, Reg_ConnectState);
}

/*设置连接状态---------------------------------------------------------------------------------------*/
void ShowText::SetRegConnectState(bool connect_state)
{
    Reg_ConnectState = connect_state;
    this->ShowData(Reg_Address, Reg_Length, Reg_Type, Reg_DataFormat, Reg_ConnectState);
}



/*数据显示-------------------------------------------------------------------------------------------*/
void ShowText::ShowData(uint16_t addr, uint16_t length, uint8_t register_type, uint8_t data_format, bool connect_state)
{
    uint32_t        start_addr = 0, temp_addr = 0;
    uint16_t        i = 0, j = 0, temp_column = 0, temp_row = 0;
    QString         ConnectStateStr = "** Device NOT CONNECTED **\n";
    QString         temp_data_str   = "", temp_str = "";
    QTextCharFormat Format;

    int             samp_data = 1;

    /*清空-----------------------------------------------------------------------------------------*/
    this->clear();



    /*设置固定行高----------------------------------------------------------------------------------*/
    QTextCursor      textCursor = this->textCursor();
    QTextBlockFormat textBlockFormat;
    textBlockFormat.setLineHeight(25, QTextBlockFormat::FixedHeight);         //设置固定行高
    textCursor.setBlockFormat(textBlockFormat);
    this->setTextCursor(textCursor);



    /*设置显示字体----------------------------------------------------------------------------------*/
    Format = this->currentCharFormat();                                      //字体格式设置
    Format.setFontPointSize(12);
    Format.setFontLetterSpacing(110);
    Format.setFontWeight(QFont::Bold);
    Format.setFontFamily(QString::fromUtf8("Arial"));
    Format.setForeground(QColor(255,0,0));
    this->mergeCurrentCharFormat(Format);


    /*连接状态处理---------------------------------------------------------------------------------*/
    if (!connect_state)
    {
       this->insertPlainText(ConnectStateStr);
       //获得字符串高度和宽度
       //QFontMetrics    FontMetrics(Format.font());
       //connect_str_height = FontMetrics.height();
    }



    /*数据显示------------------------------------------------------------------------------------*/
    Format.setForeground(QColor(0,0,0));
    this->mergeCurrentCharFormat(Format);
    switch (register_type)
    {
        case COIL_STATUS:
            start_addr = 0+addr;
        break;

        case INPUT_STATUS:
            start_addr = 100000+addr;
        break;

        case HOLDING_REGISTER:
            start_addr = 400000+addr;
        break;

        case INPUT_REGISTER:
            start_addr = 300000+addr;
        break;
    }


    /*获得行数-----------------------------------------------------------------------------------*/
    temp_row = this->geometry().height();
    temp_row = (temp_row > 6) ? (temp_row-6) : (temp_row);
    temp_row = temp_row/25;
    temp_row = (temp_row == 0) ? (1) : (temp_row);
    if ((!connect_state) && (temp_row > 1))
    {
        temp_row--;
    }
    /*获得列数----------------------------------------------------------------------------------*/
    temp_column = length / temp_row;
    temp_column = (length % temp_row) ? (temp_column+1) : (temp_column);


    /*显示数据----------------------------------------------------------------------------------*/
    for (i=0; i<temp_row; i++)
    {
        temp_data_str = "";
        for (j=0; j<temp_column; j++)
        {
            temp_addr = temp_row*j+i;
            if (temp_addr < length)
            {
                temp_addr += start_addr;
                temp_data_str += QString("%1").arg(temp_addr, 6, 10, QLatin1Char('0'));
                temp_data_str += tr(":  <");
                if ((register_type == COIL_STATUS) || (register_type == INPUT_STATUS))
                {
                    temp_data_str += QString("%1").arg(samp_data, 0, 10, QLatin1Char('0'));
                }
                else
                {
                    switch (data_format)
                    {
                        case BINARY_FORMAT:
                            temp_data_str += QString("%1").arg((uint16_t)samp_data, 16, 2, QLatin1Char('0'));
                        break;

                        case DECIMAL_FORMAT:
                            temp_data_str += QString("%1").arg((uint16_t)samp_data, 5, 10, QLatin1Char('0'));
                        break;

                        case INTEGER_FORMAT:
                            if (i%2 == 0)
                            {
                                samp_data = 10;
                            }
                            else
                            {
                                samp_data = 1000;
                            }
                           temp_data_str += QString("%1").arg(samp_data, 5, 10, QLatin1Char(' '));
                        break;

                        case HEX_FORMAT:
                            temp_data_str += QString("%1").arg((uint16_t)samp_data, 4, 16, QLatin1Char('0')).toUpper();
                            temp_data_str += 'H';
                        break;

                        case FLOAT_FORMAT:
                            if (i%2 == 0)
                            {

                            }
                            else
                            {
                                temp_data_str += QString("%1").arg((float)samp_data, 1, 'f', 4);
                            }
                        break;

                        case SWAPPED_FLOAT_FORMAT:
                            temp_data_str += QString("%1").arg((float)samp_data, 1, 'f', 4);
                        break;

                        case DOUBLE_FORMAT:
                            temp_data_str += QString("%1").arg((float)samp_data, 1, 'f', 4);
                        break;

                        case SWAPPED_DOUBLE_FORMAT:
                            temp_data_str += QString("%1").arg((float)samp_data, 1, 'f', 4);
                        break;
                    }
                }
                temp_data_str += tr(">    ");

                if ((i == 0) && (j == 0))
                {
                    temp_str = temp_data_str;
                }
            }
        }
        this->insertPlainText(temp_data_str);
        if (i != (temp_row-1))
        {
            this->insertPlainText("\n");
        }
    }
    this->moveCursor(QTextCursor::Start);



    QFontMetrics FontMetrics(Format.font());
    QRect rec =  FontMetrics.boundingRect(temp_str);

    Row_Num    = temp_row;
    Column_Num = temp_column;
    Str_Height = 25;
    Str_Width  = rec.width();
}




/*窗体大小更新事件处理--------------------------------------------------------------------------------*/
void ShowText::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    this->ShowData(Reg_Address, Reg_Length, Reg_Type, Reg_DataFormat, Reg_ConnectState);
}

/*鼠标按下事件--------------------------------------------------------------------------------------*/
void ShowText::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

}


/*鼠标双击事件处理-----------------------------------------------------------------------------------*/
void ShowText::mouseDoubleClickEvent(QMouseEvent *event)
{
     uint16_t addr = 0;
     uint16_t temp_height = 0, temp_width = 0;

     temp_height = event->y();
     temp_width  = event->x();
     if (Reg_ConnectState)
     {
         if (temp_height > (Row_Num*Str_Height))
         {
            return ;
         }
         addr = (temp_width/Str_Width)*Row_Num + (temp_height/Str_Height)+1;
     }
     else
     {
         if ((temp_height <= Str_Height) || (temp_height > ((Row_Num+1)*Str_Height)))
         {
             return;
         }
         addr = (temp_width/Str_Width)*Row_Num + (temp_height/Str_Height);
     }

     if (addr < (Reg_Address+Reg_Length))
     {
       QString str;
       str = QString::number(addr);
       QMessageBox::information(this, tr("Information 消息框"), str);
     }
}








