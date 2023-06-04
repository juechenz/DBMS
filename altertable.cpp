#include "altertable.h"
#include "ui_altertable.h"
#include "utils.h"

extern QString username;
extern QString databasename;

altertable::altertable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::altertable)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()), this, SLOT(OnpushButton()));
    ui->lineEdit_5->setText(NULL);
    ui->lineEdit_6->setText(databasename);
}

altertable::~altertable()
{
    delete ui;
}


void altertable::OnpushButton()
{
    //QString str = ui->textEdit->toPlainText();
    QString tname = ui->lineEdit->text();  
    QString colname = ui->lineEdit_2->text();
    QString collength = ui->lineEdit_3->text();
    QString newname = ui->lineEdit_4->text();
    QString coltype = ui->comboBox->currentText();
    QString constraint = ui->comboBox_2->currentText();
    QString action = ui->comboBox_3->currentText();
    QString defaultnum = ui->lineEdit_5->text();
    QString dbname = ui->lineEdit_6->text();

    QMessageBox msgBox;

    if(action=="add"){

    if(tname==NULL){
        msgBox.setInformativeText("请输入要创建的表名");  msgBox.exec();
    }
    else if(colname==NULL){
        msgBox.setInformativeText("请输入要创建的表的列名");  msgBox.exec();
    }else if(collength==NULL){
        msgBox.setInformativeText("请输入要创建的表的类型长度");  msgBox.exec();
    }else if(constraint!="ordinary" and defaultnum!=NULL){
        msgBox.setInformativeText("暂不支持同时输入拥有约束条件和default默认值");msgBox.exec();
    }else if(dbname==NULL){
        msgBox.setInformativeText("请输入要创建的表所在的database");   msgBox.exec();
    }
    else{

            if (defaultnum==NULL){
                atype1=coltype+" "+collength;
                if(constraint!=NULL){
                   atype1=atype1+" "+constraint;
                }

            }else {
                atype1=atype1+" "+"default "+defaultnum;
            }

            if(atype1.indexOf("primary ") != -1)
            {
                atype1.replace("primary ","primary");
            }

            if(atype1.indexOf("not ") != -1)
            {
                atype1.replace("not ","not");
            }


            //alter_add(tname,colname,atype1);
            atype1="";

            emit SignalSendQString_3(tname,colname,collength,coltype,constraint,action,defaultnum,dbname);



    }
}        else if(action=="drop"){
        if(tname==NULL){
            msgBox.setInformativeText("请输入要删除列所在的表名");  msgBox.exec();
        }
        else if(colname==NULL){
            msgBox.setInformativeText("请输入要删除的列名");  msgBox.exec();
        }else if(dbname==NULL){
            msgBox.setInformativeText("请输入要操作的表所在的database");   msgBox.exec();
        }
        else{
        //alter_drop(tname,colname);
        }
        }
        else if(action=="modify constraint"){
        if(tname==NULL){
            msgBox.setInformativeText("请输入要修改列所在的表名");  msgBox.exec();
        }
        else if(colname==NULL){
            msgBox.setInformativeText("请输入要修改的列名");  msgBox.exec();
        }else if(collength!=NULL){
            msgBox.setInformativeText("暂不支持修改约束条件时修改类型长度");  msgBox.exec();
        }else if(constraint!="ordinary" and defaultnum!=NULL){
            msgBox.setInformativeText("暂不支持同时修改修改约束条件和default默认值");msgBox.exec();
        }else if(constraint=="ordinary" and defaultnum==NULL){
            msgBox.setInformativeText("请输入要增加的约束条件或default默认值");msgBox.exec();
        }
        else if(dbname==NULL){
            msgBox.setInformativeText("请输入要修改表所在的database");   msgBox.exec();
        }
        else{

        }

    }else if(action=="modify length"){
        if(tname==NULL){
            msgBox.setInformativeText("请输入要修改列所在的表名");  msgBox.exec();
        }
        else if(colname==NULL){
            msgBox.setInformativeText("请输入要修改的列名");  msgBox.exec();
        }else if(collength==NULL){
            msgBox.setInformativeText("请输入修改后的类型长度");  msgBox.exec();
        }else if(constraint!="ordinary" or defaultnum!=NULL){
            msgBox.setInformativeText("暂不支持修改类型长度的同时修改约束条件/default默认值");msgBox.exec();
        }else if(dbname==NULL){
            msgBox.setInformativeText("请输入要修改表所在的database");   msgBox.exec();
        }
        else{

        }

    }
    else if(action=="rename"){
        if(tname==NULL){
            msgBox.setInformativeText("请输入要修改列所在的表名");  msgBox.exec();
        }
        else if(colname==NULL){
            msgBox.setInformativeText("请输入要修改列的原始名");  msgBox.exec();
        }else if(newname==NULL){
            msgBox.setInformativeText("请输入修改后的新列名");  msgBox.exec();
        }else if(dbname==NULL){
            msgBox.setInformativeText("请输入要修改表所在的database");   msgBox.exec();
        }
        else{

        }

}



}

void altertable::alter_add(QString tname, QString aname, QString atype,QString uname){
    qDebug() << atype;
    if(atype.indexOf("(") != -1) //如果有(
    {
        atype.replace("("," "); //将每个(都替换为一个空格
    }
    if(atype.indexOf(")") != -1) //如果有)
    {
        atype.replace(")",""); //将每个)都替换为空
    }
    QStringList atype_list = atype.split(" ");
    int atype_num = atype_list.count();
    QString filed;
    QString check;

    QString folderPath =QCoreApplication::applicationDirPath()+"/"+uname+"/"+databasename+"/"+tname;

    QDir dir(folderPath);

    if(!dir.exists()){
        qDebug() << "file not exists!";
        QMessageBox msgBox;
        msgBox.setInformativeText("目标table不存在");
        msgBox.exec();
    }else{
        //确认.tdf文件位置
        QString dbpath_tdf =
                QCoreApplication::applicationDirPath().append("/"+uname+"/"+databasename+"/"+tname+"/"+tname+".tdf");
        QFile file_tdf(dbpath_tdf);

        //确认.tic文件位置
        QString dbpath_tic =
                QCoreApplication::applicationDirPath().append("/"+uname+"/"+databasename+"/"+tname+"/"+tname+".tic");
        QFile file_tic(dbpath_tic);

        switch(atype_num){
        case 2:
            filed = aname + " "+QString::number(switch_type(atype_list[0]))+" "+ atype_list[1]+ "\r\n";
            break;
        case 3:
            filed = aname + " "+QString::number(switch_type(atype_list[0])) +" "+ atype_list[1]+ "\r\n";
            check = aname + " "+QString::number(switch_check(atype_list[2])) + "\r\n";
            break;
        case 4:
            filed = aname + " "+QString::number(switch_type(atype_list[0])) +" "+ atype_list[1]+ "\r\n";
            check = aname + " "+QString::number(switch_check(atype_list[2])) +" "+ atype_list[3]  + "\r\n";
            break;
        }

        //写入.tdf
        if(!file_tdf.open(QFile::WriteOnly|QFile::Append)){
            qDebug() << tname + ".tdf open failed!";
        }else {

            file_tdf.seek(file_tdf.size());
            file_tdf.write(filed.toLatin1());
            file_tdf.close();
        }

        //写入.tic文件
        if(!file_tic.open(QFile::WriteOnly|QFile::Append)){
            qDebug() << tname + ".tic open failed!";
        }else {
            file_tic.seek(file_tic.size());
            file_tic.write(check.toLatin1());
            file_tic.close();
        }
    }


}

void altertable::alter_drop(QString tname, QString aname, QString uname){



    QString folderPath =QCoreApplication::applicationDirPath()+"/"+uname+"/"+databasename+"/"+tname;
    qDebug() <<folderPath;
    QDir dir(folderPath);

    if(!dir.exists()){
        qDebug() << "file not exists!";
        QMessageBox msgBox;
        msgBox.setInformativeText("目标table不存在");
        msgBox.exec();
    }else{
        //确认.tdf文件位置
        QString dbpath_tdf =
                QCoreApplication::applicationDirPath().append("/"+uname+"/"+databasename+"/"+tname+"/"+tname+".tdf");
        QFile file_tdf(dbpath_tdf);

        //确认.tic文件位置
        QString dbpath_tic =
                QCoreApplication::applicationDirPath().append("/"+uname+"/"+databasename+"/"+tname+"/"+tname+".tic");
        QFile file_tic(dbpath_tic);

        //读取.tdf文件
        QTextStream in_tdf(&file_tdf);
        if(!file_tdf.open(QFile::ReadWrite)){
            qDebug() << ".tb can't open!";
        }else{
            QString num = in_tdf.readLine();
            num = QString::number(num.toInt()-1);
            QString line  = in_tdf.readLine();
            if(!(line.isNull())){
                QStringList linelist  = line.split(" ");
                qDebug() << linelist;
                tdf_temp *tdf = new tdf_temp();
                qDebug() << "1";

                tdf->aname = linelist.at(0);
                tdf->atype = linelist.at(1);
                tdf->alength = linelist.at(2);

                qDebug() << "2";


                tdf_vector.push_back(tdf);
                qDebug() << "3";
            }


            while(!(line.isNull())){
                qDebug() << "4";

                QString line  = in_tdf.readLine();
                qDebug() << "5";

                if(!(line.isNull())){
                    qDebug() << "6";
                    QStringList linelist = line.split(" ");
                    tdf_temp *tdf = new tdf_temp();


                    tdf->aname = linelist.at(0);
                    tdf->atype = linelist.at(1);
                    tdf->alength = linelist.at(2);
                    tdf_vector.push_back(tdf);
                    qDebug() << linelist;

                }else{
                    qDebug() << "current line is empty! .tb file is at the end!";
                    break;
                }
            }
            file_tdf.close();//读取完毕

            //查询字段名
            QVector <tdf_temp*>::iterator iter_tdf;
            for(iter_tdf = tdf_vector.begin();iter_tdf != tdf_vector.end();iter_tdf++){
                if(aname == (*iter_tdf)->aname){
                    tdf_vector.erase(iter_tdf);
                    break;
                }
            }

            //写入
            QFile file_tdf(dbpath_tdf);
            if(!file_tdf.open(QFile::WriteOnly)){
            }else{
                //重新写入文件
                file_tdf.write(num.toLatin1());
                file_tdf.write("\r\n");
                for(iter_tdf = tdf_vector.begin();iter_tdf != tdf_vector.end();iter_tdf++){
                    QString tempstr  = (*iter_tdf)->aname + " " +(*iter_tdf)->atype + " "
                            +(*iter_tdf)->alength;

                    if(!(tempstr.isNull())){
                        file_tdf.write(tempstr.toLatin1());
                        file_tdf.write("\r\n");
                    }

                }
                file_tdf.close();
            }

        }
        tdf_vector.clear();//清除vector容器中的数据

        //读取.tic文件
        QTextStream in_tic(&file_tic);
        if(!file_tic.open(QFile::ReadWrite)){
            qDebug() << ".tb can't open!";
        }else{

            QString line  = in_tic.readLine();
            if(!(line.isNull())){
                QStringList linelist  = line.split(" ");
                qDebug() << linelist;
                tic_temp *tic = new tic_temp();
                qDebug() << "1";
                if(linelist.count()==3){
                tic->aname = linelist.at(0);
                tic->acheck = linelist.at(1);
                tic->default_value = linelist.at(2);
                }else{
                    tic->aname = linelist.at(0);
                    tic->acheck = linelist.at(1);
                    tic->default_value = "";
                }
                qDebug() << "2";


                tic_vector.push_back(tic);
                qDebug() << "3";
            }


            while(!(line.isNull())){
                qDebug() << "4";

                QString line  = in_tic.readLine();
                qDebug() << "5";

                if(!(line.isNull())){
                    qDebug() << "6";
                    QStringList linelist = line.split(" ");
                    tic_temp *tic = new tic_temp();
                    if(linelist.count()==3){
                    tic->aname = linelist.at(0);
                    tic->acheck = linelist.at(1);
                    tic->default_value = linelist.at(2);
                    }else{
                        tic->aname = linelist.at(0);
                        tic->acheck = linelist.at(1);
                        tic->default_value = "";
                    }
                    tic_vector.push_back(tic);
                    qDebug() << linelist;

                }else{
                    qDebug() << "current line is empty! .tb file is at the end!";
                    break;
                }
            }
            file_tic.close();//读取完毕

            //查询字段名
            QVector <tic_temp*>::iterator iter_tic;
            for(iter_tic = tic_vector.begin();iter_tic != tic_vector.end();iter_tic++){
                if(aname == (*iter_tic)->aname){
                    tic_vector.erase(iter_tic);
                    break;
                }
            }

            //写入
            QFile file_tic(dbpath_tic);
            QString tempstr;
            if(!file_tic.open(QFile::WriteOnly)){
            }else{
                //重新写入文件
                for(iter_tic = tic_vector.begin();iter_tic != tic_vector.end();iter_tic++){
                    if((*iter_tic)->default_value==""){
                        tempstr  = (*iter_tic)->aname + " " +(*iter_tic)->acheck;
                    }else{
                        tempstr  = (*iter_tic)->aname + " " +(*iter_tic)->acheck + " "
                                +(*iter_tic)->default_value;
                    }
                    if(!(tempstr.isNull())){
                        file_tic.write(tempstr.toLatin1());
                        file_tic.write("\r\n");
                    }

                }
                file_tic.close();
                tic_vector.clear();

                QMessageBox msgBox;
                msgBox.setInformativeText("目标列已删除");
                msgBox.exec();
            }

        }

    }

}

void altertable::alter_rename(QString tname,QString oldname,QString newname,QString uname){

    QString folderPath =QCoreApplication::applicationDirPath()+"/"+uname+"/"+databasename+"/"+tname;
    QDir dir(folderPath);

    if(!dir.exists()){
        qDebug() << "file not exists!";
        QMessageBox msgBox;
        msgBox.setInformativeText("目标table不存在");
        msgBox.exec();
    }else{
        //确认.tdf文件位置
        QString dbpath_tdf =
                QCoreApplication::applicationDirPath().append("/"+uname+"/"+databasename+"/"+tname+"/"+tname+".tdf");
        QFile file_tdf(dbpath_tdf);

        //确认.tic文件位置
        QString dbpath_tic =
                QCoreApplication::applicationDirPath().append("/"+uname+"/"+databasename+"/"+tname+"/"+tname+".tic");
        QFile file_tic(dbpath_tic);

        //读取.tdf文件
        QTextStream in_tdf(&file_tdf);
        if(!file_tdf.open(QFile::ReadWrite)){
            qDebug() << ".tb can't open!";
        }else{
            QString num = in_tdf.readLine();
            QString line  = in_tdf.readLine();
            if(!(line.isNull())){
                QStringList linelist  = line.split(" ");
                qDebug() << linelist;
                tdf_temp *tdf = new tdf_temp();
                qDebug() << "1";

                tdf->aname = linelist.at(0);
                tdf->atype = linelist.at(1);
                tdf->alength = linelist.at(2);

                qDebug() << "2";


                tdf_vector.push_back(tdf);
                qDebug() << "3";
            }


            while(!(line.isNull())){
                qDebug() << "4";

                QString line  = in_tdf.readLine();
                qDebug() << "5";

                if(!(line.isNull())){
                    qDebug() << "6";
                    QStringList linelist = line.split(" ");
                    tdf_temp *tdf = new tdf_temp();


                    tdf->aname = linelist.at(0);
                    tdf->atype = linelist.at(1);
                    tdf->alength = linelist.at(2);
                    tdf_vector.push_back(tdf);
                    qDebug() << linelist;

                }else{
                    qDebug() << "current line is empty! .tb file is at the end!";
                    break;
                }
            }
            file_tdf.close();//读取完毕


            //查询字段名
            QVector <tdf_temp*>::iterator iter_tdf;
            for(iter_tdf = tdf_vector.begin();iter_tdf != tdf_vector.end();iter_tdf++){
                if(oldname == (*iter_tdf)->aname){
                    (*iter_tdf)->aname=newname;
                    break;
                }
            }

            //写入
            QFile file_tdf(dbpath_tdf);
            if(!file_tdf.open(QFile::WriteOnly)){
            }else{
                //重新写入文件
                file_tdf.write(num.toLatin1());
                file_tdf.write("\r\n");
                for(iter_tdf = tdf_vector.begin();iter_tdf != tdf_vector.end();iter_tdf++){
                    QString tempstr  = (*iter_tdf)->aname + " " +(*iter_tdf)->atype + " "
                            +(*iter_tdf)->alength;

                    if(!(tempstr.isNull())){
                        file_tdf.write(tempstr.toLatin1());
                        file_tdf.write("\r\n");
                    }

                }
                file_tdf.close();
            }

        }
        tdf_vector.clear();//清除vector容器中的数据

        //读取.tic文件
        QTextStream in_tic(&file_tic);
        if(!file_tic.open(QFile::ReadWrite)){
            qDebug() << ".tb can't open!";
        }else{

            QString line  = in_tic.readLine();
            if(!(line.isNull())){
                QStringList linelist  = line.split(" ");
                qDebug() << linelist;
                tic_temp *tic = new tic_temp();
                qDebug() << "1";
                if(linelist.count()==3){
                tic->aname = linelist.at(0);
                tic->acheck = linelist.at(1);
                tic->default_value = linelist.at(2);
                }else{
                    tic->aname = linelist.at(0);
                    tic->acheck = linelist.at(1);
                    tic->default_value = "";
                }
                qDebug() << "2";


                tic_vector.push_back(tic);
                qDebug() << "3";
            }


            while(!(line.isNull())){
                qDebug() << "4";

                QString line  = in_tic.readLine();
                qDebug() << "5";

                if(!(line.isNull())){
                    qDebug() << "6";
                    QStringList linelist = line.split(" ");
                    tic_temp *tic = new tic_temp();
                    if(linelist.count()==3){
                    tic->aname = linelist.at(0);
                    tic->acheck = linelist.at(1);
                    tic->default_value = linelist.at(2);
                    }else{
                        tic->aname = linelist.at(0);
                        tic->acheck = linelist.at(1);
                        tic->default_value = "";
                    }
                    tic_vector.push_back(tic);
                    qDebug() << linelist;

                }else{
                    qDebug() << "current line is empty! .tb file is at the end!";
                    break;
                }
            }
            file_tic.close();//读取完毕

            //查询字段名
            QVector <tic_temp*>::iterator iter_tic;
            for(iter_tic = tic_vector.begin();iter_tic != tic_vector.end();iter_tic++){
                if(oldname == (*iter_tic)->aname){
                    (*iter_tic)->aname=newname;
                    break;
                }
            }

            //写入
            QFile file_tic(dbpath_tic);
            QString tempstr;
            if(!file_tic.open(QFile::WriteOnly)){
            }else{
                //重新写入文件
                for(iter_tic = tic_vector.begin();iter_tic != tic_vector.end();iter_tic++){
                    if((*iter_tic)->default_value==""){
                        tempstr  = (*iter_tic)->aname + " " +(*iter_tic)->acheck;
                    }else{
                        tempstr  = (*iter_tic)->aname + " " +(*iter_tic)->acheck + " "
                                +(*iter_tic)->default_value;
                    }
                    if(!(tempstr.isNull())){
                        file_tic.write(tempstr.toLatin1());
                        file_tic.write("\r\n");
                    }

                }
                file_tic.close();
                tic_vector.clear();

                QMessageBox msgBox;
                msgBox.setInformativeText("目标列已删除");
                msgBox.exec();
                }

            }
        }
}

void altertable::alter_modify_typelen(QString tname, QString aname, QString atype,QString uname){
    qDebug() << atype;
    if(atype.indexOf("(") != -1) //如果有(
    {
        atype.replace("("," "); //将每个(都替换为一个空格
    }
    if(atype.indexOf(")") != -1) //如果有)
    {
        atype.replace(")",""); //将每个)都替换为空
    }
    QStringList atype_list = atype.split(" ");
    QString alength = atype_list[1];
    qDebug() << atype_list[1];
    QString folderPath =QCoreApplication::applicationDirPath()+"/"+uname+"/"+databasename+"/"+tname;
    QDir dir(folderPath);

    if(!dir.exists()){
        qDebug() << "file not exists!";
        QMessageBox msgBox;
        msgBox.setInformativeText("目标table不存在");
        msgBox.exec();
    }else{
        //确认.tdf文件位置
        QString dbpath_tdf =
                QCoreApplication::applicationDirPath().append("/"+uname+"/"+databasename+"/"+tname+"/"+tname+".tdf");
        QFile file_tdf(dbpath_tdf);


        //读取.tdf文件
        QTextStream in_tdf(&file_tdf);
        if(!file_tdf.open(QFile::ReadWrite)){
            qDebug() << ".tb can't open!";
        }else{
            QString num = in_tdf.readLine();
            QString line  = in_tdf.readLine();
            if(!(line.isNull())){
                QStringList linelist  = line.split(" ");
                qDebug() << linelist;
                tdf_temp *tdf = new tdf_temp();
                qDebug() << "1";

                tdf->aname = linelist.at(0);
                tdf->atype = linelist.at(1);
                tdf->alength = linelist.at(2);

                qDebug() << "2";


                tdf_vector.push_back(tdf);
                qDebug() << "3";
            }


            while(!(line.isNull())){
                qDebug() << "4";

                QString line  = in_tdf.readLine();
                qDebug() << "5";

                if(!(line.isNull())){
                    qDebug() << "6";
                    QStringList linelist = line.split(" ");
                    tdf_temp *tdf = new tdf_temp();


                    tdf->aname = linelist.at(0);
                    tdf->atype = linelist.at(1);
                    tdf->alength = linelist.at(2);
                    tdf_vector.push_back(tdf);
                    qDebug() << linelist;

                }else{
                    qDebug() << "current line is empty! .tb file is at the end!";
                    break;
                }
            }
            file_tdf.close();//读取完毕

            //查询字段名
            QVector <tdf_temp*>::iterator iter_tdf;
            for(iter_tdf = tdf_vector.begin();iter_tdf != tdf_vector.end();iter_tdf++){
                if(aname == (*iter_tdf)->aname){
                    (*iter_tdf)->alength=alength;
                    break;
                }
            }

            //写入
            QFile file_tdf(dbpath_tdf);
            if(!file_tdf.open(QFile::WriteOnly)){
            }else{
                //重新写入文件
                file_tdf.write(num.toLatin1());
                file_tdf.write("\r\n");
                for(iter_tdf = tdf_vector.begin();iter_tdf != tdf_vector.end();iter_tdf++){
                    QString tempstr  = (*iter_tdf)->aname + " " +(*iter_tdf)->atype + " "
                            +(*iter_tdf)->alength;

                    if(!(tempstr.isNull())){
                        file_tdf.write(tempstr.toLatin1());
                        file_tdf.write("\r\n");
                    }

                }
                file_tdf.close();
            }

        }
        tdf_vector.clear();//清除vector容器中的数据
    }

}

void altertable::alter_modify_tic(QString tname, QString aname, QString constraint,QString uname){
    //需要将constraint中的约束语句拿出来放在acheck中
    QString check;
    if(constraint.indexOf("default") != -1) //如果有\n
    {
        constraint.replace("default ","");
        check=aname + " " + QString::number(4) + " "+ constraint + " " + "\r\n";
    }else{
        check=aname +" "+QString::number(switch_check(constraint))+ " " + "\r\n";
    }

    QString folderPath =QCoreApplication::applicationDirPath()+"/"+uname+"/"+databasename+"/"+tname;
    QDir dir(folderPath);

    if(!dir.exists()){
        qDebug() << "file not exists!";
        QMessageBox msgBox;
        msgBox.setInformativeText("目标table不存在");
        msgBox.exec();
    }else{
        //确认.tic文件位置
        QString dbpath_tic =
                QCoreApplication::applicationDirPath().append("/"+uname+"/"+databasename+"/"+tname+"/"+tname+".tic");
        QFile file_tic(dbpath_tic);

        //写入.tic文件
        if(!file_tic.open(QFile::WriteOnly|QFile::Append)){
            qDebug() << tname + ".tic open failed!";
        }else {
            file_tic.seek(file_tic.size());
            file_tic.write(check.toLatin1());
            file_tic.close();
        }
    }
}
