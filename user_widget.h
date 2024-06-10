#ifndef USER_WIDGET_H
#define USER_WIDGET_H

#include <QWidget>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QStringList>
#include "userinformation.h"
#include "userpay_widget.h"
#include "userbuyticket_widget.h"

namespace Ui {
class User_Widget;
}

class User_Widget : public QWidget
{
    Q_OBJECT

public:
    explicit User_Widget(QWidget *parent = nullptr);
    ~User_Widget();
    void enterUserInformation(QString id,double money);//录入用户信息
    void userWidgetInit();//获取用户信息
    void refreshUserFile();//更新User.txt文件
    void watchTickets();//查看已购车票
    void userWidgetProcess(userPay_widget *up,userBuyTicket_widget *ubt);//用户界面进程

private slots:
    void recvSignWidget();//接收来自登录界面的信号
    void reUserData();//更新用户信息

    void on_exitButton_clicked();

    void on_watchButton_clicked();

    void on_payButton_clicked();

    void on_buyTicketButton_clicked();

    void on_watchTicketButton_clicked();

signals:
    void exitSign();//退出登录信号
    void showUserPayWidget();//展示用户充值界面
    void showBuyTicketWidget();//展示购票界面

private:
    Ui::User_Widget *ui;
    userInformation u;
};

#endif // USER_WIDGET_H
