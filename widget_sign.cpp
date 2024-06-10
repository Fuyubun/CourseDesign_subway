#include "widget_sign.h"
#include "ui_widget_sign.h"

widget_sign::widget_sign(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widget_sign)
{
    ui->setupUi(this);

    //设置界面标题和大小
    this->setWindowTitle("SubwaySystemSign");
    this->setFixedSize(627,458);

    //设置窗口图标
    this->setWindowIcon(QIcon("://picture//logo.jpg"));

    //设置背景图片
    this->setAutoFillBackground(true);
    QPalette p =this->palette();QImage img=QImage("://picture//sign.jpg");
    img=img.scaled(this->size());
    QBrush *pic=new QBrush(img);
    p.setBrush(QPalette::Window,*pic);
    //QPixmap pix("://picture//log_sign.jpg");
    //p.setBrush(QPalette::Window,QBrush(pix));
    this->setPalette(p);
}

widget_sign::~widget_sign()
{
    delete ui;
}

void widget_sign::on_returnButton_clicked()
{
    this->close();
    this->ui->idLineEdit->clear();
    this->ui->passwordLineEdit->clear();
    emit returnInitWidget();//激活返回初始化界面信号
}

void widget_sign::recvInitWidget()
{
    this->show();
}

void widget_sign::writeUserSignFile(QString id,double money)
{
    QFile file("D://qtProject//Subway//User_temp.txt");
    file.open(QIODevice::WriteOnly|QIODevice::Text);

    QTextStream out(&file);
    out<<id<<endl;
    out<<money<<endl;

    file.close();
}

bool widget_sign::userSign()
{
    QString inID, inPassword;
    bool signFlag=false;

    inID=this->ui->idLineEdit->text();
    inPassword=this->ui->passwordLineEdit->text();

    //检查用户名或密码是否为空
    bool check1=ui->idLineEdit->text().isEmpty();
    bool check2=ui->passwordLineEdit->text().isEmpty();
    if(check1||check2){
        QMessageBox::information(this,"提示","账号或密码不能为空！");
        return false;
    }

    QString readStr;
    QFile file("D://qtProject//Subway//User.txt");
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream in(&file);
    int cnt=0;

    while(!in.atEnd())
    {
        readStr=in.readLine();
        cnt++;
        if(((cnt-1)%3==0||cnt==1)&&inID==readStr){
            readStr=in.readLine();//读密码
            if(inPassword==readStr){
                signFlag=true;
                QString qMoney=in.readLine();//读资金
                double uMoney=qMoney.toDouble();
                this->writeUserSignFile(inID,uMoney);
                break;
            }
        }
    }

    file.close();

    if(signFlag)
        QMessageBox::information(this,"提示","登录成功!");
    else
        QMessageBox::information(this,"提示","账号不存在或密码错误!");

    return signFlag;
}

bool widget_sign::admSign()
{
    bool signFlag=false;

    QString id,password;
    id=this->ui->idLineEdit->text();
    password=this->ui->passwordLineEdit->text();
    //检查输入是否为空
    bool check1=ui->idLineEdit->text().isEmpty();
    bool check2=ui->passwordLineEdit->text().isEmpty();
    if(check1||check2){
        QMessageBox::information(this,"提示","账号或密码不能为空！");
        return false;
    }

    if(id==ADM_ID && password==ADM_PASSWORD){
        QMessageBox::information(this,"提示","登录成功!");
        signFlag=true;
    }
    else
      QMessageBox::information(this,"提示","账号或密码错误");

    return signFlag;
}

void widget_sign::on_userSignButton_clicked()
{
    if(this->userSign()){
        this->close();
        emit showUserWidget();

        this->ui->idLineEdit->clear();
        this->ui->passwordLineEdit->clear();
    }
}

void widget_sign::userSignProcess(User_Widget *uw)
{
    connect(this,SIGNAL(showUserWidget()),uw,SLOT(recvSignWidget()));
}

void widget_sign::admSignProcess(adm_MainWindow *adm)
{
    connect(this,SIGNAL(showAdmMainWindow()),adm,SLOT(recvSignWidget()));
}

void widget_sign::on_admSignButton_clicked()
{
    if(this->admSign()){
        this->close();
        emit showAdmMainWindow();

        this->ui->idLineEdit->clear();
        this->ui->passwordLineEdit->clear();
    }
}
