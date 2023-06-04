#ifndef SELECTTABLE_H
#define SELECTTABLE_H

#include <QWidget>
#include<QFile>
#include<qdebug.h>
#include<utils.h>
#include "newtable.h"
#include "inserttable.h"

namespace Ui {
class selecttable;
}

class selecttable : public QWidget
{
    Q_OBJECT

public:
    explicit selecttable(QWidget *parent = nullptr);
    void select(QString tname,QString colname,QString where,QString ordername,QString uname);
    void selectAll(QString tname,QString where,QString ordername,QString uname);
    void tableJoin(QStringList tnameList,/* QString colname,*/ QString where);
//    void setOrder(QStringList *ol){order=ol;};
//    QStringList* getOrder(){return order;};
    QStringList setOrder(QString ordername);
    ~selecttable();
signals:
    void SignalSendQString_4(QString tname,QString colname,QString where);
    void SignalSendSelectSet(QStringList colList,QStringList resSet,QStringList order);
//    void sendOrder(QStringList order);

private:
    Ui::selecttable *ui;
    newtable temp;

private slots:
    void OnpushButton();
};

#endif // SELECTTABLE_H
