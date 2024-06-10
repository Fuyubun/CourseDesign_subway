#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //设置界面标题和大小
    this->setWindowTitle("SubwaySystemInit");
    this->setFixedSize(726,403);

    //设置窗口图标
    this->setWindowIcon(QIcon("://picture//logo.jpg"));

    //设置背景图片
    this->setAutoFillBackground(true);
    QPalette p =this->palette();
    QImage img=QImage("://picture//init_test.jpg");
    img=img.scaled(this->size());
    QBrush *pic=new QBrush(img);
    p.setBrush(QPalette::Window,*pic);
    //QPixmap pix("://picture//init.jpg");
    //p.setBrush(QPalette::Window,QBrush(pix));
    this->setPalette(p);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_logButton_clicked()//点击注册按钮槽
{
    this->hide();
    emit showLogWidget();
}

void Widget::on_signButton_clicked()//点击登录按钮槽
{
    this->hide();
    emit showSignWidget();
}

void Widget::recvLogWidget()//接收注册界面返回信号槽函数
{
    this->show();
}

void Widget::recvSignWidget()//接收登录界面返回信号槽函数
{
    this->show();
}

void Widget::recvUserWidget()//接收用户界面退出登录信号槽函数
{
    this->show();
}

void Widget::recvAdmMainWindow()//接收管理员界面退出登录信号槽函数
{
    this->show();
}

void Widget::initWidgetProcess(widget_log *log,widget_sign *sign,User_Widget *uw,adm_MainWindow *adm)
{
    connect(this,SIGNAL(showLogWidget()),log,SLOT(recvInitWidget()));
    connect(log,SIGNAL(returnInitWidget()),this,SLOT(recvLogWidget()));
    connect(this,SIGNAL(showSignWidget()),sign,SLOT(recvInitWidget()));
    connect(sign,SIGNAL(returnInitWidget()),this,SLOT(recvSignWidget()));

    connect(uw,SIGNAL(exitSign()),this,SLOT(recvUserWidget()));
    connect(adm,SIGNAL(exitSign()),this,SLOT(recvAdmMainWindow()));
}
