#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegExp>
#include <QRegularExpression>
#include <regex>
#include <cstring>
#include "string.h"

QString filepath0;
extern QString username;
extern QString databasename;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle ( tr ( "myDBMS" ) );
    nt = new newtable;
    at = new altertable;
    it = new inserttable;
    st = new selecttable;
    ut = new updatetable;
    det = new deletetable;
    cddb = new cddatabase;



    //connect(st,SIGNAL(sendOrder(QStringList)),this,SLOT(recOrder(QStringList)));


    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(OnpushButton2()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(OnpushButton3()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(OnpushButton4()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(OnpushButton5()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(OnpushButton6()));

    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(OnpushButton8()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(OnpushButton9()));


    connect(nt, SIGNAL(SignalSendQString_2(QString,QString,QString,QString,QString,QString)), this, SLOT(SlotGetQString_2(QString,QString,QString,QString,QString,QString)));
    connect(at, SIGNAL(SignalSendQString_3(QString,QString,QString,QString,QString,QString,QString,QString)), this, SLOT(SlotGetQString_3(QString,QString,QString,QString,QString,QString,QString,QString)));
    connect(st, SIGNAL(SignalSendQString_4(QString,QString,QString)), this, SLOT(SlotGetQString_4(QString,QString,QString)));
    connect(gra.da.getST(), SIGNAL(SignalSendSelectSet(QStringList,QStringList,QStringList)), this, SLOT(SlotGetSelectSet(QStringList,QStringList,QStringList)));
    connect(it, SIGNAL(SignalSendQString_5(QString,QString,QString)), this, SLOT(SlotGetQString_5(QString,QString,QString)));
    connect(ut, SIGNAL(SignalSendQString_6(QString,QString,QString)), this, SLOT(SlotGetQString_6(QString,QString,QString)));
    connect(nt, SIGNAL(SignalSendQString_7(QString)), this, SLOT(SlotGetQString_7(QString)));
    connect(det, SIGNAL(SignalSendQString_8(QString,QString)), this, SLOT(SlotGetQString_8(QString,QString)));
    connect(cddb, SIGNAL(SignalSendQString_9(QString)), this, SLOT(SlotGetQString_9(QString)));
    connect(cddb, SIGNAL(SignalSendQString_10(QString)), this, SLOT(SlotGetQString_9(QString)));
    connect(nt, SIGNAL(SignalSendQString_11(QString,QString,QString,QString,QString,QString,QString)), this, SLOT(SlotGetQString_11(QString,QString,QString,QString,QString,QString,QString)));
    connect(cddb, SIGNAL(SignalSenddbname(QString)), this, SLOT(SlotGetdbname(QString)));

    //    //设置表格的列数，必须要先设置，不然表格显示不出来
    //    ui->tableWidget->setColumnCount(4);
    //    //建立表头
    //    QStringList header;
    //    header << "col0" << "col1" << "col2" << "col3";
    //    ui->tableWidget->setHorizontalHeaderLabels(header);
    //设置表头显示模式,这里设置的是拉伸模式
    //ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // 4 转到当前目录下
    rootDir.cd(QDir::currentPath()+"/debug/1/"+databasename);
    //    qDebug() << "-------------------------------------------------";
    //     qDebug() << QDir::currentPath()+"/debug/1/"+databasename;

    // 5 初始化
    ui->label->setText("路径："+rootDir.absolutePath());


    // 6 新建文件系统模型指针并设置根目录
    filesystem = new QFileSystemModel(this);
    filesystem->setRootPath(rootDir.absolutePath());

    // 在listview装载
    ui->treeView->setModel(filesystem);
    ui->treeView->setRootIndex(filesystem->index(rootDir.absolutePath()));

    // 隐藏系统自带的Header
    ui->treeView->header()->setVisible(false);
    // 隐藏其他三列，大小，名称等信息
    ui->treeView->setColumnHidden(1, true);
    ui->treeView->setColumnHidden(2, true);
    ui->treeView->setColumnHidden(3, true);


    QStringList filter;

    //除上面path外, 只有在这里指定的文件或文件夹才会显示
    filter << "*.tic" << "*.trd" << "*.tdf"<< "*.tb"<< "*.db";
    filesystem->setNameFilters(filter);

    //除filter之外的目录或文件设置为不显示(而不是灰色不可用状态)
    filesystem->setNameFilterDisables(false);


    ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);

}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::recOrder(QStringList ol)
//{
//    qDebug()<<"olsize";
//    qDebug()<<ol.size();
//    order.append(ol.at(0));
//}

void MainWindow::receivelogin() {
    this->show(); /* 显示主窗口 */
}


void MainWindow::SlotGetQString_2(QString tname,QString colname,QString collength,QString coltype,QString constraint,QString dbname)
{
    ui->textBrowser->append(tname);
    ui->textBrowser->append(colname);
    ui->textBrowser->append(collength);
    ui->textBrowser->append(coltype);
    ui->textBrowser->append(constraint);
    ui->textBrowser->append(dbname);
}

void MainWindow::SlotGetQString_3(QString tname,QString colname,QString collength,QString coltype,QString constraint,QString action,QString defaultnum,QString dbname)
{
    ui->textBrowser->append(tname);
    ui->textBrowser->append(colname);
    ui->textBrowser->append(collength);
    ui->textBrowser->append(coltype);
    ui->textBrowser->append(constraint);
    ui->textBrowser->append(action);
    ui->textBrowser->append(defaultnum);
    ui->textBrowser->append(dbname);

}

void MainWindow::SlotGetQString_4(QString tname,QString colname,QString where)
{
    ui->textBrowser->append(tname);
    ui->textBrowser->append(colname);
    ui->textBrowser->append(where);
}

void MainWindow::SlotGetSelectSet(QStringList colList,QStringList resSet,QStringList order)
{
    if(resSet.size()==1){
        ui->textBrowser->append("select结果为空");
        return;
    }

    ui->tableWidget->clear();

    int colNum=resSet[0].toInt();
    int rowCount = (resSet.size()-1)/colNum;

    ui->tableWidget->resizeRowsToContents();//调整行内容大小
    ui->tableWidget->setColumnCount(colNum);//设置列数
    ui->tableWidget->setRowCount(0);//设置初始行数为0
    //ui->tableWidget->horizontalHeader()->setDefaultSectionSize(200);//标题头的大小
    //ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);//横向先自适应宽度
    //ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);//然后设置要根据内容使用宽度的列

    //设置表头的文字(列名)
    ui->tableWidget->setHorizontalHeaderLabels(colList);

    //向表里面动态添加参数
    for(int i=0;i<rowCount;i++){
        ui->tableWidget->insertRow(i);
        for(int j = i*colNum+1; j <= (i+1)*colNum; j++){
            ui->tableWidget->setItem(i,(j-1)%colNum,new QTableWidgetItem(resSet[j]));
        }
    }

    //order
    qDebug()<<"mainwindow:ordersize";
    qDebug()<<order.size();
    if(order.size()!=0)
    {
        qDebug()<<"排序";
        QString type=order.takeLast();//asc or desc
        Qt::SortOrder ot=Qt::AscendingOrder;
        QStringList ol=order;
        QMap<QString,int> index;

        if(type=="desc") ot=Qt::DescendingOrder;

        for(int k=0;k<colNum&&(!ol.isEmpty());k++)
        {
            if(ol.at(0)==colList.at(k))
            {
                index.insert(ol.at(0),k);
                ol.takeFirst();
                qDebug()<<"key,index";
                qDebug()<<index.keys();
                qDebug()<<index.values();
            }
        }
        this->ui->tableWidget->sortByColumn(index.values().at(0),ot);
        if(index.size()>1)
        {
            qDebug()<<"多列排序";

            while(!index.isEmpty()){

            }
        }
    }
}

void MainWindow::SlotGetQString_5(QString tname,QString colname,QString values)
{
    ui->textBrowser->append(tname);
    ui->textBrowser->append(colname);
    ui->textBrowser->append(values);
}
void MainWindow::SlotGetQString_6(QString tname,QString set,QString where)
{
    ui->textBrowser->append(tname);
    ui->textBrowser->append(set);
    ui->textBrowser->append(where);
}
void MainWindow::SlotGetQString_7(QString tname)
{
    ui->textBrowser->append(tname);
}

void MainWindow::SlotGetQString_8(QString tname,QString where)
{
    ui->textBrowser->append(tname);
    ui->textBrowser->append(where);
}

void MainWindow::SlotGetQString_9(QString dbname)
{
    ui->textBrowser->append(dbname);
    qDebug() << dbname;
}
void MainWindow::SlotGetQString_10(QString dbname)
{
    ui->textBrowser->append(dbname);
}

void MainWindow::SlotGetQString_11(QString tname,QString colname,QString collength,QString coltype,QString constraint,QString defaultnum,QString dbname)
{
    ui->textBrowser->append(tname);
    ui->textBrowser->append(colname);
    ui->textBrowser->append(collength);
    ui->textBrowser->append(coltype);
    ui->textBrowser->append(constraint);
    ui->textBrowser->append(defaultnum);
    ui->textBrowser->append(dbname);
}

void MainWindow::SlotGetdbname(QString dbname)
{
    ui->textBrowser->append(dbname);
}

void MainWindow::OnpushButton2()
{
    nt->show();
}

void MainWindow::OnpushButton3()
{
    at->show();
}

void MainWindow::OnpushButton4()
{
    st->show();
}
void MainWindow::OnpushButton5()
{
    it->show();
}
void MainWindow::OnpushButton6()
{
    ut->show();
}

void MainWindow::OnpushButton8()
{
    det->show();
}

void MainWindow::OnpushButton9()
{
    cddb->show();
}

void MainWindow::on_pushButton_clicked()
{
    ui->tableWidget->clear();       //清空表
    QString str = ui->textEdit->toPlainText();
    qDebug() << str;
    if(str.indexOf("\n") != -1) //如果有\n
    {
        str.replace("\n",""); //将每个\n都替换为空
    }
    qDebug() << str;

    issql(str);

    model=gra.translate(model,str);
    qDebug() << model;
    //QString s = QString::number(model, 10);
    showinfo(model);
    model=99;

}

void MainWindow::issql(QString str){

    if (str.contains("grant")) {
        ui->textBrowser->append("grant");
        model=GRANT;
    }
    else if (str.contains("revoke")) {
        ui->textBrowser->append("revoke");
        model=REVOKE;
    }
    else if(str.contains("create")){
        if(str.contains("table")){
            model=CREATETABLE;
        }
        else if(str.contains("database")){
            model=CREATEDATABASE;
        }


    }
    else if(str.contains("drop")){
        if(str.contains("alter")){
            model=ALTERTABLEDROP;
        }
        else if(str.contains("table")){
            model=DROPTABLE;
        }
        else if(str.contains("database")){
            model=DROPDATABASE;
        }
    }
    else if(str.contains("alter")){
        if(str.contains("add")){

            model=ALTERTABLEADD;
        }
        else if (str.contains("modify")) {
            ui->textBrowser->append("modify");
            model=ALTERTABLEMODIFY;
        }
        else if (str.contains("drop")) {
            ui->textBrowser->append("drop");
            model=ALTERTABLEDROP;
        }
        else if (str.contains("rename")) {
            ui->textBrowser->append("rename");
            model=RENAME;
        }
    }
    else if (str.contains("insert")) {
        ui->textBrowser->append("insert");
        model=INSERT;
    }
    else if (str.contains("update")) {
        ui->textBrowser->append("update");
        model=UPDATE;
    }
    else if (str.contains("select")) {

        ui->textBrowser->append("select from where");
        model=SELECTWHERE;

    }
    else if (str.contains("delete")) {
        ui->textBrowser->append("delete");
        model=DELETE;
    }
    else if (str.contains("use")) {
        ui->textBrowser->append("use");
        model=USEDATABASE;
    }

}

void MainWindow::showinfo(int mod){
    switch(mod)
    {
    case WRONGREGEX:{
        ui->textBrowser->append("语法错误，请重新输入");
    }
        break;
    case CREATETABLE:{
        ui->textBrowser->append("创建表");
    }
        break;
    case DROPTABLE:{
        ui->textBrowser->append("删除表");
    }
        break;
    case ALTERTABLEADD:{
        ui->textBrowser->append("增加表的一列");
    }
        break;
    case ALTERTABLEMODIFY:{
        ui->textBrowser->append("修改表的一列属性");
    }
        break;
    case ALTERTABLEDROP:{
        ui->textBrowser->append("删除表的一列属性");
    }
        break;
    case RENAME:{
        ui->textBrowser->append("修改表的一列名字");
    }
        break;
    case INSERT:{
        ui->textBrowser->append("插入数据");
    }
        break;
    case UPDATE:{
        ui->textBrowser->append("更新数据");
    }
        break;
    case SELECTWHERE:{
        ui->textBrowser->append("查询");
    }
        break;
    case DELETE:{
        ui->textBrowser->append("删除数据");
    }
        break;

    case CREATEDATABASE:{
        ui->textBrowser->append("创建数据库");
    }
        break;
    case DROPDATABASE:{
        ui->textBrowser->append("删除数据库");
    }
        break;

    case USEDATABASE:{
        ui->textBrowser->append("连接数据库");
    }
        break;
    case GRANT:{
        ui->textBrowser->append("授予权限");
    }
        break;
    case REVOKE:{
        ui->textBrowser->append("收回权限");
    }
        break;
    }
}


void MainWindow::on_pushButton_7_clicked()
{
    ui->tableWidget->clear();
    //从文件读取数据
    while (ui->tableWidget->rowCount() > 0) {
        ui->tableWidget->removeRow(0);
    }
    //ui->tableWidget->clear();
    QFile f(filepath0);
    f.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream output(&f);
    output.setCodec("UTF-8");
    QHash<QString, QString> varHash;
    QString lineStr;//文件的每一行的字符串
    QStringList lineList; //整行字符串，分割处理为单个字符串，存入到表中
    varHash.clear();
    lineList.clear();//操作前，清空
    //遍历文件
    QString line;
    int n=-1;
    int max = 0;
    do{
        n++;
        line=output.readLine();
        if(line.indexOf("\r\n") != -1) //如果有\n
        {
            line.replace("\r\n",""); //将每个\n都替换为空
        }

        lineList = line.split(" "); //去除换行符获取字符串，存放到表中

        if(lineList.count()>max) max=lineList.count();



    }while(!(line.isNull()));
    f.close();

    //int colCount = ui->tableWidget->columnCount();
    //qDebug() <<QString::number(max, 10);
    ui->tableWidget->setColumnCount(max);

    f.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream output2(&f);
    output2.setCodec("UTF-8");



    while(!output2.atEnd()&&n>0)
    {
        lineList.clear();
        lineStr = output2.readLine(); //读取文件的一行

        if(lineStr.indexOf("\r\n") != -1) //如果有\n
        {
            lineStr.replace("\r\n",""); //将每个\n都替换为空
        }

        lineList = lineStr.split(" "); //去除换行符获取字符串，存放到表中



        //向表里面动态添加参数
        int rowCount = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(rowCount);
        for(int i = 0; i < lineList.count(); i++)
        {

            ui->tableWidget->setItem(rowCount,i,new QTableWidgetItem(lineList[i]));

        }
    }
    f.close();//关闭文件

}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    // 获取选中条目的绝对路径并显示
    QString curItemRel = ui->treeView->model()->data(index).toString();

    curItem = filesystem->fileInfo(index).absolutePath()+"/"+curItemRel;
    filepath0=curItem;
    //ui->textBrowser->append(filepath0);
    ui->label_3->setText("展开："+curItem);
}


// 按钮单击事件
void MainWindow::on_pushButton_10_clicked()
{
    rootDir.cdUp();
    filesystem->setRootPath(rootDir.absolutePath());
    ui->treeView->setModel(filesystem);
    ui->treeView->setRootIndex(filesystem->index(rootDir.absolutePath()));
    ui->label_3->setText("路径："+rootDir.absolutePath());
    filepath0=rootDir.absolutePath();
    //ui->textBrowser->append(filepath0);
}

void MainWindow::on_tableWidget_customContextMenuRequested(const QPoint &pos)
{
    QMenu menu;
    QAction *selectAll = menu.addAction(tr("全选"));
    menu.addSeparator();
    QAction *clear = menu.addAction(tr("清空内容"));
    menu.addSeparator();
    QAction *addrow = menu.addAction(tr("插入一行"));
    menu.addSeparator();
    QAction *delrow = menu.addAction(tr("删除当前行"));
    menu.addSeparator();
    QAction *addcol = menu.addAction(tr("插入一列"));
    menu.addSeparator();
    QAction *delcol = menu.addAction(tr("删除当前列"));
    menu.addSeparator();

    connect(selectAll, &QAction::triggered, [=](){
        ui->tableWidget->selectAll();
    });

    connect(clear, &QAction::triggered, [=](){
        ui->tableWidget->clear();
    });

    connect(addrow, &QAction::triggered, [=](){
        int rowIndex = ui->tableWidget->rowCount();
        ui->tableWidget->setRowCount(rowIndex + 1);//总行数增加1
    });

    connect(delrow, &QAction::triggered, [=](){
        int i = ui->tableWidget->currentRow();
        ui->tableWidget->removeRow(i);
    });

    connect(addcol, &QAction::triggered, [=](){
        int colIndex = ui->tableWidget->columnCount();
        ui->tableWidget->setColumnCount(colIndex + 1);//总行数增加1
    });

    connect(delcol, &QAction::triggered, [=](){
        int i = ui->tableWidget->currentColumn();
        ui->tableWidget->removeColumn(i);
    });







    menu.exec(QCursor::pos());
}

void MainWindow::on_pushButton_11_clicked()
{

    int row = ui->tableWidget->rowCount();
    int col = ui->tableWidget->columnCount();
    QList<QString> list;


    for (int i = 0; i < row; i++)
    {
        int isemp=0;
        QString rowStr = "";
        for (int j = 0; j < col; j++){
            if(ui->tableWidget->item(i,j)!=0&&ui->tableWidget->item(i, j)->text()!=NULL)
            {

                rowStr += ui->tableWidget->item(i, j)->text() + " ";
            }
            else
            {
                isemp++;
            }
        }
        if(isemp!=0){
            QMessageBox::information(0,tr("提示"),tr("增加的当前行数据为空!"));
        }
        if(isemp!=col){
            QString strTmp = rowStr.left(rowStr.size()-1);
            strTmp += "\r\n";
            list.push_back(strTmp);
        }

    }

    QFile f(filepath0);
    QTextStream in(&f);

    //读取文件
    if(!f.open(QFile::WriteOnly)){
        qDebug() << ".trd open failed!";
    }else {
        for(int i=0;i<list.count();i++){
            QString content=list[i];
            f.write(content.toLatin1());
        }

        f.close();
    }


}


void MainWindow::on_treeView_customContextMenuRequested(const QPoint &pos)
{
    QMenu menu;
    QAction *newt = menu.addAction(tr("新建表"));
    menu.addSeparator();
    QAction *delt = menu.addAction(tr("删除表"));
    menu.addSeparator();

    connect(newt, &QAction::triggered, [=](){

        QString tname,name,type,desc;
        int a;

        tname=QInputDialog::getText(this, tr("input"), tr("请输入表名："));
        a=QInputDialog::getInt(this, tr("input"), tr("table列的数量"));

        for (int i = 0; i < a; i++)
        {
            name=QInputDialog::getText(this, tr("请输入列名："), tr("请输入列名："));
            desc=desc+name+" ";
            type=QInputDialog::getText(this,tr("请输入类型："), tr("请输入类型："));
            desc=desc+type;
            if(i!=a-1)desc=desc+",";
            qDebug() << desc;
        }

        //ui->treeView->selectAll();

        nt->createtable(tname,desc);
    });



    connect(delt, &QAction::triggered, [=](){
        QString folderPath =filepath0;
        qDebug() << folderPath;

        QStringList list1 = filepath0.split("/");

        QString tablename;
        tablename=list1.at(list1.count()-1);
        nt->droptable(tablename,username);
    });

    menu.exec(QCursor::pos());
}

void MainWindow::on_pushButton_12_clicked()
{
    QString tname,name,type,desc;
    int a;

    tname=QInputDialog::getText(this, tr("input"), tr("请输入表名："));
    a=QInputDialog::getInt(this, tr("input"), tr("table列的数量"));

    for (int i = 0; i < a; i++)
    {
        name=QInputDialog::getText(this, tr("请输入列名："), tr("请输入列名："));
        desc=desc+name+" ";
        type=QInputDialog::getText(this,tr("请输入类型："), tr("请输入类型："));
        desc=desc+type;
        if(i!=a-1)desc=desc+",";
        qDebug() << desc;
    }

    //ui->treeView->selectAll();

    nt->createtable(tname,desc);
}

void MainWindow::on_pushButton_13_clicked()
{
    int rowIndex = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(rowIndex + 1);//总行数增加1
}

void MainWindow::on_pushButton_14_clicked()
{
    int i = ui->tableWidget->currentRow();
    ui->tableWidget->removeRow(i);
}

void MainWindow::on_pushButton_17_clicked()
{
    int colIndex = ui->tableWidget->columnCount();
    ui->tableWidget->setColumnCount(colIndex + 1);//总行数增加1
}

void MainWindow::on_pushButton_18_clicked()
{
    int i = ui->tableWidget->currentColumn();
    ui->tableWidget->removeColumn(i);
}

void MainWindow::on_pushButton_15_clicked()
{
    emit Signallogin();
}

void MainWindow::on_pushButton_16_clicked()
{
    QString folderPath =filepath0;
    qDebug() << folderPath;

    QStringList list1 = filepath0.split("/");

    QString tablename;
    tablename=list1.at(list1.count()-1);
    nt->droptable(tablename,username);

    //    QDir dir;
    //    dir.setPath(folderPath);
    //    dir.removeRecursively();
}
