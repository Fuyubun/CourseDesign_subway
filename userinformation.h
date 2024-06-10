#ifndef USERINFORMATION_H
#define USERINFORMATION_H

#include <QObject>

class userInformation : public QObject
{
    Q_OBJECT
public:
    explicit userInformation(QObject *parent = nullptr);
    QString id;
    QString password;
    double money;

signals:

public slots:
};

#endif // USERINFORMATION_H
