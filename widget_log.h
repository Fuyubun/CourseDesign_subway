#ifndef WIDGET_LOG_H
#define WIDGET_LOG_H

#include <QWidget>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QDebug>
#include <iostream>
#include <fstream>
#include <string>
#include <QMessageBox>

using namespace std;

namespace Ui {
class widget_log;
}

class widget_log : public QWidget
{
    Q_OBJECT

public:
    explicit widget_log(QWidget *parent = nullptr);
    ~widget_log();
    bool writeUserFile(QString id,QString password,double money=0);
    //int getUserNumber(void);
    void userLog(void);

private slots:
    void on_returnButton_clicked();
    void recvInitWidget();//接受初始界面信号槽函数

    void on_userLogButton_clicked();

signals:
    void returnInitWidget();//返回初始化界面信号

private:
    Ui::widget_log *ui;
};

#endif // WIDGET_LOG_H
