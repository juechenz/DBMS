#ifndef ALTERTABLE_H
#define ALTERTABLE_H

#include <QWidget>
#include <QDir>
#include <QFile>
#include <qdebug.h>
#include <qmessagebox.h>
#include "utils.h"


struct tdf_temp{
    QString aname;
    QString atype;
    QString alength;
};

struct tic_temp{
    QString aname;
    QString acheck;
    QString default_value;
};


namespace Ui {
class altertable;
}

class altertable : public QWidget
{
    Q_OBJECT

public:
    QVector <tdf_temp*> tdf_vector;
    QVector <tic_temp*> tic_vector;
    void alter_add(QString,QString,QString,QString);
    void alter_drop(QString,QString,QString);
    void alter_rename(QString,QString,QString,QString);
    void alter_modify_tic(QString,QString,QString,QString);
    void alter_modify_typelen(QString,QString,QString,QString);
    explicit altertable(QWidget *parent = nullptr);
    ~altertable();
signals:
    void SignalSendQString_3(QString tname,QString colname,QString collength,QString coltype,
                             QString constraint,QString action,QString defaultnum,QString dbname);


private:
    Ui::altertable *ui;
    QString atype1;
private slots:
    void OnpushButton();
};

#endif // ALTERTABLE_H
