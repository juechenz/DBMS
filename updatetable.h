#ifndef UPDATETABLE_H
#define UPDATETABLE_H

#include <QWidget>
#include <qdebug.h>
#include <qfile.h>
#include <utils.h>

namespace Ui {
class updatetable;
}

class updatetable : public QWidget
{
    Q_OBJECT

public:
    explicit updatetable(QWidget *parent = nullptr);
    ~updatetable();
    void update(QString tname,QString set,QString where,QString uname);
signals:
    void SignalSendQString_6(QString tname,QString set,QString where);


private:
    Ui::updatetable *ui;
private slots:
    void OnpushButton();
};

#endif // UPDATETABLE_H
