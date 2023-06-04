#ifndef UTILS_H
#define UTILS_H
#include <QString>
#include <QStringList>
#include <qdebug.h>

int switch_check(QString );
int switch_type(QString );
QString switch_back_check(QString);
QString switch_back_type(QString);
bool whereAnalysis(QString where,QStringList fieldName,QStringList lineList);
bool whereAnalysis_delete(QString where,QStringList fieldName,QStringList lineList);

#endif // UTILS_H
