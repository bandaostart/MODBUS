#ifndef SHOWWIDGET_H
#define SHOWWIDGET_H

#include <QObject>
#include <QSplitter>
#include <QTextEdit>
#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>

class ShowWidget : public QSplitter
{
    Q_OBJECT

public:
    explicit ShowWidget(QWidget *parent = 0);


public:
    QWidget   *WidgetTop;
    QLabel    *AddressNameLabel;
    QLabel    *AddressTextLabel;
    QLabel    *LengthNameLabel;
    QLabel    *LengthTextLabel;
    QLabel    *IdNameLabel;
    QLabel    *IdTextLabel;





    QTextEdit *TextBottom;
};

#endif // SHOWWIDGET_H
