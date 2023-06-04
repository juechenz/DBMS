#include "selecttable.h"
#include "ui_selecttable.h"

using namespace std;
extern QString username;
QString usern;
extern QString databasename;

selecttable::selecttable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::selecttable)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()), this, SLOT(OnpushButton()));
}

selecttable::~selecttable()
{
    delete ui;
}


void selecttable::OnpushButton()
{
    //QString str = ui->textEdit->toPlainText();
    QString tname = ui->lineEdit->text();
    QString colname = ui->lineEdit_2->text();
    QString where = ui->textEdit->toPlainText();

    if(where.indexOf("\n") != -1) //如果有\n
    {
        where.replace("\n",""); //将每个\n都替换为空
    }

    //emit SignalSendQString_1(str);
    emit SignalSendQString_4(tname,colname,where);

}


void selecttable::select(QString tname, QString colname, QString where,QString ordername,QString uname)
{
    usern=uname;
    if(!tname.contains(' ')){
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
        while(!file_tdf.atEnd()){
            output=file_tdf.readLine();
            QStringList outputList=output.split(' ');
            fieldName.append(outputList[0]);
            fieldType.append(outputList[1]);
            fieldLen.append(outputList[2].remove("\r\n"));
        }
        file_tdf.close();

        QStringList colList;
        if(colname==NULL){
            colList=fieldName;
        }else{
            colList=colname.split(" ");
        }
        qDebug()<<colList;

        int colIndex[colList.size()];
        if(colname!=NULL){
            for(int i=0;i<colList.size();i++){
                int index=fieldName.indexOf(colList[i]);
                if(index==-1){
                    qDebug()<<QStringList("列名输入错误");
                    return;
                }else  colIndex[i]=index;
            }
        }

        //where条件为空
        if(where==NULL){
            //确认.trd文件位置
            QString dbpath_trd =
                    QCoreApplication::applicationDirPath().append("/"+uname+"/"+databasename+"/"+tname+"/"+tname+".trd");
            QFile file_trd(dbpath_trd);

            QString strAll;                     //存所有记录
            QStringList strlist;                //存每一行记录
            QStringList resSet;                 //结果集
            resSet.append(QString::number(colList.size()));   //结果集第一个字符串记录一行的数据个数

            if(file_trd.open((QIODevice::ReadOnly))){
                QTextStream stream(&file_trd);
                strAll=stream.readAll();        //读所有记录
                strAll.remove(strAll.size()-2,2);    //删掉最后一个"\r\n",PS:一共算两个字符
                strlist=strAll.split("\r\n");
                for(int i=0;i<strlist.count();i++){
                    QString temp=strlist[i];
                    QStringList templist=temp.split(" ");
                    if(colname==NULL){
                        resSet+=templist;
                    }else{
                        for(int j=0;j<colList.size();j++){
                            resSet+=templist[colIndex[j]];             //添加至结果集
                        }
                    }
                }
            }

            file_trd.close();
            qDebug() << "select done";
            qDebug() <<resSet;
            emit SignalSendSelectSet(colList,resSet,setOrder(ordername));
            return;
        }
        else{
            QString dbpath_trd =
                    QCoreApplication::applicationDirPath().append("/"+uname+"/"+databasename+"/"+tname+"/"+tname+".trd");
            QFile file_trd(dbpath_trd);

            QString strAll;                     //存所有记录
            QStringList strlist;                //存每一行记录
            QStringList resSet;                 //结果集
            resSet.append(QString::number(fieldName.size()));   //结果集第一个字符串记录一行的数据个数

            if(file_trd.open((QIODevice::ReadOnly))){
                QTextStream stream(&file_trd);
                strAll=stream.readAll();        //读所有记录
                strAll.remove(strAll.size()-2,2);    //删掉最后一个"\r\n",PS:一共算两个字符
                strlist=strAll.split("\r\n");
                for(int i=0;i<strlist.count();i++){
                    QString temp=strlist[i];
                    QStringList templist=temp.split(" ");
                    if( whereAnalysis(where,fieldName,templist) ){        //解析where条件
                        if(colname==NULL){
                            resSet+=templist;
                        }else{
                            for(int j=0;j<colList.size();j++){
                                resSet+=templist[colIndex[j]];             //添加至结果集
                            }
                        }
                    }
                }
            }
            qDebug() <<resSet;
            emit SignalSendSelectSet(colList,resSet,setOrder(ordername));
            return;

            qDebug() << "to do select exist where section";
        }
        return;
    }
    else{
        temp.droptable("temptable",uname);
        QStringList tnameList=tname.split(' ');

        QStringList whereList=where.split(' ');
        whereList.removeAll("");
        qDebug()<<whereList;
        whereList.removeAll("&");

        QStringList joinList;
        vector<int> joinCondIndex;
        for(int i=0;i<whereList.size();i++){
            if(whereList[i].indexOf('.')!=whereList[i].lastIndexOf('.')){
                joinList.append(whereList[i]);
                //whereList.removeAt(i);
                joinCondIndex.push_back(i);
            }
        }
        while(!joinCondIndex.empty()){
            whereList.removeAt(joinCondIndex.back());
            joinCondIndex.pop_back();
        }

        qDebug()<<joinList;
        if(joinList.size()!=tnameList.size()-1){
            qDebug()<<"缺少表连接条件";
            return;
        }

        for(int i=0;i<joinList.size();i++){
            QStringList singleJoinCond=joinList[i].split('=');

        }

        /*QStringList sortedJoinList;
        if(joinList.size()==1){
            sortedJoinList=joinList;
        }else{
            for(int i=0;i<tnameList.size()-1;i++){
                for(int j=0;j<joinList.size();j++){
                    if(joinList[j].contains(tnameList[i])&&joinList[j].contains(tnameList[i+1])){
                        sortedJoinList.append(joinList[j]);
                        break;
                    }
                }
            }
        }

        if(joinList.size()!=sortedJoinList.size()){
            qDebug()<<"表连接条件错误";
            return;
        }*/

        /*
        for(int i=0;i<joinList.size();i++){
            QStringList joinTableNameList;
            QStringList temp=joinList[i].split('=');
            QStringList left=temp[0].split('.');
            QStringList right=temp[1].split('.');
            joinTableNameList.append(left[0]);
            joinTableNameList.append(right[0]);
        }
        */

        tableJoin(tnameList,joinList[0]);

        /*if(joinList.size()>1){
            tnameList.append("temptable");
            for(int i=1;i<joinList.size();i++){
                tableJoin(tnameList,"tempteble."+joinList[i]);
            }
        }*/

        select("temptable",colname,whereList.join(' '),ordername,uname);

        temp.droptable("temptable",uname);
    }
}


void selecttable::selectAll(QString tname, QString where,QString ordername,QString uname)
{
    usern=uname;
    select(tname,NULL,where,ordername,uname);
}

void selecttable::tableJoin(QStringList tnameList, /*QString colname,*/ QString where)
{
    if(where==NULL){
        qDebug()<<"无表连接条件";
        return;            //没有连接条件
    }else{
        //where处理
        QStringList conditionList=where.split(' ');
        conditionList.removeAll("");
        qDebug()<<conditionList;
        conditionList.removeAll("&");

        QMap<QString,QStringList> tnameMap;
        for(int i=0;i<tnameList.size();i++){
            //.tdf文件位置
            QString dbpath_tdf =
                    QCoreApplication::applicationDirPath().append("/"+usern+"/"+databasename+"/"+tnameList[i]+"/"+tnameList[i]+".tdf");
            QFile file_tdf(dbpath_tdf);

            QString output;
            file_tdf.open(QFile::ReadOnly);
            file_tdf.readLine();
            //获取字段名、数据类型、数据长度
            while(!file_tdf.atEnd()){
                output=file_tdf.readLine();
                QStringList outputList=output.split(' ');
                tnameMap[tnameList[i]].append(outputList[0]);   //存每个表对应的字段名
            }
            file_tdf.close();
        }

        //where解析
        QMap<QString,QString> trdContentMap;
        for(int i=0;i<tnameList.size();i++){
            QString dbpath_trd =
                    QCoreApplication::applicationDirPath().append("/"+usern+"/"+databasename+"/"+tnameList[i]+"/"+tnameList[i]+".trd");
            QFile file_trd(dbpath_trd);

            QString strAll;                     //存所有记录

            if(file_trd.open((QIODevice::ReadOnly))){
                QTextStream stream(&file_trd);
                strAll=stream.readAll();        //读所有记录
                strAll.remove(strAll.size()-2,2);    //删掉最后一个"\r\n",PS:一共算两个字符
                trdContentMap[tnameList[i]]=strAll;
            }
        }


        QStringList joinRes;                     //暂存结果集
        QStringList tempTableField;             //临时表字段
        //for(int i=0;i<conditionList.size();i++){
        if(conditionList[0/*i*/].contains('.')){
            QStringList singleCond=conditionList[0/*i*/].split('=');
            QString tnameLeft,tnameRight,fieldLeft,fieldRight;
            tnameLeft=singleCond[0].split('.')[0];
            if(singleCond[0].size()==2){
                fieldLeft=singleCond[0].split('.')[1];
            }else{
                QString removed=tnameLeft+".";
                fieldLeft=singleCond[0].remove(removed);
            }
            tnameRight=singleCond[1].split('.')[0];
            fieldRight=singleCond[1].split('.')[1];

            int indexLeft=tnameMap[tnameLeft].indexOf(fieldLeft);
            int indexRight=tnameMap[tnameRight].indexOf(fieldRight);

            for(int i=0;i<tnameMap[tnameLeft].size();i++){
                tempTableField.append(tnameLeft+"."+tnameMap[tnameLeft][i]+" char 100");
            }
            for(int i=0;i<tnameMap[tnameRight].size();i++){
                if(i!=indexRight)
                    tempTableField.append(tnameRight+"."+tnameMap[tnameRight][i]+" char 100");
            }

            if(indexLeft==-1||indexRight==-1){
                qDebug()<<"连接字段不存在";
                return;
            }

            QStringList leftLineList=trdContentMap[tnameLeft].split("\r\n");
            QStringList rightLineList=trdContentMap[tnameRight].split("\r\n");
            for(int j=0;j<leftLineList.size();j++){
                QStringList leftLine=leftLineList[j].split(' ');
                for(int k=0;k<rightLineList.size();k++){
                    QStringList rightLine=rightLineList[k].split(' ');
                    if(indexLeft>=leftLine.size()||indexRight>=rightLine.size())
                        continue;
                    if(leftLine[indexLeft]==rightLine[indexRight]){
                        rightLine.removeAt(indexRight);
                        QString temp=leftLine.join(' ');
                        temp.append(" ");
                        temp+=rightLine.join(' ');
                        joinRes.append(temp);
                    }
                }
            }
        }else{
            qDebug()<<"where未明确指定列";
        }
        //}

        //建临时表
        QString tablefield=tempTableField.join(',');

        temp.createtable("temptable",tablefield);
        qDebug()<<joinRes;
        inserttable tempinsert;
        for(int i=0;i<joinRes.size();i++){
            tempinsert.inserttb("temptable",QStringList(),joinRes[i].split(' '),usern);
        }
        //select("temptable",colname,NULL);
    }
}

QStringList selecttable::setOrder(QString ordername)
{
    QStringList order=ordername.split(" ");
    qDebug()<<order;
    order.removeAll("");
    qDebug()<<"select:ordersize";
    qDebug()<<order.size();
    if(!order.isEmpty())
        order.takeFirst();
    //order.takeFirst();
    return order;
}


