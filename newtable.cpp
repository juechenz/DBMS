#include "newtable.h"
#include "ui_newtable.h"
#include "utils.h"

using namespace std;
extern QString username;
extern QString databasename;

newtable::newtable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::newtable)
{

    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()), this, SLOT(OnpushButton()));
    connect(ui->pushButton_2,SIGNAL(clicked()), this, SLOT(OnpushButton2()));
     ui->lineEdit_5->setText(NULL);
     ui->lineEdit_6->setText(databasename);
     ui->lineEdit_7->setText(databasename);
     counts=0;
}

newtable::~newtable()
{
    delete ui;
}



void newtable::OnpushButton()
{
    //QString str = ui->textEdit->toPlainText();
    QString tname = ui->lineEdit->text();
    QString colname = ui->lineEdit_2->text();
    QString collength = ui->lineEdit_3->text();
    QString coltype = ui->comboBox->currentText();
    QString constraint = ui->comboBox_2->currentText();
    QString defaultnum = ui->lineEdit_5->text();
    QString dbname = ui->lineEdit_6->text();
     qDebug() <<defaultnum;
     qDebug() <<"1";
     qDebug() <<QString::number(counts);
     qDebug() <<tablenum;
     QMessageBox msgBox;

     if(tname==NULL){
         msgBox.setInformativeText("请先输入要创建的表名");  msgBox.exec();
     }
     else if(tablenum==NULL){
         msgBox.setInformativeText("请先输入要创建的表共有几列");   msgBox.exec();
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

         if(desc1.contains(colname)){
             msgBox.setInformativeText("列名不能重复，请重新输入");   msgBox.exec();
         }else{
             if(counts<tablenum.toInt()) {
                 qDebug() <<"2";

             if (defaultnum==NULL){
                 qDebug() <<"3";

                 //emit SignalSendQString_2(tname,colname,collength,coltype,constraint,dbname);

                 if(counts>0) desc1=desc1+",";
                 desc1=desc1+colname+" "+coltype;
                 if(constraint!="ordinary"){
                     if (collength==NULL){
                         desc1=desc1+" "+constraint;
                         counts=counts+1;

                     }else if(collength!=NULL){
                         desc1=desc1+" "+collength+" "+constraint;
                         counts=counts+1;
                     }
                 }else if(constraint=="ordinary"){
                         if(collength!=NULL){
                             desc1=desc1+" "+collength;
                           counts=counts+1;

                         }else counts=counts+1;

                 }
                  qDebug() <<desc1;
                  //createtable(tname,desc1);
                  QMessageBox msgBox;
                  msgBox.setInformativeText("您已创建"+QString::number(counts)+"列，还差"+
                                            QString::number(tablenum.toInt()-counts)+"列的属性值需要创建");
                  msgBox.exec();

             }

             else {
                 qDebug() <<"4";

                 //emit SignalSendQString_11(tname,colname,collength,coltype,constraint,defaultnum,dbname);
                 if(counts>0) desc1=desc1+",";
                 desc1=desc1+colname+" "+coltype;
                 if (collength==NULL){
                     desc1=desc1+" "+"default "+defaultnum;
                     counts=counts+1;

                 }else if(collength!=NULL){
                     desc1=desc1+" "+collength+" "+"default "+defaultnum;
                     counts=counts+1;
                 }
                  qDebug() <<desc1;
                  //createtable(tname,desc1);
                  QMessageBox msgBox;
                  msgBox.setInformativeText("您已创建"+QString::number(counts)+"列，还差"+
                                            QString::number(tablenum.toInt()-counts)+"列的属性值需要创建");
                  msgBox.exec();

                }
             }



             if(counts==tablenum.toInt()){
                 databasename=dbname;

                 if(desc1.indexOf("primary ") != -1)
                 {
                     desc1.replace("primary ","primary");
                 }

                 if(desc1.indexOf("not ") != -1)
                 {
                     desc1.replace("not ","not");
                 }

                 createtable(tname,desc1);
                 desc1="";
             }
         }




     }






}

void newtable::OnpushButton2()
{
    //QString str = ui->textEdit->toPlainText();
    QString tname = ui->lineEdit_4->text();
    QString dbname = ui->lineEdit_7->text();
    databasename=dbname;

    QMessageBox msgBox;

    if(tname==NULL){
        msgBox.setInformativeText("请输入要创建的表名");  msgBox.exec();
    }
    else if(dbname==NULL){
        msgBox.setInformativeText("请输入要创建的表所在的database");   msgBox.exec();
    }else{
        emit SignalSendQString_7(tname);
        //droptable(tname);
    }


}

void newtable::createtable(QString tname,QString desc)
{
    if(desc.indexOf("(") != -1) //如果有(
    {
        desc.replace("("," "); //将每个(都替换为一个空格
    }
    if(desc.indexOf(")") != -1) //如果有)
    {
        desc.replace(")",""); //将每个)都替换为空
    }
    qDebug() << desc;
    QString folderPath =QCoreApplication::applicationDirPath()+"/"+username+"/"+databasename+"/"+tname;
    int attribute_num =0;
    int filed_num =0;
    qDebug() << folderPath;
    QDir dir(folderPath);
    if(!dir.exists()){
        dir.mkpath(folderPath);
        qDebug() << "create table success!";

    //确认.tdf文件位置
    QString dbpath_tdf =
            QCoreApplication::applicationDirPath().append("/"+username+"/"+databasename+"/"+tname+"/"+tname+".tdf");
    QFile file_tdf(dbpath_tdf);

    //确认.tic文件位置
    QString dbpath_tic =
            QCoreApplication::applicationDirPath().append("/"+username+"/"+databasename+"/"+tname+"/"+tname+".tic");
    QFile file_tic(dbpath_tic);

    //确认.trd文件位置并创建
    QString dbpath_trd =
            QCoreApplication::applicationDirPath().append("/"+username+"/"+databasename+"/"+tname+"/"+tname+".trd");
    QFile file_trd(dbpath_trd);
    if(!file_trd.open(QFile::WriteOnly|QFile::Append)){
        qDebug() << tname + ".tdf open failed!";
    }else {
        file_trd.close();
    }

    //unqiue:1 notnull:2 primarykey:3 defautl
    //“第一列属性数量 第一个属性名 第一个属性类型
    QString filed;
    QString check;
    QStringList attribut_list = desc.split(",");
    QStringList filed_list;
    attribute_num = attribut_list.count();
    QString filed_name,filed_type,filed_length,filed_check;



    if(!file_tdf.open(QFile::WriteOnly|QFile::Append)){
        qDebug() << tname + ".tdf open failed!";
    }else {
        QString num = QString::number(attribute_num) + "\r\n";
        file_tdf.seek(file_tdf.size());
        file_tdf.write(num.toLatin1());
        file_tdf.close();
    }

    for (int i=0;i<attribute_num;i++) {

        filed_list=attribut_list[i].split(" ");

        QMessageBox msgBox;

        filed_name=filed_list[0];
        filed_type=filed_list[1];
        filed_length=filed_list[2];
        filed_num=filed_list.count();
        qDebug() <<filed_name;
        qDebug() <<QString::number(desc.indexOf(filed_name));
        qDebug() <<QString::number(desc.lastIndexOf(filed_name));
         if(desc.indexOf(filed_name) != desc.lastIndexOf(filed_name)){
            msgBox.setInformativeText("列名不能重复，请重新输入");   msgBox.exec();
            dir.setPath(folderPath);
            dir.removeRecursively();
            i=attribute_num;
        }else{
             switch (filed_num) {
             case 3:
                 filed= filed_name + " " + QString::number(switch_type(filed_type))+ " " + filed_length + "\r\n";

                 //写入.tdf文件
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
                 break;
             case 4:
                 filed_check=filed_list[3];
                 check = filed_name +" " + QString::number(switch_check(filed_check))+ "\r\n";
                 filed = filed_name +" " + QString::number(switch_type(filed_type)) + " " + filed_length +"\r\n";

                 //写入.tdf文件
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
                 break;
             case 5:
                 check = filed_name +" " + QString::number(4) +" "+ filed_list[4]+ "\r\n";
                 filed = filed_name +" " + QString::number(switch_type(filed_type)) +" " +filed_length+ "\r\n";

                 //写入.tdf文件
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
                 break;
             case 6:
                 check = filed_name +" " + QString::number(4) +" "+ filed_list[4]+ "\r\n";

                 //写入.tdf文件
                 if(!file_tdf.open(QFile::WriteOnly|QFile::Append)){
                     qDebug() << tname + ".tdf open failed!";
                 }else {
                     file_tdf.seek(file_tdf.size());
                     file_tdf.write(filed.toLatin1());
                     file_tdf.close();
                 }
             }

//             //写入.tdf文件
//             if(!file_tdf.open(QFile::WriteOnly|QFile::Append)){
//                 qDebug() << tname + ".tdf open failed!";
//             }else {
//                 file_tdf.seek(file_tdf.size());
//                 file_tdf.write(filed.toLatin1());
//                 file_tdf.close();
//             }

//             //写入.tic文件
//             if(!file_tic.open(QFile::WriteOnly|QFile::Append)){
//                 qDebug() << tname + ".tic open failed!";
//             }else {
//                 file_tic.seek(file_tic.size());
//                 file_tic.write(check.toLatin1());
//                 file_tic.close();
//             }

         }
         check="";
    }

    if(desc.indexOf(filed_name) == desc.lastIndexOf(filed_name)){
    //创建.tb文件
    QString dbpath = QCoreApplication::applicationDirPath().append("/"+username+"/"+databasename+"/"+databasename+".tb");
    QFile file(dbpath);
    if(!file.open(QFile::WriteOnly|QFile::Append)){
        qDebug() << tname+".tb open failed!";
    }else {
        //数据库信息文件打开！
        QDateTime current_time = QDateTime::currentDateTime();
        QString currentTime = current_time.toString("yyyy-MM-dd,hh:mm:ss");
        QString str_tb = tname + " " + folderPath + " " + currentTime + " " + username + " " + databasename + "\r\n";
        file.seek(file.size());
        file.write(str_tb.toLatin1());
        file.close();
        QMessageBox msgBox;
        if(tname!="temptable"){
            msgBox.setInformativeText("目标table已创建");
            msgBox.exec();
        }
    }


    }


    }

    else{
        qDebug() << "file exists!";
        QMessageBox msgBox;
        if(tname!="temptable"){
            msgBox.setInformativeText("目标table已存在");
            msgBox.exec();
        }
    }


}

void newtable::droptable(QString tname,QString uname){

    QString folderPath =QCoreApplication::applicationDirPath()+"/"+uname+"/"+databasename+"/"+tname;
    qDebug() << folderPath;
    QDir dir;

    bool flag = false;
    if(!dir.exists(folderPath)){
        qDebug() << "dir not found!";
        if(tname!="temptable"){
            QMessageBox msgBox;
            msgBox.setText("目标table不存在");
            msgBox.exec();
        }
    }else{
        dir.setPath(folderPath);
        dir.setFilter(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
        QFileInfoList list = dir.entryInfoList();
        //文件夹不为空
        if(tname!="temptable"){
        QMessageBox msgBox;
            msgBox.setInformativeText("您确定要删除该表吗？");
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
                qDebug() << "table still exists!";
                  break;
              case QMessageBox::Cancel:
                  // Cancel was clicked
                qDebug() << "table still exists!";
                  break;
              default:
                  // should never be reached
                  break;
            }
        }else flag=true;

    }

    if(flag){
        //删除
        dir.setPath(folderPath);
        dir.removeRecursively();
        qDebug() << "table delete success!";

        QString dbpath = QCoreApplication::applicationDirPath().append("/"+uname+"/"+databasename+"/"+databasename+".tb");
        QFile file(dbpath);
        QTextStream in(&file);



        //读取文件
        if(!file.open(QFile::ReadWrite)){
            qDebug() << ".tb can't open!";
        }else{

            QString line  = in.readLine();
    //            qDebug() << "94 "  + line;
    //            line.trimmed();//去掉换行符
            if(!(line.isNull())){
                QStringList linelist  = line.split(" ");
                qDebug() << linelist;
                tbinfostruct *tbi = new tbinfostruct();
                qDebug() << "1";

                tbi->tname = linelist.at(0);
                tbi->path = linelist.at(1);
                tbi->createtime = linelist.at(2);
                tbi->user = linelist.at(3);
                tbi->dbname = linelist.at(4);
                qDebug() << "2";


                tbvector.push_back(tbi);
                qDebug() << "3";
            }



            while(!(line.isNull())){
                qDebug() << "4";

                QString line  = in.readLine();
                qDebug() << "5";

                if(!(line.isNull())){
                    qDebug() << "6";
                    QStringList linelist = line.split(" ");
                    tbinfostruct *tbi = new tbinfostruct();


                    tbi->tname = linelist.at(0);
                    tbi->path = linelist.at(1);
                    tbi->createtime = linelist.at(2);
                    tbi->user = linelist.at(3);
                    tbi->dbname = linelist.at(4);

                    tbvector.push_back(tbi);
                    qDebug() << linelist;

                }else{
                    qDebug() << "current line is empty! .tb file is at the end!";
                    break;
                }
            }

            file.close();//读取完毕


            //查询删除目标表
            QVector <tbinfostruct*>::iterator iter;
    //            int count = 0;
            for(iter = tbvector.begin();iter != tbvector.end();iter++){
                if(tname == (*iter)->tname){
                    //目标存在
    //                    dbvector.remove(count,1);
                    tbvector.erase(iter);
                    if(tname!="temptable"){
                        QMessageBox msgBox;
                        msgBox.setInformativeText("目标table已删除");
                        msgBox.exec();
                    }
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
                for(iter = tbvector.begin();iter != tbvector.end();iter++){
                    QString tempstr  = (*iter)->tname + " " +(*iter)->path + " "
                            +(*iter)->createtime + " "
                            +(*iter)->user+ " "
                            +(*iter)->dbname;

                    if(!(tempstr.isNull())){
                        file.write(tempstr.toLatin1());
                        file.write("\r\n");
                    }

                }
                file.close();
            }
            tbvector.clear();
        }
    }

    //修改数据库定义文件信息


}

void newtable::on_pushButton_3_clicked()
{
    tablenum = ui->lineEdit_8->text();
    QString tname = ui->lineEdit->text();
    QMessageBox msgBox;
    if(tname==NULL){
        msgBox.setInformativeText("请输入要创建的表名");  msgBox.exec();
    }
    else if(tablenum==NULL){
        msgBox.setInformativeText("请输入要创建的表共有几列");   msgBox.exec();
    }else{
        msgBox.setInformativeText("请接下来根据您输入的列数量来分别输入每一列的属性");   msgBox.exec();
    }




//    int i,j,k,w,a;
//        string ch[] = {"A", "B", "C", "D", "E", "F"};
//        a=QInputDialog::getInt(this, tr("input"), tr("table列的数量"));

//        for (k = 0; k < a; k++)
//        {
//            i = QInputDialog::getInt(this, tr("input"), tr("i"));
//            j = QInputDialog::getInt(this, tr("input"), tr("j"));
//            w = QInputDialog::getInt(this, tr("input"), tr("w"));

//        }
}
