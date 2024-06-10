#include "adm_mainwindow.h"
#include "ui_adm_mainwindow.h"

adm_MainWindow::adm_MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::adm_MainWindow)
{
    ui->setupUi(this);

    //设置界面标题和大小
    this->setWindowTitle("SubwaySystemAdm");
    this->setFixedSize(1090,710);

    //设置窗口图标
    this->setWindowIcon(QIcon("://picture//logo.jpg"));

    //设置背景图片
    this->setAutoFillBackground(true);
    QPalette p =this->palette();
    QImage img=QImage("://picture//adm.jpg");
    img=img.scaled(this->size());
    QBrush *pic=new QBrush(img);
    p.setBrush(QPalette::Window,*pic);
    //QPixmap pix("://picture//user_administrator.jpg");
    //p.setBrush(QPalette::Window,QBrush(pix));
    this->setPalette(p);

    this->ui->textBrowser->setText("欢迎使用！");
}

adm_MainWindow::~adm_MainWindow()
{
    delete ui;
}

void adm_MainWindow::recvSignWidget()
{
    this->show();
}

void adm_MainWindow::on_userInfo_triggered()
{
    this->ui->textBrowser->clear();

    QFile file("D://qtProject//Subway//User.txt");
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream in(&file);

    QString readStr;
    int cnt=0;
    while(!in.atEnd())
    {
        readStr=in.readLine();
        cnt++;
        this->ui->textBrowser->append(tr("用户%1:%2").arg(cnt).arg(readStr));//把id读出来显示
        readStr=in.readLine();//密码读出来不用
        readStr=in.readLine();
        this->ui->textBrowser->append(tr("账户余额：%1").arg(readStr));//把账户余额读出来显示
    }

    file.close();
}

void adm_MainWindow::subwayInit()
{
    //读subwayCycle.txt文件，将发车间隔赋值给subwayLine类
    QFile file("D://qtProject//Subway//subwayCycle.txt");
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream in(&file);
    int i=0;
    QString cycle0,cycle1;
    while(!in.atEnd())
    {
        cycle0=in.readLine();
        cycle1=in.readLine();
        this->sub[i].setCycle(cycle0.toDouble(),cycle1.toDouble());
        i++;
    }

    file.close();
}

void adm_MainWindow::on_exti_triggered()
{
    this->close();
    this->ui->textBrowser->clear();
    this->ui->textBrowser->setText("欢迎使用！");
    emit exitSign();
}

int adm_MainWindow::getSubWayNum(double cycle)
{
    int num=0;
    QTime currentTime=QTime::currentTime();
    int totalSeconds = currentTime.second() + 60*currentTime.minute() + 3600*currentTime.hour();

    if(totalSeconds<23400)//六点半发车
        num=0;
    else if(totalSeconds>82800)//二十三点结束
        num=(int)(59400/((int)(cycle*60)));
    else
        num=(int)((totalSeconds-23400)/((int)(cycle*60)));

    return num;
}

void adm_MainWindow::on_subwayRun_triggered()
{
    this->subwayInit();
    this->ui->textBrowser->clear();

    int num=0;
    QString direction0,direction1;

    for(int i=0;i<6;i++)
    {
        switch(i)
        {
        case 0:
            direction0="开福区政府";
            direction1="省政府";
            break;
        case 1:
            direction0="光达";
            direction1="梅溪湖西";
            break;
        case 2:
            direction0="广生";
            direction1="山塘";
            break;
        case 3:
            direction0="杜家坪";
            direction1="罐子岭";
            break;
        case 4:
            direction0="水渡河";
            direction1="毛竹塘";
            break;
        case 5:
            direction0="黄花机场T1T2";
            direction1="谢家桥";
            break;
        default:
            direction0="NaN";
            direction1="NaN";
            break;
        }

        this->ui->textBrowser->append(tr("%1号线").arg(i+1));
        num=this->getSubWayNum(this->sub[i].getCycle0());
        this->ui->textBrowser->append(tr("往%0方向 发车间隔:%1分钟,已发车%2辆").arg(direction0).arg(this->sub[i].getCycle0()).arg(num));
        num=this->getSubWayNum(this->sub[i].getCycle1());
        this->ui->textBrowser->append(tr("往%0方向 发车间隔:%1分钟,已发车%2辆").arg(direction1).arg(this->sub[i].getCycle1()).arg(num));
        this->ui->textBrowser->append("\n");
    }
}

void adm_MainWindow::on_subwaySchedule_triggered()
{
    emit showSubSheduleWidget();
}

void adm_MainWindow::admMainWindowProcess(subSchedule_Widget *sch)
{
    connect(this,SIGNAL(showSubSheduleWidget()),sch,SLOT(recvAdmMainWindow()));
}
