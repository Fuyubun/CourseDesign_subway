#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "widget_log.h"
#include "widget_sign.h"
#include "user_widget.h"
#include "adm_mainwindow.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    void initWidgetProcess(widget_log *log,widget_sign *sign,User_Widget *uw,adm_MainWindow *adm);

private slots:
    void on_logButton_clicked();
    void on_signButton_clicked();
    void recvLogWidget();//接收注册界面返回信号槽函数
    void recvSignWidget();//接收登录界面返回信号槽函数
    void recvUserWidget();//接收用户界面退出登录信号
    void recvAdmMainWindow();//接收管理员界面退出登录信号

signals:
    void showLogWidget();//注册界面展示信号
    void showSignWidget();//登录界面展示信号

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
