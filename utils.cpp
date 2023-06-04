#include "utils.h"

int switch_type(QString atype){
    if(atype == "int")
        return 1;
    else if(atype == "char")
        return 2;
    else if(atype == "float")
        return 3;
    else
        return 0;
}


int switch_check(QString acheck){
    if(acheck == "unique")
        return 1;
    else if(acheck == "notnull")
        return 2;
    else if(acheck == "primarykey")
        return 3;
    else if(acheck == "default")
        return 4;
    else
        return 0;
}

QString switch_back_type(QString atype){
    if(atype == "1")
        return "int";
    else if(atype == "2")
        return "char";
    else if(atype == "3")
        return "float";
    else
        return 0;
}

QString switch_back_check(QString acheck){
    if(acheck == "1")
        return "unique";
    else if(acheck == "2")
        return "notnull";
    else if(acheck == "3")
        return "primarykey";
    else if(acheck == "4")
        return "default";
    else
        return 0;
}

bool whereAnalysis(QString where,QStringList fieldName,QStringList lineList){
    QStringList conditionList=where.split(' ');
    conditionList.removeAll("");
    qDebug()<<conditionList;

    conditionList.removeAll("&");
    //qDebug()<<conditionList;

    //拟采用语法树或者数据结构的栈解析where子句
    //测试
    int flag=0;
    int conditionSize=conditionList.size();
    if(conditionSize<=0)  return false;

    for(int i=0;i<conditionSize;i++){
        QStringList singleCond=conditionList[i].split('=');
        int target=fieldName.indexOf(singleCond[0]);   //记录查找字段位置
        if(target==-1){
            qDebug()<<"where句中字段不存在";
            return false;
        }
        if(lineList[target]==singleCond[1]){
            flag++;
        }
    }

    if(flag==conditionSize)  return true;
    else return false;
}

bool whereAnalysis_delete(QString where,QStringList fieldName,QStringList lineList){
    QStringList conditionList=where.split(' ');
    //conditionList.removeFirst();
    qDebug()<<conditionList;

    conditionList.removeAll("&");
    //qDebug()<<conditionList;

    //拟采用语法树或者数据结构的栈解析where子句
    //测试
    int flag=0;
    int conditionSize=conditionList.size();
    if(conditionSize<=0)  return false;

    for(int i=0;i<conditionSize;i++){
        QStringList singleCond=conditionList[i].split('=');
        int target=fieldName.indexOf(singleCond[0]);   //记录查找字段位置
        if(target==-1){
            qDebug()<<"where句中字段不存在";
            return false;
        }
        if(lineList[target]==singleCond[1]){
            flag++;
        }
    }

    if(flag==conditionSize)  return true;
    else return false;
}
