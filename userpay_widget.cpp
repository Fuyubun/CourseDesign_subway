#include "userpay_widget.h"
#include "ui_userpay_widget.h"

userPay_widget::userPay_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::userPay_widget)
{
    ui->setupUi(this);

    //设置界面标题和大小
    this->setWindowTitle("SubwaySystemUserPay");
    this->setFixedSize(458,292);

    //设置窗口图标
    this->setWindowIcon(QIcon("://picture//logo.jpg"));
}

userPay_widget::~userPay_widget()
{
    delete ui;
}

void userPay_widget::userPay()
{
    //检查输入金额是否为空
    bool check=this->ui->moneyLineEdit->text().isEmpty();
    if(check){
        QMessageBox::information(this,"提示","充值金额不能为空！");
        return;
    }

    //检查输入金额是否小于等于0或大于999
    QString QpayMoneyTemp=this->ui->moneyLineEdit->text();
    double DpayMoney=QpayMoneyTemp.toDouble();
    if(DpayMoney<=0||DpayMoney>999){
        QMessageBox::information(this,"提示","充值金额不能为非正数或大于999！");
        return;
    }

    QFile file("D://qtProject//Subway//User_temp.txt");
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream in(&file);
    //User_temp文件中，第一行为用户名，第二行为金额
    //依次读取用户名和老金额
    QString id=in.readLine();
    QString QoldMoney=in.readLine();
    file.close();

    //计算并写入新金额
    double DoldMoney=QoldMoney.toDouble();
    double DnewMoney=DoldMoney+DpayMoney;
    file.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream out(&file);
    out<<id<<endl;
    out<<DnewMoney<<endl;
    file.close();

    emit refreshUserData();

    QMessageBox::information(this,"提示","充值成功！");
    this->ui->moneyLineEdit->clear();
    this->close();
}

void userPay_widget::recvUserWidget()
{
    this->show();
}

//取消充值
void userPay_widget::on_cancelButton_clicked()
{
    this->ui->moneyLineEdit->clear();
    this->close();
}
//充值
void userPay_widget::on_payButton_clicked()
{
    this->userPay();
}
