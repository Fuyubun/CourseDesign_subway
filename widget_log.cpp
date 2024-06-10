#include "widget_log.h"
#include "ui_widget_log.h"

widget_log::widget_log(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widget_log)
{
    ui->setupUi(this);

    //设置界面标题和大小
    this->setWindowTitle("SubwaySystemLog");
    this->setFixedSize(627,458);

    //设置窗口图标
    this->setWindowIcon(QIcon("://picture//logo.jpg"));

    //设置背景图片
    this->setAutoFillBackground(true);
    QPalette p =this->palette();
    QImage img=QImage("://picture//log.jpg");
    img=img.scaled(this->size());
    QBrush *pic=new QBrush(img);
    p.setBrush(QPalette::Window,*pic);
    //QPixmap pix("://picture//log_sign.jpg");
    //p.setBrush(QPalette::Window,QBrush(pix));
    this->setPalette(p);
}

widget_log::~widget_log()
{
    delete ui;
}

void widget_log::on_returnButton_clicked()
{
    this->close();
    emit returnInitWidget();//激活返回初始化界面信号
}

void widget_log::recvInitWidget()
{
    this->show();
}

bool widget_log::writeUserFile(QString id,QString password,double money)
{
    bool openFlag=true;
    QFile file("D://qtProject//Subway//User.txt");

    if(!file.open(QIODevice::Append|QIODevice::Text)){
        QMessageBox::information(this,"提示","文件打开失败！");
        openFlag=false;
    }
    else{
        QTextStream out(&file);
        out<<id<<endl;
        out<<password<<endl;
        out<<money<<endl;
    }

    file.close();

    return openFlag;
}

/*int widget_log::getUserNumber(void)
{
    ifstream ifs;

    ifs.open("User.txt", ios::in);

    int number = 0;
    string readBuf;
    while (getline(ifs,readBuf))
    {
        number++;
    }

    ifs.close();

    number /= 3;
    return number;
}
*/

void widget_log::userLog(void)
{
    QString inID, inPassword, rePassword;
    bool logFlag=true;

    inID=this->ui->idLineEdit->text();
    inPassword=this->ui->passwordLineEdit->text();
    rePassword=this->ui->rePasswordLineEdit->text();

    //检查用户名或密码是否为空
    bool check1=ui->idLineEdit->text().isEmpty();
    bool check2=ui->passwordLineEdit->text().isEmpty();
    bool check3=ui->rePasswordLineEdit->text().isEmpty();
    if(check1||check2||check3){
        QMessageBox::information(this,"提示","用户名或密码不能为空！");
        return;
    }

    QString readStr;
    QFile file("D://qtProject//Subway//User.txt");
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream in(&file);
    int cnt=0;
    //判断用户名是否被占用
    while(!in.atEnd())
    {
        readStr=in.readLine();
        cnt++;
        if(((cnt-1)%3==0||cnt==1)&&inID==readStr){
            QMessageBox::information(this,"提示","该用户名已被占用！");
            logFlag=false;
            break;
        }
    }
    //判断两次输入密码是否相同
    if(inPassword!=rePassword){
        QMessageBox::information(this,"提示","请输入两次相同的密码！");
        logFlag=false;
    }

    file.close();

    if(logFlag==true&&this->writeUserFile(inID,inPassword))
        QMessageBox::information(this,"提示","注册成功！");
}

void widget_log::on_userLogButton_clicked()
{
    this->userLog();
    this->ui->idLineEdit->clear();
    this->ui->passwordLineEdit->clear();
    this->ui->rePasswordLineEdit->clear();
}
