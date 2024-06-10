#ifndef USERPAY_WIDGET_H
#define USERPAY_WIDGET_H

#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

namespace Ui {
class userPay_widget;
}

class userPay_widget : public QWidget
{
    Q_OBJECT

public:
    explicit userPay_widget(QWidget *parent = nullptr);
    ~userPay_widget();
    void userPay();

private slots:
    void recvUserWidget();//接收来自用户界面的信号

    void on_cancelButton_clicked();

    void on_payButton_clicked();

signals:
    void refreshUserData();//更新用户信息

private:
    Ui::userPay_widget *ui;
};

#endif // USERPAY_WIDGET_H
