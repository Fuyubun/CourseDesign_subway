#ifndef USERBUYTICKET_WIDGET_H
#define USERBUYTICKET_WIDGET_H

#include <QWidget>
#include <QStringList>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

namespace Ui {
class userBuyTicket_widget;
}

class userBuyTicket_widget : public QWidget
{
    Q_OBJECT

public:
    explicit userBuyTicket_widget(QWidget *parent = nullptr);
    ~userBuyTicket_widget();
    int calculateTicketPrice();//计算票价
    void buyTicket();//购票
    void writeTicketFile(QString id,QString startStation,QString endStation);

private slots:
    void recvUserWidget();//接收到用户界面的信号

    void on_cancelButton_clicked();

    void on_lineComboBox_activated(int index);

    void on_endComboBox_activated(int index);

    void on_startComboBox_activated(int index);

    void on_buyButton_clicked();

private:
    Ui::userBuyTicket_widget *ui;

signals:
    void refreshUserData();//更新用户信息
};

#endif // USERBUYTICKET_WIDGET_H
