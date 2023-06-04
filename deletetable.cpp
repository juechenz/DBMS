#include "deletetable.h"
#include "ui_deletetable.h"

extern QString username;
extern QString databasename;

deletetable::deletetable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::deletetable)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()), this, SLOT(OnpushButton()));
}

deletetable::~deletetable()
{
    delete ui;
}


void deletetable::OnpushButton()
{
    //QString str = ui->textEdit->toPlainText();
    QString tname = ui->lineEdit->text();
    QString where = ui->textEdit->toPlainText();
    if(where.indexOf("\n") != -1) //如果有\n
    {
        where.replace("\n",""); //将每个\n都替换为空
    }

    //emit SignalSendQString_1(str);
    emit SignalSendQString_8(tname,where);

}

void deletetable::deletetb(QString tname, QString desc,QString uname){
    QStringList attribut_list = desc.split("=");
    QString aname =attribut_list[0];
    QString condition=attribut_list[1];

//    //.tdf文件位置
//    QString dbpath_tdf =
//            QCoreApplication::applicationDirPath().append("/"+uname+"/"+databasename+"/"+tname+"/"+tname+".tdf");
//    QFile file_tdf(dbpath_tdf);

//    QString output;
//    QStringList fieldName;
//    QStringList fieldType;
//    QStringList fieldLen;
//    file_tdf.open(QFile::ReadOnly);
//    file_tdf.readLine();
//    //获取字段名、数据类型、数据长度
//    for(int i=0;!file_tdf.atEnd();i++){
//        output=file_tdf.readLine();
//        QStringList outputList=output.split(' ');
//        fieldName.append(outputList[0]);
//        fieldType.append(outputList[1]);
//        fieldLen.append(outputList[2].remove("\r\n"));
//    }
//    file_tdf.close();

    //判断字段名是否正确


//    //分割set表达式
//    QStringList setexp = set.split('=');
//    qDebug()<<setexp;

    /*
     * 通过.tdf文件判断set后的字段名是否正确
     */
    //.tdf文件位置
    QString dbpath_tdf =
            QCoreApplication::applicationDirPath().append("/"+username+"/"+databasename+"/"+tname+"/"+tname+".tdf");
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
    if(!fieldName.contains(aname)){
        qDebug()<<"指定删除字段不存在";
        return;
    }

    //where条件为空
    if(desc==NULL){
        //确认.trd文件位置
        if(!condition.contains(aname)||!condition.contains('+'|'-'|'*'|'/')){
            QString dbpath_trd =
                    QCoreApplication::applicationDirPath().append("/"+username+"/"+databasename+"/"+tname+"/"+tname+".trd");
            QFile file_trd(dbpath_trd);

            int index=fieldName.indexOf(aname);    //记录字段位置
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
                    templist[index]=condition;
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

        int index=fieldName.indexOf(aname);    //记录修改字段位置
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
                qDebug() << desc;
                qDebug() <<fieldName;
                qDebug() <<templist;
                if( !whereAnalysis_delete(desc,fieldName,templist) ){        //解析where条件
                    strlist[i]=templist.join(" ");
                    stream<<strlist[i]<<"\r\n";
                }
                       //重写.trd文件
            }
        }
    }
    qDebug() << "to do update where section done";


}
