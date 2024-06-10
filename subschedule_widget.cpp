#include "subschedule_widget.h"
#include "ui_subschedule_widget.h"

subSchedule_Widget::subSchedule_Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::subSchedule_Widget)
{
    ui->setupUi(this);

    //设置界面标题和大小
    this->setWindowTitle("SubwaySystemSubSchedule");
    this->setFixedSize(421,382);

    //设置窗口图标
    this->setWindowIcon(QIcon("://picture//logo.jpg"));

    //设置下拉框
    this->ui->lineComboBox->addItem("请选择");
    this->ui->lineComboBox->addItem("1号线");
    this->ui->lineComboBox->addItem("2号线");
    this->ui->lineComboBox->addItem("3号线");
    this->ui->lineComboBox->addItem("4号线");
    this->ui->lineComboBox->addItem("5号线");
    this->ui->lineComboBox->addItem("6号线");
}

subSchedule_Widget::~subSchedule_Widget()
{
    delete ui;
}

void subSchedule_Widget::recvAdmMainWindow()
{
    this->show();
}

void subSchedule_Widget::on_cancelButton_clicked()
{
    this->ui->directionComboBox->clear();
    this->ui->handLineEdit->clear();

    this->close();
}

void subSchedule_Widget::on_lineComboBox_activated(int index)
{
    this->ui->directionComboBox->clear();
    this->ui->handLineEdit->clear();

    QStringList strList;
    switch(index)
    {
    case 1:
        strList<<"开福区政府"<<"省政府";
        break;
    case 2:
        strList<<"光达"<<"梅溪湖西";
        break;
    case 3:
        strList<<"广生"<<"山塘";
        break;
    case 4:
        strList<<"杜家坪"<<"罐子岭";
        break;
    case 5:
        strList<<"水渡河"<<"毛竹塘";
        break;
    case 6:
        strList<<"黄花机场T1T2"<<"谢家桥";
        break;
    default:
        break;
    }

    ui->directionComboBox->addItems(strList);
}

void subSchedule_Widget::changeCycle(int line, int direction, double cycle)
{
    //把所有发车时间读出来存进数组
    double Cycle[6][2];
    QString readStr;
    QFile file("D://qtProject//Subway//subwayCycle.txt");
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream in(&file);
    for(int i=0;i<6;i++)
    {
        Cycle[i][0]=in.readLine().toDouble();
        Cycle[i][1]=in.readLine().toDouble();
    }
    file.close();

    //更改发车间隔
    Cycle[line-1][direction]=cycle;

    //写入新的数据
    QFile file_w("D://qtProject//Subway//subwayCycle.txt");
    file_w.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream out(&file_w);
    out<<Cycle[0][0]<<endl;
    out<<Cycle[0][1]<<endl;
    file_w.close();

    QFile file_w2("D://qtProject//Subway//subwayCycle.txt");
    file_w2.open(QIODevice::Append|QIODevice::Text);
    QTextStream out1(&file_w2);
    for(int i=1;i<6;i++)
    {
        out1<<Cycle[i][0]<<endl;
        out1<<Cycle[i][1]<<endl;
    }
    file_w2.close();
}

void subSchedule_Widget::on_handButton_clicked()
{
    bool check=false;
    check=(this->ui->lineComboBox->currentIndex() && !(this->ui->handLineEdit->text().isEmpty()));

    if(check){
        if(this->ui->handLineEdit->text().toDouble()<=0 || this->ui->handLineEdit->text().toDouble()>20)
            QMessageBox::information(this,"提示","发车间隔不应小于等于0分钟或大于20分钟！");
        else{
            this->changeCycle(this->ui->lineComboBox->currentIndex(),this->ui->directionComboBox->currentIndex(),
                              this->ui->handLineEdit->text().toDouble());
            QMessageBox::information(this,"提示","操作成功！");
        }
    }
    else
        QMessageBox::information(this,"提示","请输入完整的信息！");
}
