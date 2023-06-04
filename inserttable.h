#ifndef INSERTTABLE_H
#define INSERTTABLE_H

#include <QWidget>

namespace Ui {
class inserttable;
}

class inserttable : public QWidget
{
    Q_OBJECT

public:
    explicit inserttable(QWidget *parent = nullptr);
    ~inserttable();
    void inserttb(QString tname,QStringList attri_list,QStringList datalist,QString uname);
    bool check_unique(QString tname,QString check_data,int index);

signals:
    void SignalSendQString_5(QString tname,QString colname,QString values);


private:
    Ui::inserttable *ui;
private slots:
    void OnpushButton();
};

#endif // INSERTTABLE_H
