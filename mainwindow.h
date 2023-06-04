#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QMainWindow>
#include <qdebug.h>
#include <QFile>
#include <QTextStream>
#include <QFileSystemModel>
#include "gramma.h"
#include "info.h"
#include "newtable.h"
#include "altertable.h"
#include "inserttable.h"
#include "selecttable.h"
#include "updatetable.h"
#include "deletetable.h"
#include "cddatabase.h"
#include "data.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int model=99;
    Ui::MainWindow *ui;
    QDir rootDir;
    QString curItem;
    QFileSystemModel *filesystem;
//    QStringList *order;


public slots:


void receivelogin();

private slots:
//void recOrder(QStringList ol);

void on_pushButton_clicked();

void SlotGetQString_2(QString tname,QString colname,QString collength,QString coltype,QString constraint,QString dbname);
void SlotGetQString_3(QString tname,QString colname,QString collength,QString coltype,QString constraint,QString action,QString defaultnum,QString dbname);
void SlotGetQString_4(QString tname,QString colname,QString where);
void SlotGetSelectSet(QStringList colList,QStringList resSet,QStringList order);
void SlotGetQString_5(QString tname,QString colname,QString values);
void SlotGetQString_6(QString tname,QString colname,QString values);
void SlotGetQString_7(QString tname);
void SlotGetQString_8(QString tname,QString where);
void SlotGetQString_9(QString dbname);
void SlotGetQString_10(QString dbname);
void SlotGetQString_11(QString tname,QString colname,QString collength,QString coltype,QString constraint,QString defaultnum,QString dbname);
void SlotGetdbname(QString dbname);
void OnpushButton2();
void OnpushButton3();
void OnpushButton4();
void OnpushButton5();
void OnpushButton6();
void OnpushButton8();
void OnpushButton9();

void on_pushButton_7_clicked();

void on_pushButton_10_clicked();
void on_treeView_clicked(const QModelIndex &index);

void on_tableWidget_customContextMenuRequested(const QPoint &pos);

void on_pushButton_11_clicked();

void on_treeView_customContextMenuRequested(const QPoint &pos);

void on_pushButton_12_clicked();

void on_pushButton_13_clicked();

void on_pushButton_14_clicked();

void on_pushButton_17_clicked();

void on_pushButton_18_clicked();

void on_pushButton_15_clicked();

void on_pushButton_16_clicked();

signals:
void Signallogin();

private:

    gramma gra;
    newtable *nt;
    altertable *at;
    inserttable *it;
    selecttable *st;
    updatetable *ut;
    deletetable *det;
    cddatabase *cddb;

    void issql(QString);
    void showinfo(int);
};
#endif // MAINWINDOW_H
