#ifndef DATA_H
#define DATA_H


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
#include "cddatabase.h"
#include <QInputDialog>
#include "newtable.h"
#include "altertable.h"
#include "inserttable.h"
#include "updatetable.h"
#include "deletetable.h"
#include "selecttable.h"

using namespace std;


class data
{
public:
    int table_name;
    int datadelete(char*);
    int dataupdate(char*);
    int datainsert(char*);
    int datainsert2(char*);
    int dataselect(char*);
    int dataselectsome(char *);
    int dataselectall(char *);
    int createtable(char *);
    int droptable(char *);
    int alteradd(char *);
    int altermodify1(char *);
    int altermodify2(char *);
    int alterdrop(char *);
    int alterrename(char *);
    int createdatabse(char *);
    int dropdatabse(char *str);
    int usedatabse(char *str);
    int grant1(char *str);
    int grant2(char *str);
    int revoke1(char *str);
    int revoke2(char *str);
selecttable* getST();


private:
    cddatabase cd;
    newtable ct;
    altertable at;
    updatetable ut;
    deletetable dt;
    inserttable it;
    selecttable st;
};

#endif // DATA_H
