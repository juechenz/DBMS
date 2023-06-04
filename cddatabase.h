#ifndef CDDATABASE_H
#define CDDATABASE_H

#include <QWidget>
#include <regex>
#include<iostream>
#include <fstream>
#include  <QString>
#include <qdebug.h>
#include <QDir>
#include <QFileInfo>
#include <QFile>
#include <QVector>
#include <qmessagebox.h>
#include <QDateTime>

struct dbstruct{
    QString dbname;
    QString path;
    QString createtime;
    QString user;
};

struct userin{
    QString user1;
    QString user2;
    QString descrip;
};


namespace Ui {
class cddatabase;
}

class cddatabase : public QWidget
{
    Q_OBJECT

public:
    explicit cddatabase(QWidget *parent = nullptr);
    ~cddatabase();
    void createdb(QString dbname);
    void dropdb(QString dbname);
    void grantuser(QString,QString,QString);
    void revokeuser(QString,QString,QString);
    bool permission(QString,QString,QString);
    QVector <dbstruct*> dbvector;
    QVector <userin*> uservector;
signals:
    void SignalSendQString_9(QString dbname);
    void SignalSendQString_10(QString dbname);
    void SignalSenddbname(QString dbname);

private:
    Ui::cddatabase *ui;
private slots:
    void OnpushButton();
    void OnpushButton2();
};

#endif // CDDATABASE_H
