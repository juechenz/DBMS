#include "updatetable.h"
#include "ui_updatetable.h"

using namespace std;
extern QString username;
extern QString databasename;

updatetable::updatetable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::updatetable)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()), this, SLOT(OnpushButton()));
}

updatetable::~updatetable()
{
    delete ui;
}


void updatetable::OnpushButton()
{
    //QString str = ui->textEdit->toPlainText();
    QString tname = ui->lineEdit->text();
    QString set = ui->lineEdit_2->text();
    QString where = ui->textEdit->toPlainText();

    if(where.indexOf("\n") != -1) //如果有\n
    {
        where.replace("\n",""); //将每个\n都替换为空
    }


    emit SignalSendQString_6(tname,set,where);
    //update(tname,set,where);

}


void updatetable::update(QString tname, QString set, QString where, QString uname)
{
    //分割set表达式
    QStringList setexp = set.split('=');
    qDebug()<<setexp;

    /*
     * 通过.tdf文件判断set后的字段名是否正确
     */
    //.tdf文件位置
    QString dbpath_tdf =
            QCoreApplication::applicationDirPath().append("/"+uname+"/"+databasename+"/"+tname+"/"+tname+".tdf");
    QFile file_tdf(dbpath_tdf);

    QString output;
    QStringList fieldName;
    QStringList fieldType;
    QStringList fieldLen;
    file_tdf.open(QFile::ReadOnly);
    file_tdf.readLine();
    //获取字段名、数据类型、数据长度
    for(int i=0;!file_tdf.atEnd();i++){
        output=file_tdf.readLine();
        QStringList outputList=output.split(' ');
        fieldName.append(outputList[0]);
        fieldType.append(outputList[1]);
        fieldLen.append(outputList[2].remove("\r\n"));
    }
    file_tdf.close();

    //判断字段名是否正确
    if(!fieldName.contains(setexp[0])){
        qDebug()<<"指定修改字段不存在";
        return;
    }

    //where条件为空
    if(where==NULL){
        //确认.trd文件位置
        if(!setexp[1].contains(setexp[0])||!setexp[1].contains('+'|'-'|'*'|'/')){
            QString dbpath_trd =
                    QCoreApplication::applicationDirPath().append("/"+username+"/"+databasename+"/"+tname+"/"+tname+".trd");
            QFile file_trd(dbpath_trd);

            int index=fieldName.indexOf(setexp[0]);    //记录字段位置
            QString strAll;                     //存所有记录
            QStringList strlist;                //存每一行记录
            if(file_trd.open((QIODevice::ReadWrite))){
                QTextStream stream(&file_trd);
                strAll=stream.readAll();        //读所有记录
                strAll.remove(strAll.size()-2,2);    //删掉最后一个"\r\n",PS:一共算两个字符
                strlist=strAll.split("\r\n");
                file_trd.resize(0);             //清空原来的.trd文件
                for(int i=0;i<strlist.count();i++){
                    QString temp=strlist[i];
                    QStringList templist=temp.split(" ");
                    templist[index]=setexp[1];
                    strlist[i]=templist.join(" ");
                    stream<<strlist[i]<<"\r\n";       //重写.trd文件
                }
            }

            file_trd.close();
            qDebug() << "update done";
        }
        else{
            qDebug() << "to do update complex set & no where section";
        }
    }
    else{
        QString dbpath_trd =
                QCoreApplication::applicationDirPath().append("/"+username+"/"+databasename+"/"+tname+"/"+tname+".trd");
        QFile file_trd(dbpath_trd);

        int index=fieldName.indexOf(setexp[0]);    //记录修改字段位置
        QString strAll;                     //存所有记录
        QStringList strlist;                //存每一行记录

        if(file_trd.open((QIODevice::ReadWrite))){
            QTextStream stream(&file_trd);
            strAll=stream.readAll();        //读所有记录
            strAll.remove(strAll.size()-2,2);    //删掉最后一个"\r\n",PS:一共算两个字符
            strlist=strAll.split("\r\n");
            file_trd.resize(0);             //清空原来的.trd文件
            for(int i=0;i<strlist.count();i++){
                QString temp=strlist[i];
                QStringList templist=temp.split(" ");
                if( whereAnalysis(where,fieldName,templist) ){        //解析where条件
                    templist[index]=setexp[1];             //替换
                }
                strlist[i]=templist.join(" ");
                stream<<strlist[i]<<"\r\n";       //重写.trd文件
            }
        }
    }
    qDebug() << "to do update where section done";
}




    /*
    //确认.tic文件位置
    QString dbpath_tic =
            QCoreApplication::applicationDirPath().append("/"+username+"/"+databasename+"/"+tname+"/"+tname+".tic");
    QFile file_tic(dbpath_tic);


    if (file_trd.open(QIODevice::ReadWrite)){
        // 替换操作
        file_trd.seek(0);
        QByteArray bytes = file_trd.readAll();
        bytes.replace(sFrom, sTo.toUtf8());
        // 回写到二进制文件
        file_trd.seek(0);
        file_trd.write(bytes);
    }*/


