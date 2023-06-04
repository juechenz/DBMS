#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

#include "mainwindow.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Login : public QWidget
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();

private:
    Ui::Login *ui;
    MainWindow *mianw;
private slots:
    void SlotGetback();
};
#endif // LOGIN_H
