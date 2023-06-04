#ifndef DELETETABLE_H
#define DELETETABLE_H

#include <QWidget>
#include <QFile>
#include <qdebug.h>
#include "utils.h"

namespace Ui {
class deletetable;
}

class deletetable : public QWidget
{
    Q_OBJECT

public:
    void deletetb(QString,QString,QString);
    explicit deletetable(QWidget *parent = nullptr);
    ~deletetable();
signals:
    void SignalSendQString_8(QString tname,QString where);


private:
    Ui::deletetable *ui;
private slots:
    void OnpushButton();
};

#endif // DELETETABLE_H
