#include "login.h"
#include "ui_login.h"

//窗口设置
#include <QStyle>

//数据库连接
#include <QtSql/QSqlQuery>//数据库操作函数
#include <QtSql/QSqlError>//输出错误信息

#include <QMessageBox>//
#include <QSettings>//读写配置文件
#include <QtDebug>
QString username;
extern QString username;
extern QString databasename;

Login::Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);

//窗口设置
    //设置窗口不显示标题，无边框
     setWindowFlags(Qt::Window|Qt::FramelessWindowHint);

     mianw=new MainWindow;
     connect(mianw, SIGNAL(Signallogin()), this, SLOT(SlotGetback()));


//设置最小化、关闭按钮

     //获取最小化、关闭按钮图标

      QPixmap minPix = style()->standardPixmap(QStyle::SP_TitleBarMinButton);
      QPixmap closePix = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);

      ui->mintoolButton->setIcon(minPix);
      ui->closetoolButton->setIcon(closePix);
      ui->mintoolButton->setStyleSheet("bakground-color:tranparent:");
      ui->closetoolButton->setStyleSheet("bakground-color:tranparent:");

      connect(ui->mintoolButton,&QPushButton::clicked,this,&Login::showMinimized);
      connect(ui->closetoolButton,&QPushButton::clicked,this,&Login::close);

//数据库连接
      //连接数据库
         //查看当前支持的数据库的驱动
          qDebug()<<QSqlDatabase::drivers();

          QSqlDatabase DB;//创建一个数据库的文件
         //加载数据库的文件
          QString aFile="./dataBase.db";
          if(aFile.isEmpty())
          {
              qDebug()<<" 数据库文件加载失败 " ;
              return ;
          }
          //打开数据库
          DB=QSqlDatabase::addDatabase("QSQLITE");//创建QSQLITE数据库连接
          DB.setDatabaseName(aFile); //数据库名
          if(!DB.open())
          {
              //没有数据库文件则创建文件
              qDebug()<<"数据库文件打开失败";
              qDebug()<<DB.lastError().text();//输出错误信息
           }
          qDebug()<< " 打开数据库文件成功 " ;

      //从配置文件中读取用户名和密码：
          QSettings setting("config.ini",QSettings::IniFormat);
          QString account = setting.value("section/account").toString();
          QString password = setting.value("section/password").toString();
          ui->accountEdit->setText(account);
          ui->passwordEdit->setText(password);

         //用户注册，向数据库插入数据
          connect(ui->rButton,&QPushButton::clicked,this,[=](){

          //接受用户输入：
              QString account = ui->accountEdit->text();//用户账号
              QString password = ui->passwordEdit->text();//密码

          //创建自己需要使用的表格
              QSqlQuery query(DB);
              if(!query.exec("create table user(account varchar(255) primary key, password varchar(255))"))
              {
                  qDebug() << "Error: Fail to create table."<< query.lastError();
              }
              else
              {
                  qDebug() << "Table created!";
              }


          //插入数据
              QString qs = QString("insert into user(account,password) values('%1','%2')")
                      .arg(account).arg(password);

              if(query.exec(qs)) //如果插入成功
              {
                  QMessageBox::information(this,"注册","注册成功");
              }
              else
              {
                  QMessageBox::information(this,"注册","注册失败");
                  qDebug()<<query.lastError().text();//输出错误信息
                  //return;
              }

          //查看数据
              //查看数据库中有的表格的名字
              qDebug()<<"查看数据库中所有的表：";
              QStringList str_table=DB.tables();
              qDebug()<<str_table;
              //查询数据库中的数据
              qDebug()<<"查看数据库中数据";
              query.prepare ("SELECT * FROM user");
              query.exec();
              while(query.next())
              {
                  qDebug()<<QString("account:%1,password:%2").
                            arg(query.value("account").toString()).arg(query.value("password").toString());
              }

          });

      //用户登录：查询数据

          connect(ui->loginButton,&QPushButton::clicked,this,[=](){

              //接受用户输入：
               QString account = ui->accountEdit->text();//用户账号
               QString password = ui->passwordEdit->text();//密码

              //查询数据
               QSqlQuery query;//操作数据库
               QString qs = QString("select * from user where account ='%1' and password='%2'").
                       arg(account).arg(password);

               if(!query.exec(qs))//如果没有查到记录
               {
                   qDebug() << query.lastError().text();//输出错误信息
                   return;
               }

               //获取查询的数据
               if(query.next())//获取到数据
               {
                   QMessageBox::information(this,"登录","登录成功");
                   mianw->receivelogin();
                   this->hide();
                   username=account;

                   QString folderPath =QCoreApplication::applicationDirPath()+"/"+username+"/"+databasename;
                   qDebug() << folderPath;
                   QDir dir(folderPath);
                   if(!dir.exists()){
                       dir.mkpath(folderPath);
                       qDebug() << "create database success!";
                   }
                   QString dbpath = QCoreApplication::applicationDirPath().append("/ourdbms.db");
                   string path=dbpath.toStdString();

                   QFile file(dbpath);
                    QTextStream in(&file);
                   if(!file.open(QFile::ReadWrite)){
                       qDebug() << "ourdbms.db open failed!";
                   }else {
                         file.close();

                         if(!file.open(QFile::ReadWrite)){
                             qDebug() << "ourdbms.db open failed!";
                         }else {
                             QString line  = in.readLine();
                             //            qDebug() << "94 "  + line;
                             //            line.trimmed();//去掉换行符
                             qDebug() << line;
                             if((line.isNull())){
                                 QDateTime current_time = QDateTime::currentDateTime();
                                 QString currentTime = current_time.toString("yyyy-MM-dd,hh:mm:ss");
                                 QString str =  databasename + " " + folderPath + " " + currentTime + " " + username + "\r\n";
                                 file.seek(file.size());
                                 //        file.write("\n");
                                 file.write(str.toLatin1());
                                 file.close();
                             }
                             //数据库信息文件打开！
                         }

                   }

                   //connect(tw,&TestWidget::testSigna,this,&Widget::show);//显示主窗口

                   //在配置文件中记录用户账号密码
                   if(ui->checkBox->isChecked())//选中，也就是用户已经登录
                   {
                       //创建配置文件
                       QSettings setting("config.ini",QSettings::IniFormat);//配置文件在工程目录下
                       //把用户账号密码写到配置文件中
                       setting.beginGroup("section");//节开始
                       setting.setValue("account",account);
                       setting.setValue("password",password);
                       setting.endGroup();//结束
                   }
               }
               else
               {
                   QMessageBox::information(this,"登录","登录失败");
               }
          });



}

void Login::SlotGetback(){
    this->show();
    mianw->hide();
}

Login::~Login()
{
    delete ui;
}

