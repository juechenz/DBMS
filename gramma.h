#ifndef GRAMMA_H
#define GRAMMA_H


#include <stdio.h>
#include  <QString>
#include <QFile>
#include <qdebug.h>

#include "info.h"
#include "data.h"

class gramma
{
public:
    int translate(int,QString);
    data da;
};

#endif // GRAMMA_H
