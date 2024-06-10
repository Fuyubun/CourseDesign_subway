#include "widget.h"
#include "widget_log.h"
#include "widget_sign.h"
#include "user_widget.h"
#include "userpay_widget.h"
#include "userbuyticket_widget.h"
#include "adm_mainwindow.h"
#include "subschedule_widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget Init;
    widget_log log;
    widget_sign sign;
    User_Widget uw;
    userPay_widget up;
    userBuyTicket_widget ubt;
    adm_MainWindow adm;
    subSchedule_Widget sub;

    Init.show();
    Init.initWidgetProcess(&log,&sign,&uw,&adm);
    sign.userSignProcess(&uw);
    sign.admSignProcess(&adm);
    uw.userWidgetProcess(&up,&ubt);
    adm.admMainWindowProcess(&sub);

    return a.exec();
}
