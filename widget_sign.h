#ifndef WIDGET_SIGN_H
#define WIDGET_SIGN_H

#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>
#include "user_widget.h"
#include "adm_mainwindow.h"

#define ADM_ID "adm"
#define ADM_PASSWORD "654adm321"

namespace Ui {
class widget_sign;
}

class widget_sign : public QWidget
{
    Q_OBJECT

public:
    explicit widget_sign(QWidget *parent = nullptr);
    ~widget_sign();
    void writeUserSignFile(QString id,double money);
    bool userSign();
    bool admSign();
    void userSignProcess(User_Widget *uw);
    void admSignProcess(adm_MainWindow *adm);

private:
    Ui::widget_sign *ui;

private slots:
    void on_returnButton_clicked();
    void recvInitWidget();//接受初始界面信号槽函数

    void on_userSignButton_clicked();

    void on_admSignButton_clicked();

signals:
    void returnInitWidget();//返回初始化界面信号
    void showUserWidget();//展示用户界面信号
    void showAdmMainWindow();//展示管理员界面信号

};

#endif // WIDGET_SIGN_H
