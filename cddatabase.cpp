#include "cddatabase.h"
#include "ui_cddatabase.h"

extern QString username;
using namespace std;
extern QString databasename;


cddatabase::cddatabase(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cddatabase)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()), this, SLOT(OnpushButton()));
    connect(ui->pushButton_2,SIGNAL(clicked()), this, SLOT(OnpushButton2()));
}

cddatabase::~cddatabase()
{
    delete ui;
}


void cddatabase::OnpushButton()
{
    //QString str = ui->textEdit->toPlainText();
    QString dbname = ui->lineEdit->text();

    QMessageBox msgBox;

    if(dbname==NULL){
        msgBox.setInformativeText("请输入要创建的database");  msgBox.exec();
    }

    else{
    createdb(dbname);
    emit SignalSendQString_9(dbname);}

}

void cddatabase::OnpushButton2()
{
    //QString str = ui->textEdit->toPlainText();
    QString dbname = ui->lineEdit_2->text();

    QMessageBox msgBox;

    if(dbname==NULL){
        msgBox.setInformativeText("请输入要删除的database");  msgBox.exec();
    }

    else{
    dropdb(dbname);

    //emit SignalSendQString_1(str);
    emit SignalSendQString_10(dbname);}

}

void cddatabase::createdb(QString dbname){
    QString dname=dbname;

    QString folderPath =QCoreApplication::applicationDirPath()+"/"+username+"/"+dname;
    qDebug() << folderPath;
    QDir dir(folderPath);
    if(!dir.exists()){
        dir.mkpath(folderPath);
        qDebug() << "create database success!";

        QString dbpath = QCoreApplication::applicationDirPath().append("/ourdbms.db");
        string path=dbpath.toStdString();
        QDateTime current_time = QDateTime::currentDateTime();
        QString currentTime = current_time.toString("yyyy-MM-dd,hh:mm:ss");

        QFile file(dbpath);
        if(!file.open(QFile::WriteOnly|QFile::Append)){
            qDebug() << "ourdbms.db open failed!";
        }else {
            //数据库信息文件打开！
            QDateTime current_time = QDateTime::currentDateTime();
            QString currentTime = current_time.toString("yyyy-MM-dd,hh:mm:ss");
            QString str =  dname + " " + folderPath + " " + currentTime + " " + username + "\r\n";
            file.seek(file.size());
    //        file.write("\n");
            file.write(str.toLatin1());
            file.close();
            QMessageBox msgBox;
            emit SignalSendQString_9(dname);//其他的cpp调用该函数的时候无法emit，但同一cpp调用的时候可以
            msgBox.setInformativeText("目标database已创建");
            msgBox.exec();
        }
    }else{
        qDebug() << "file exists!";
        QMessageBox msgBox;
        msgBox.setInformativeText("目标database已存在");
        msgBox.exec();
    }


}

void cddatabase::dropdb(QString dbname){
    QString dname=dbname;
    QString folderPath =QCoreApplication::applicationDirPath()+"/"+username+"/"+dname;
    qDebug() << folderPath;
    QDir dir;

    bool flag = false;
    if(!dir.exists(folderPath)){
        qDebug() << "dir not found!";
        QMessageBox msgBox;
        msgBox.setText("目标database不存在");
        msgBox.exec();
    }else{
        dir.setPath(folderPath);
        dir.setFilter(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
        QFileInfoList list = dir.entryInfoList();
        //数据库中存在表
        if(list.count() <= 0){
            //database null delete!
            qDebug() << "file is null!Ready to delete!";
            flag = true;

         }else{
            //文件夹不为空
            qDebug() << "database not null!";
            QMessageBox msgBox;
            msgBox.setInformativeText("您确定要删除该数据库吗？");
            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::No);
            int ret = msgBox.exec();

            switch (ret) {
              case QMessageBox::Yes:
                  // Save was clicked
                flag = true;
                  break;
              case QMessageBox::No:
                  // Don't Save was clicked
                qDebug() << "database still exists!";
                  break;
              case QMessageBox::Cancel:
                  // Cancel was clicked
                qDebug() << "database still exists!";
                  break;
              default:
                  // should never be reached
                  break;
            }

        }
    }

    if(flag){
        //删除
        dir.setPath(folderPath);
        dir.removeRecursively();
        qDebug() << "database delete success!";

        //修改数据库定义文件信息
        QString dbpath = QCoreApplication::applicationDirPath().append("/ourdbms.db");
        QFile file(dbpath);
        QTextStream in(&file);



        //读取文件
        if(!file.open(QFile::ReadWrite)){
            qDebug() << "ourdbms.db can't open!";
        }else{

            QString line  = in.readLine();
    //            qDebug() << "94 "  + line;
    //            line.trimmed();//去掉换行符
            if(!(line.isNull())){
                QStringList linelist  = line.split(" ");
                qDebug() << linelist;
                dbstruct *dbs = new dbstruct();
                qDebug() << "1";

                dbs->dbname = linelist.at(0);
                dbs->path = linelist.at(1);
                dbs->createtime = linelist.at(2);
                dbs->user = linelist.at(3);
                qDebug() << "2";

                qDebug() << dbs->dbname;
                qDebug() << dbs->path;
                qDebug() << dbs->createtime;
                qDebug() << dbs->user;

                dbvector.push_back(dbs);
                qDebug() << "3";
            }


            while(!(line.isNull())){
                qDebug() << "4";

                QString line  = in.readLine();
                qDebug() << "5";

                if(!(line.isNull())){
                    qDebug() << "6";
                    QStringList linelist = line.split(" ");
                    dbstruct *dbs = new dbstruct();

                    dbs->dbname = linelist.at(0);
                    dbs->path = linelist.at(1);
                    dbs->createtime = linelist.at(2);
                    dbs->user = linelist.at(3);

                    dbvector.push_back(dbs);
                    qDebug() << linelist;

                }else{
                    qDebug() << "current line is empty!ourdbms.db file is at the end!";
                    break;
                }
            }

            file.close();//读取完毕


            //查询删除目标数据库
            QVector<dbstruct*>::iterator iter;
    //            int count = 0;
            for(iter = dbvector.begin();iter != dbvector.end();iter++){
                if(dbname == (*iter)->dbname){
                    //目标存在
    //                    dbvector.remove(count,1);
                    dbvector.erase(iter);
                    QMessageBox msgBox;
                    msgBox.setInformativeText("目标数据库已删除");
                    msgBox.exec();
                    qDebug() << "7";
                    break;
                }
    //                count ++;
            }


            //写入
            QFile file(dbpath);
            if(!file.open(QFile::WriteOnly)){
            }else{
                //重新写入文件
                for(iter = dbvector.begin();iter != dbvector.end();iter++){
                    QString tempstr  = (*iter)->dbname + " " +(*iter)->path + " "
                            +(*iter)->createtime + " "
                            +(*iter)->user;
                    qDebug() << "8";

                    if(!(tempstr.isNull())){
                        file.write(tempstr.toLatin1());
                        file.write("\r\n");
                    }

                }
                file.close();
            }
        }
    }



}

void cddatabase::grantuser(QString uname,QString action,QString tname){

    if(action.indexOf(",") != -1) //如果有\n
    {
        action.replace(","," "); //将每个\n都替换为空
    }

    if(tname.indexOf(",") != -1) //如果有\n
    {
        tname.replace(","," "); //将每个\n都替换为空
    }


        QString aupath = QCoreApplication::applicationDirPath().append("/authorization.txt");
        string path=aupath.toStdString();

        QFile file(aupath);
        if(!file.open(QFile::WriteOnly|QFile::Append)){
            qDebug() << "authorization.txt open failed!";
        }else {
            //数据库信息文件打开！

            QString str =  username + " " + uname + " " + action + " " + tname+ "\r\n";
            file.seek(file.size());
            file.write(str.toLatin1());
            file.close();
            QMessageBox msgBox;
            //emit SignalSendQString_9(dname);//其他的cpp调用该函数的时候无法emit，但同一cpp调用的时候可以
            msgBox.setInformativeText("目标已授权");
            msgBox.exec();
        }

}

void cddatabase::revokeuser(QString uname,QString action,QString tname){
    uservector.clear();


    if(action.indexOf(",") != -1) //如果有\n
    {
        action.replace(","," "); //将每个\n都替换为空
    }

    if(tname.indexOf(",") != -1) //如果有\n
    {
        tname.replace(","," "); //将每个\n都替换为空
    }

    qDebug() <<action;
    qDebug() << tname;



        QString aupath = QCoreApplication::applicationDirPath().append("/authorization.txt");
        string path=aupath.toStdString();
        QFile file(aupath);
        QTextStream in(&file);



        //读取文件
        if(!file.open(QFile::ReadWrite)){
            qDebug() << "authorization.txt!";
        }else{

            QString line  = in.readLine();
            if(!(line.isNull())){
                QStringList linelist  = line.split(" ");
                qDebug() << linelist;
                userin *useri = new userin();


                useri->user1 = linelist.at(0);
                useri->user2 = linelist.at(1);
                for(int i=2;i<linelist.count()-1;i++){
                    useri->descrip+=linelist.at(i)+" ";
                }
                useri->descrip+=linelist.at(linelist.count()-1);

                qDebug() << useri->user1;
                qDebug() << useri->user2;
                qDebug() << useri->descrip;

                uservector.push_back(useri);
            }


            while(!(line.isNull())){

                QString line  = in.readLine();

                if(!(line.isNull())){

                    QStringList linelist = line.split(" ");
                    userin *useri = new userin();

                    useri->user1 = linelist.at(0);
                    useri->user2 = linelist.at(1);
                    for(int i=2;i<linelist.count()-1;i++){
                        useri->descrip+=linelist.at(i)+" ";
                    }
                    useri->descrip+=linelist.at(linelist.count()-1);

                    uservector.push_back(useri);
                    qDebug() << linelist;

                }else{
                    qDebug() << "authorization.txt is empty!";
                    break;
                }
            }

            file.close();//读取完毕


            //查询删除目标数据库
            QVector<userin*>::iterator iter;
    //            int count = 0;
            for(iter = uservector.begin();iter != uservector.end();iter++){
                if(uname == (*iter)->user2){
                    qDebug() << (*iter)->descrip;
                    if((*iter)->descrip.indexOf(action) != -1) //如果有\n
                    {
                        qDebug() << "1";
                        if((*iter)->descrip.indexOf(tname) != -1) //如果有\n
                        {
                            qDebug() << "2";
                        uservector.erase(iter);
                        QMessageBox msgBox;
                        msgBox.setInformativeText("权限已回收");
                        msgBox.exec();
                        qDebug() << "7";
                        break;
                        }
                    }




                }
    //                count ++;
            }


            //写入
            QFile file(aupath);
            if(!file.open(QFile::WriteOnly)){
            }else{
                //重新写入文件
                for(iter = uservector.begin();iter != uservector.end();iter++){
                    QString tempstr  = (*iter)->user1 + " " +(*iter)->user2 + " "
                            +(*iter)->descrip ;
                    qDebug() << "8";

                    if(!(tempstr.isNull())){
                        file.write(tempstr.toLatin1());
                        file.write("\r\n");
                    }

                }
                file.close();
            }
        }
uservector.clear();
}


bool cddatabase::permission(QString uname,QString action,QString tname){


//    if(action.indexOf(",") != -1) //如果有\n
//    {
//        action.replace(","," "); //将每个\n都替换为空
//    }

//    if(tname.indexOf(",") != -1) //如果有\n
//    {
//        tname.replace(","," "); //将每个\n都替换为空
//    }
//qDebug() <<uname;
//qDebug() <<action;
//qDebug() << tname;



        QString aupath = QCoreApplication::applicationDirPath().append("/authorization.txt");
        string path=aupath.toStdString();
        QFile file(aupath);
        QTextStream in(&file);



        //读取文件
        if(!file.open(QFile::ReadWrite)){
            qDebug() << "authorization.txt!";
        }else{

            QString line  = in.readLine();
            if(!(line.isNull())){
                QStringList linelist  = line.split(" ");
//                qDebug() << linelist;
                userin *useri = new userin();


                useri->user1 = linelist.at(0);
                useri->user2 = linelist.at(1);
                for(int i=2;i<linelist.count()-1;i++){
                    useri->descrip+=linelist.at(i)+" ";
                }
                useri->descrip+=linelist.at(linelist.count()-1);

//                qDebug() << useri->user1;
//                qDebug() << useri->user2;
//                qDebug() << useri->descrip;

                uservector.push_back(useri);
            }


            while(!(line.isNull())){

                QString line  = in.readLine();

                if(!(line.isNull())){

                    QStringList linelist = line.split(" ");
                    userin *useri = new userin();

                    useri->user1 = linelist.at(0);
                    useri->user2 = linelist.at(1);
                    for(int i=2;i<linelist.count()-1;i++){
                        useri->descrip+=linelist.at(i)+" ";
                    }
                    useri->descrip+=linelist.at(linelist.count()-1);

                    uservector.push_back(useri);
//                    qDebug() << linelist;

                }else{
                    //qDebug() << "authorization.txt is empty!";
                    break;
                }
            }

            file.close();//读取完毕


            //查询删除目标数据库
            QVector<userin*>::iterator iter;
    //            int count = 0;
            for(iter = uservector.begin();iter != uservector.end();iter++){
//                qDebug() <<(*iter)->user2;
//                qDebug() <<username;
//                qDebug() <<uname;
//                qDebug() <<(*iter)->user1;
//                qDebug() << (*iter)->descrip;
                if(username == (*iter)->user2){
                    if(uname == (*iter)->user1){
                    if((*iter)->descrip.indexOf(action) != -1||(*iter)->descrip.indexOf("all")!= -1) //如果有\n
                    {
                        if((*iter)->descrip.indexOf(tname) != -1||(*iter)->descrip.indexOf("any")!= -1) //如果有\n
                        {
                       return true;
                        }
                    }
                }
                }
            }


        }
        return false;

}
