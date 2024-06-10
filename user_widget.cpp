#include "user_widget.h"
#include "ui_user_widget.h"

User_Widget::User_Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::User_Widget)
{
    ui->setupUi(this);

    //设置界面标题和大小
    this->setWindowTitle("SubwaySystemUser");
    this->setFixedSize(1090,710);

    //设置窗口图标
    this->setWindowIcon(QIcon("://picture//logo.jpg"));

    //设置背景图片
    this->setAutoFillBackground(true);
    QPalette p =this->palette();
    QImage img=QImage("://picture//user_test.jpg");
    img=img.scaled(this->size());
    QBrush *pic=new QBrush(img);
    p.setBrush(QPalette::Window,*pic);
    //QPixmap pix("://picture//user_administrator.jpg");
    //p.setBrush(QPalette::Window,QBrush(pix));
    this->setPalette(p);
}

User_Widget::~User_Widget()
{
    delete ui;
}

void User_Widget::enterUserInformation(QString id,double money)
{
    this->u.id=id;
    this->u.money=money;
}

void User_Widget::userWidgetInit()
{
    //读User_temp文件，获取此时登录的用户信息
    QFile file("D://qtProject//Subway//User_temp.txt");
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream in(&file);

    QString id=in.readLine();
    QString Qmoney=in.readLine();
    double Dmoney=Qmoney.toDouble();

    file.close();

    this->enterUserInformation(id,Dmoney);
}

void User_Widget::refreshUserFile()
{
    QString strAll;
    QStringList strList;

    //读取User文件的所有信息
    QFile readFile("D://qtProject//Subway//User.txt");
    if(readFile.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream stream(&readFile);
        strAll=stream.readAll();
    }
    readFile.close();

    //写入新的用户信息
    QFile writeFile("D://qtProject//Subway//User.txt");
    if(writeFile.open(QIODevice::WriteOnly|QIODevice::Text)){
        QTextStream stream(&writeFile);
        strList=strAll.split("\n");//换行符分隔文本

        for(int i=0;i<strList.count();i++){
            if(strList.at(i).contains(this->u.id)&&i%3==0){
                int j=i+1,k=i+2;
                stream<<strList.at(i)<<endl;//写入用户名
                stream<<strList.at(j)<<endl;//写入密码
                QString strTemp=strList.at(k);
                QString replaceTemp=QString::number(this->u.money,'f',2);
                strTemp.replace(0,strTemp.length(),replaceTemp);
                stream<<strTemp<<endl;//更改金额
                i=k;
            }
            else{
                if(i==strList.count()-1)
                    stream<<strList.at(i);
                else
                    stream<<strList.at(i)<<endl;
            }
        }
    }
    writeFile.close();
}

void User_Widget::recvSignWidget()
{
    this->show();
    this->userWidgetInit();
}

void User_Widget::reUserData()
{
    this->userWidgetInit();
    this->refreshUserFile();//先用User_temp数据更新user_information再更新User文件
}

void User_Widget::userWidgetProcess(userPay_widget *up,userBuyTicket_widget *ubt)
{
    connect(this,SIGNAL(showUserPayWidget()),up,SLOT(recvUserWidget()));
    connect(up,SIGNAL(refreshUserData()),this,SLOT(reUserData()));
    connect(this,SIGNAL(showBuyTicketWidget()),ubt,SLOT(recvUserWidget()));
    connect(ubt,SIGNAL(refreshUserData()),this,SLOT(reUserData()));
}

void User_Widget::watchTickets()
{
    bool check=false;
    QString readStr;
    QFile file("D://qtProject//Subway//ticket.txt");
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream in(&file);
    int cnt=0;
    while(!in.atEnd())
    {
        readStr=in.readLine();
        cnt++;
        if(((cnt-1)%3==0 || cnt==1) && readStr==this->u.id){
            check=true;
            QString startStation=in.readLine();
            QString endStation=in.readLine();
            cnt+=2;
            QMessageBox::information(this,"已购车票情况",tr("起始站：%1\n终点站：%2").arg(startStation).arg(endStation));
        }
    }
    file.close();

    if(!check){
        QMessageBox::information(this,"提示","未查询到车票购买情况！");
    }
}

//退出登录
void User_Widget::on_exitButton_clicked()
{
    this->close();
    emit exitSign();
}

//查看个人信息
void User_Widget::on_watchButton_clicked()
{
    QMessageBox::information(this,"个人信息",tr("用户名：%1\n账户剩余金额：%2").arg(this->u.id).arg(this->u.money));
}

void User_Widget::on_payButton_clicked()
{
    emit showUserPayWidget();
}

void User_Widget::on_buyTicketButton_clicked()
{
    emit showBuyTicketWidget();
}

void User_Widget::on_watchTicketButton_clicked()
{
    this->watchTickets();
}
