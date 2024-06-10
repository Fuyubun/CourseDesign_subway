#include "userbuyticket_widget.h"
#include "ui_userbuyticket_widget.h"

userBuyTicket_widget::userBuyTicket_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::userBuyTicket_widget)
{
    ui->setupUi(this);

    //设置界面标题和大小
    this->setWindowTitle("SubwaySystemBuyTicket");
    this->setFixedSize(658,423);

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

userBuyTicket_widget::~userBuyTicket_widget()
{
    delete ui;
}

void userBuyTicket_widget::recvUserWidget()
{
    this->show();
}

void userBuyTicket_widget::on_cancelButton_clicked()
{
    this->ui->startComboBox->clear();
    this->ui->endComboBox->clear();
    this->ui->priceTextBrowser->clear();

    this->close();
}

void userBuyTicket_widget::on_lineComboBox_activated(int index)
{
    this->ui->startComboBox->clear();
    this->ui->endComboBox->clear();
    this->ui->priceTextBrowser->clear();
    QStringList strList;

    switch(index){
    case 1://1号线
        strList<<"请选择"<<"省政府"<<"友谊路"<<"铁道学院"<<"徐家冲"<<"黄土岭"<<"南湖路"<<"侯家塘"<<"南门口"<<"黄兴广场"<<"五一广场"<<"培元桥"<<"文昌阁"<<"开福寺"
              <<"北辰三角洲"<<"马厂"<<"开福区政府";
        break;
    case 2://2号线
        strList<<"请选择"<<"梅溪湖西"<<"麓云路"<<"文化艺术中心"<<"梅溪湖东"<<"望城路(汽车西站)"<<"金星路"<<"西湖公园"<<"溁湾镇"<<"橘子洲"<<"湘江中路"<<"五一广场"
              <<"芙蓉广场"<<"迎宾路口"<<"袁家岭"<<"长沙火车站"<<"锦泰广场"<<"万家丽广场"<<"人民东路"<<"长沙大道"<<"沙湾公园"<<"杜花路"<<"长沙火车南站"<<"光达";
        break;
    case 3://3号线
        strList<<"请选择"<<"山塘"<<"洋湖湿地"<<"洋湖新城"<<"阳光"<<"中南大学"<<"阜埠河"<<"灵官渡"<<"侯家塘"<<"东塘站"<<"桂花公园"<<"阿弥岭"<<"朝阳村"<<"长沙火车站"
              <<"烈士公园东"<<"丝茅冲"<<"四方坪"<<"鸦雀湖"<<"长沙大学"<<"月湖公园北"<<"湘龙"<<"星沙"<<"松雅湖南"<<"星沙文体中心"<<"螺丝塘"<<"广生";
        break;
    case 4://4号线
        strList<<"请选择"<<"罐子岭"<<"月亮岛西"<<"相江新城"<<"汉王陵公园"<<"福元大桥西"<<"茶子山"<<"观沙岭"<<"六沟垅"<<"望月湖"<<"溁湾镇"<<"湖南师大"<<"湖南大学"
              <<"阜埠河"<<"碧沙湖"<<"黄土岭"<<"砂子塘"<<"赤岗岭"<<"树木岭"<<"圭塘"<<"沙湾公园"<<"粟塘"<<"平阳"<<"长沙火车南站"<<"光达"<<"杜家坪";
        break;
    case 5://5号线
        strList<<"请选择"<<"毛竹塘"<<"板塘冲"<<"大塘"<<"雨花区政府"<<"木桥"<<"圭塘"<<"高桥南"<<"高桥北"<<"芙蓉区政府"<<"万家丽广场"<<"马王堆"<<"火炬村"<<"鸭子铺"
              <<"马栏山"<<"月湖公园北"<<"白茅铺"<<"土桥"<<"水渡河";
        break;
    case 6://6号线
        strList<<"请选择"<<"谢家桥"<<"象鼻窝"<<"中塘"<<"一师范西校区"<<"长庆"<<"和馨园"<<"长丰"<<"麓谷体育公园"<<"麓谷公园"<<"涧塘"<<"湖南工商大学"<<"白鸽咀"
              <<"湘雅三医院"<<"六沟垅"<<"文昌阁"<<"湘雅医院"<<"烈士公园南"<<"迎宾路口"<<"窑岭湘雅二医院"<<"朝阳村"<<"芙蓉区政府"<<"人民东路"
             <<"花桥"<<"隆平水稻博物馆"<<"农科院农大"<<"东湖"<<"韶光"<<"龙华"<<"檀木桥"<<"曹家坪"<<"龙峰"<<"大路村"<<"木马椴"<<"黄花机场T1T2";
        break;
    default:
        break;
    }

    ui->startComboBox->addItems(strList);
    ui->endComboBox->addItems(strList);
}

void userBuyTicket_widget::on_endComboBox_activated(int index)
{
    bool check=false;
    if(this->ui->startComboBox->currentIndex()!=0 && index!=0)
        check=true;

    if(check){
        int price=this->calculateTicketPrice();
        QString pri=QString::number(price);
        this->ui->priceTextBrowser->setText(pri);
    }
    else
        this->ui->priceTextBrowser->clear();
}

int userBuyTicket_widget::calculateTicketPrice()
{
    int price = 2;
    int lineNum = (this->ui->endComboBox->currentIndex()) - (this->ui->startComboBox->currentIndex());
    lineNum = (lineNum>0)?lineNum:-lineNum;

    if(lineNum==0){
        QMessageBox::information(this,"提示","起点站与终点站不能相同！");
        price=0;
    }
    else if(lineNum>=11 && lineNum<16)
        price=3;
    else if(lineNum>=16 && lineNum<23)
        price=4;
    else if(lineNum>=23 && lineNum<30)
        price=5;
    else if(lineNum>=30)
        price=6;

    return price;
}

void userBuyTicket_widget::on_startComboBox_activated(int index)
{
    bool check=false;
    if(this->ui->endComboBox->currentIndex()!=0 && index!=0)
        check=true;

    if(check){
        int price=this->calculateTicketPrice();
        QString pri=QString::number(price);
        this->ui->priceTextBrowser->setText(pri);
    }
    else
        this->ui->priceTextBrowser->clear();
}

void userBuyTicket_widget::buyTicket()
{
    //判断信息是否完整
    bool check=false;
    if(this->ui->lineComboBox->currentIndex()!=0 &&this->ui->endComboBox->currentIndex()!=0
            && this->ui->startComboBox->currentIndex()!=0)
        check=true;
    else {
        QMessageBox::information(this,"提示","请输入完整信息！");
        return;
    }

    int lineNum = (this->ui->endComboBox->currentIndex()) - (this->ui->startComboBox->currentIndex());
    if(check && lineNum){
        //读取此时用户信息
        QFile file("D://qtProject//Subway//User_temp.txt");
        file.open(QIODevice::ReadOnly|QIODevice::Text);
        QTextStream in(&file);
        QString id=in.readLine();
        QString Qmoney=in.readLine();
        double Dmoney=Qmoney.toDouble();
        file.close();

        //判断余额是否足够
        if(Dmoney<this->calculateTicketPrice()){
            QMessageBox::information(this,"提示","余额不足！");
            return;
        }
        else {
            double newMoney=Dmoney-this->calculateTicketPrice();
            //写入新的用户信息
            QFile file("D://qtProject//Subway//User_temp.txt");
            file.open(QIODevice::WriteOnly|QIODevice::Text);
            QTextStream out(&file);
            out<<id<<endl;
            out<<newMoney<<endl;
            file.close();

            //写入车票信息
            QString startStation=this->ui->startComboBox->currentText();
            QString endStation=this->ui->endComboBox->currentText();
            this->writeTicketFile(id,startStation,endStation);

            //弹出提示并激活更新用户信息信号
            QMessageBox::information(this,"提示","购票成功！");
            emit refreshUserData();

            this->ui->startComboBox->clear();
            this->ui->endComboBox->clear();
            this->ui->priceTextBrowser->clear();
        }
    }
    else
        QMessageBox::information(this,"提示","购票失败！请检查信息是否正确");
}

void userBuyTicket_widget::writeTicketFile(QString id, QString startStation, QString endStation)
{
    QFile Tfile("D://qtProject//Subway//ticket.txt");
    Tfile.open(QIODevice::Append|QIODevice::Text);
    QTextStream Tout(&Tfile);

    Tout<<id<<endl;
    Tout<<startStation<<endl;
    Tout<<endStation<<endl;
    Tfile.close();
}

void userBuyTicket_widget::on_buyButton_clicked()
{
    this->buyTicket();
}
