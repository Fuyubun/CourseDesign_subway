#ifndef ADM_MAINWINDOW_H
#define ADM_MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QTime>
#include "subwayline.h"
#include "subschedule_widget.h"

namespace Ui {
class adm_MainWindow;
}

class adm_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit adm_MainWindow(QWidget *parent = nullptr);
    ~adm_MainWindow();
    void subwayInit();//地铁发车时间初始化
    int getSubWayNum(double cycle);
    void admMainWindowProcess(subSchedule_Widget *sch);

private slots:
    void recvSignWidget();//接收来自登录界面的信号

    void on_userInfo_triggered();

    void on_exti_triggered();

    void on_subwayRun_triggered();

    void on_subwaySchedule_triggered();

signals:
    void exitSign();//退出登录信号
    void showSubSheduleWidget();//展示车辆调度页面信号

private:
    Ui::adm_MainWindow *ui;
    subwayLine sub[6];
};

#endif // ADM_MAINWINDOW_H
