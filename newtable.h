#ifndef NEWTABLE_H
#define NEWTABLE_H

#include <QWidget>
#include <QDir>
#include <QFile>
#include <QString>
#include <QDateTime>
#include <qmessagebox.h>
#include <qdebug.h>

struct tbinfostruct{
    QString tname;
    QString path;
    QString createtime;
    QString user;
    QString dbname;
};

namespace Ui {
class newtable;
}

class newtable : public QWidget
{
    Q_OBJECT

public:
    explicit newtable(QWidget *parent = nullptr);
    ~newtable();
    void createtable(QString tname,QString desc);
    void droptable(QString tname,QString uname);
    QVector <tbinfostruct*> tbvector;
    int counts=0;
    QString tablenum;
    QString desc1;
signals:
    void SignalSendQString_2(QString tname,QString colname,QString collength,QString coltype,QString constraint,QString dbname);
    void SignalSendQString_7(QString tname);
    void SignalSendQString_11(QString tname,QString colname,QString collength,QString coltype,QString constraint,QString defaultnum,QString dbname);
private:
    Ui::newtable *ui;
private slots:
    void OnpushButton();
    void OnpushButton2();
    void on_pushButton_3_clicked();
};

#endif // NEWTABLE_H
