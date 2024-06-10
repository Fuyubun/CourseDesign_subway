#ifndef SUBSCHEDULE_WIDGET_H
#define SUBSCHEDULE_WIDGET_H

#include <QWidget>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

namespace Ui {
class subSchedule_Widget;
}

class subSchedule_Widget : public QWidget
{
    Q_OBJECT

public:
    explicit subSchedule_Widget(QWidget *parent = nullptr);
    ~subSchedule_Widget();
    void changeCycle(int line,int direction,double cycle);

private slots:
    void recvAdmMainWindow();//接收来自管理员界面的信号

    void on_cancelButton_clicked();

    void on_lineComboBox_activated(int index);

    void on_handButton_clicked();

    void on_autoButton_clicked();

private:
    Ui::subSchedule_Widget *ui;
};

#endif // SUBSCHEDULE_WIDGET_H
