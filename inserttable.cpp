#include "inserttable.h"
#include "ui_inserttable.h"
#include<QFile>
#include<QTextStream>
#include"QDebug.h"
#include"QMessageBox"

using namespace std;
extern QString username;
extern QString databasename;
QString uname2;

inserttable::inserttable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::inserttable)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()), this, SLOT(OnpushButton()));
}

inserttable::~inserttable()
{
    delete ui;
}


void inserttable::OnpushButton()
{
    //QString str = ui->textEdit->toPlainText();
    QString tname = ui->lineEdit->text();
    QString colname = ui->lineEdit_2->text();
    QString values = ui->textEdit->toPlainText();

    if(values.indexOf("\n") != -1) //如果有\n
    {
        values.replace("\n",""); //将每个\n都替换为空
    }


    emit SignalSendQString_5(tname,colname,values);

}

//从tic读约束，逐个判定约束是否满足，满足则写入trd
//attributeList:存储.tic中的所有属性，以及非全插入时的更新属性列表
void inserttable::inserttb(QString tname,QStringList attri_list, QStringList datalist,QString uname)
{
    //QMessageBox::warning(this,"aa","bb");
    qDebug()<<"insert process";
    QStringList attributeList;
    QStringList checkList;
    QStringList checkDefault;
    QStringList ins_datalist;    //操作后用于插入.trd的list
    int al_size=attri_list.size();
    int dl_size=datalist.size();
    qDebug()<<al_size;
    qDebug()<<dl_size;
    int tal_size;
    bool flag=true;
    uname2=uname;

    //确认.tdf文件位置
    QString dbpath_tdf =
            QCoreApplication::applicationDirPath().append("/"+uname2+"/"+databasename+"/"+tname+"/"+tname+".tdf");
    qDebug()<<dbpath_tdf;
    QFile file_tdf(dbpath_tdf);
    //确认.tic文件位置
    QString dbpath_tic =
            QCoreApplication::applicationDirPath().append("/"+uname2+"/"+databasename+"/"+tname+"/"+tname+".tic");
    QFile file_tic(dbpath_tic);
    //确认.trd文件位置
    QString dbpath_trd =
            QCoreApplication::applicationDirPath().append("/"+uname2+"/"+databasename+"/"+tname+"/"+tname+".trd");
    QFile file_trd(dbpath_trd);

    //检查文件打开和变量数目
    if(!file_tdf.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug() << tname + ".tdf open failed!";
        QMessageBox::warning(this,"wrong",tname + ".tdf open failed!");
    }
    else
    {
        qDebug()<<"file open succeed";
        //从.tdf读取全部属性，存入attributelist
        QTextStream in(&file_tdf);
        QString line=in.readLine();
        line=in.readLine();
        while(!line.isNull())
        {
            QStringList checkrow=line.split(' ');
            attributeList.append(checkrow.at(0));
            line=in.readLine();
        }
        file_tdf.close();
        //获得全部属性个数
        tal_size=attributeList.size();
        qDebug()<<tal_size;

        //检查是否输入过多属性||属性名是否输入正确
        for(int x=0;x<attri_list.size();x++)
        {
            if(al_size>tal_size)
            {
                qDebug()<<"contain non-exstent attribute";
                QMessageBox::warning(this,"wrong","contain non-exstent attribute");
                return;
            }
            else if(!attributeList.contains(attri_list.at(x)))
            {
                qDebug()<<"the name of attribute is wrong";
                QMessageBox::warning(this,"wrong","the name of attribute is wrong");
                return;
            }
        }
        //全插入,无属性或者全部属性
        if(al_size==0||al_size==tal_size)
        {
            qDebug()<<"全插入";
            if(dl_size<tal_size||dl_size>tal_size)
            {
                qDebug()<< "total insert:the number of attribute is wrong";
                QMessageBox::warning(this,"wrong","total insert:the number of attribute is wrong");
                return;
            }
        }
        //部分插入
        else{
            qDebug()<<"部分插入";
            if(dl_size<al_size||dl_size>al_size)
            {
                qDebug()<< "insert:the number of attribute is wrong";
                QMessageBox::warning(this,"wrong","insert:the number of attribute is wrong");
                return;
            }
            //更新属性列表
            qDebug()<<"更新属性列表";
            for(int i=0,j=0;i<tal_size;i++)
            {
                if(j>=al_size||attributeList.at(i)!=attri_list.at(j))
                {
                    qDebug()<<"replace: "<<i;
                    attributeList.replace(i,NULL);
                    continue;
                }
                j++;
                //qDebug()<<"j="+j;
            }
        }
    }


    if(!file_tic.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug() << tname + ".tic open failed!";
        QMessageBox::warning(this,"wrong",tname + ".tic open failed!");
    }
    else{
        qDebug()<<"file open succeed";
        QTextStream in2(&file_tic);
        QString line2=in2.readLine();
        while(!line2.isNull())
        {
            QStringList checkrow=line2.split(" ");
            checkList.append(checkrow.at(1));
            //qDebug()<<"获取checklist";
            //qDebug()<<checkrow.at(1);
            if(checkrow.at(1)=="4")
            {
                //qDebug()<<"获得defaultlist";
                //qDebug()<<checkrow.at(2);
                checkDefault.append(checkrow.at(2));
            }
            line2=in2.readLine();
        }

    }
    //检查约束
    qDebug()<<"检查约束";
    if(checkList.size()!=0){
        for(int m=0,n=0,t=0;m<tal_size;m++)
        {
            if(attributeList.at(m)==NULL)
            {
                //qDebug()<<"列 m=NULL";
                //qDebug()<<checkList.at(m);
                if(checkList.at(m)=="2"||checkList.at(m)=="3")
                {
                    flag=false;
                    qDebug()<<"column"<<m<<"can't be empty";
                }
                else if(checkList.at(m)=="4")
                {
                    //qDebug()<<"插入ins_datalist";
                    ins_datalist.insert(m,checkDefault.at(t));
                    //qDebug()<<ins_datalist.at(m);
                    t++;
                }
                else
                    ins_datalist.insert(m,NULL);
            }
            else
            {
                //unqiue:1 notnull:2 primarykey:3 defautl:4
                QString check_data=datalist.at(n);
                ins_datalist.insert(m,check_data);

                qDebug()<<attributeList.at(m);
                qDebug()<<check_data;
                qDebug()<<checkList.at(n).toInt();

                switch (checkList.at(n).toInt()) {
                case 1:
                    flag=check_unique(tname,check_data,m);
                    break;
                case 2:
                    if(check_data==NULL)
                        flag=false;
                    break;
                case 3:
                    flag=check_unique(tname,check_data,m);
                    if(check_data==NULL)
                        flag=false;
                    break;
                case 4:
                    if(check_data==NULL)
                    {
                        check_data=checkDefault.at(t);
                        t++;
                    }
                    break;
                default:
                    break;
                }
                n++;
            }

        }
    }
    else{
        ins_datalist=datalist;
    }
    //违反则终止插入
    if(!flag)
    {
        QMessageBox::warning(this,"wrong","Violation of constraints");
        qDebug()<<"违反约束条件";
        return;
    }

    //符合约束，写入.trd
    if(!file_trd.open(QFile::WriteOnly|QFile::Append)){
        qDebug() << tname + ".trd open failed!";
        QMessageBox::warning(this,"wrong",tname + ".trf open failed!");
    }else {
        qDebug()<<"file open succeed";
        QString insert_data=ins_datalist.join(" ")+ "\r\n";
        qDebug()<<insert_data;
        file_trd.write(insert_data.toLatin1());
        file_trd.close();
    }


    //    else{
    //        QTextStream in(&file_tic);
    //        QString line=in.readLine();  //逐行读取.tic的约束
    //        int i=0;   //属性位置
    //        qDebug()<<datalist.size();
    //        while(i<datalist.size()&&!line.isNull())
    //        {
    //            //读取约束
    //            qDebug()<<line;
    //            QStringList chekrow=line.split(' ');
    //            QString check=chekrow.at(1);
    //            qDebug()<<check;
    //            //读取待检查的数据
    //            QString check_data=datalist.at(i);
    //            int checkType=check.toInt();
    //            qDebug()<<check_data;

    //            //检查数据是否符合约束
    //            //unqiue:1 notnull:2 primarykey:3 defautl:4
    //            bool flag=true;
    //            switch (checkType) {
    //            case 1:
    //                flag=check_unique(tname,check_data,i);
    //                break;
    //            case 2:
    //                if(check_data==nullptr)
    //                    flag=false;
    //                break;
    //            case 3:
    //                flag=check_unique(tname,check_data,i);
    //                if(check_data==nullptr)
    //                    flag=false;
    //                break;
    //            case 4:
    //                if(check_data==nullptr)
    //                    check_data=chekrow.at(2);
    //                break;
    //            default:
    //                break;
    //            }

    //            //违反则终止插入
    //            if(!flag)
    //            {
    //                qDebug()<<"违反约束条件";
    //                return;
    //            }
    //            else{
    //                i++;
    //                line=in.readLine(); //读取下一行
    //            }
    //        }
    //    }
}

//用于检查check_data是否符合唯一性约束，index是属性位置
bool inserttable::check_unique(QString tname,QString check_data,int index)
{
    qDebug()<<"check unique";
    //确认.trd文件位置
    QString dbpath_trd =
            QCoreApplication::applicationDirPath().append("/"+uname2+"/"+databasename+"/"+tname+"/"+tname+".trd");
    QFile file_trd(dbpath_trd);

    if(!file_trd.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug() << tname + ".trd open failed!";
    }
    else {
        QTextStream in(&file_trd);
        QString line=in.readLine();  //逐行读取
        while(!line.isNull())
        {
            //比较对应位置的数据是否重合
            QStringList datarow=line.split(' ');
            QString file_data=datarow.at(index);
            if(file_data.compare(check_data)==0)
            {
                file_trd.close();
                return false;
            }
            line=in.readLine();
        }
        file_trd.close();
        return true;
    }

}
