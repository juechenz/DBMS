#include "data.h"
#include<QCoreApplication>
#include<regex>

QString s0="数据项： ";
QString s1="关键字： ";
QString s2="所选表： ";
QString s3="判断条件： ";

extern QString username;
using namespace std;
QString databasename="defaultdb";


int data::datadelete(char* str)
{
    bool flag=true;
    string table_name;
    string judge="";
    smatch result;
    string s=str;
    regex Exp("( *delete +from +)((\\w+\\.)?)(\\w+)(( +where +)(\\w+[><=]=?'?\\w+'?)( +and +\\w+[><=]=?'?\\w+'?)*)? *;?");//提取关键内容

    regex_match(s,result,Exp);

    string a0,b1,c2,d3,e4,f5,g6,h7,i8,j9;
    a0=result[0];b1=result[1];c2=result[2];d3=result[3];e4=result[4];
    f5=result[5];g6=result[6];h7=result[7];i8=result[8];j9=result[9];
    qDebug() << QString::fromStdString(a0);
    qDebug() << QString::fromStdString(b1);
    qDebug() << QString::fromStdString(c2);
    qDebug() << QString::fromStdString(d3);
    qDebug() << QString::fromStdString(e4);
    qDebug() << QString::fromStdString(f5);
    qDebug() << QString::fromStdString(g6);
    qDebug() << QString::fromStdString(h7);
    qDebug() << QString::fromStdString(i8);
    qDebug() << QString::fromStdString(j9);
    qDebug() << "----------------------------";

    QString tname,condition;
    string usern;
    QString uname;
    usern=result[3];
    uname=QString::fromStdString(usern);

    table_name=result[4];
    judge=result[5];
    tname=QString::fromStdString(table_name);
    condition=QString::fromStdString(judge);

    if(tname.indexOf(",") != -1) //如果有\n
    {
        tname.replace(","," "); //将每个\n都替换为空
    }
    if(condition.indexOf(" ") != -1) //如果有\n
    {
        condition.replace(" ",""); //将每个\n都替换为空
    }

    if(condition.indexOf("where") != -1) //如果有\n
    {
        condition.replace("where",","); //将每个\n都替换为空
    }
    if(condition.indexOf("and") != -1) //如果有\n
    {
        condition.replace("and","/"); //将每个\n都替换为空
    }
    if(condition.indexOf(",") != -1) //如果有\n
    {
        condition.replace(",",""); //将每个\n都替换为空
    }
    if(condition.indexOf("'") != -1) //如果有\n
    {
        condition.replace("'",""); //将每个\n都替换为空
    }
    if(uname.indexOf(".") != -1) //如果有\n
    {
        uname.replace(".",""); //将每个\n都替换为空
        flag=cd.permission(uname,"delete",tname);

    }








    qDebug() << uname;
    qDebug() << tname;
    qDebug() <<condition;

    if(flag==true){
        if(uname==NULL){
            uname=username;
        }
        dt.deletetb(tname,condition,uname);
    }else{
        QMessageBox msgBox;
        msgBox.setInformativeText("您没有该操作的权限");
        msgBox.exec();
    }


    return 0;
}

int data::dataupdate(char* str){//更新
    bool flag=true;
    string table_name;
    string judge="",judge2="";
    string newContent;
    smatch result;
    string s=str;
    regex Exp("(update +)((\\w+\\.)?)(\\w+)( +set +)(\\w+='?\\w+'?)(( +where +)(\\w+[><=]=?'?\\w+'?)( +and +\\w+[><=]=?'?\\w+'?)*)? *;?");//提取关键内容
    regex_match(s,result,Exp);

    QString newdata,tname,condition;

    string usern;
    QString uname;
    usern=result[3];
    uname=QString::fromStdString(usern);

    table_name=result[4];
    newContent=result[6];
    judge=result[7];
    newdata=QString::fromStdString(newContent);
    tname=QString::fromStdString(table_name);
    condition=QString::fromStdString(judge);

    if(newdata.indexOf(",") != -1) //如果有\n
    {
        newdata.replace(","," "); //将每个\n都替换为空
    }

    if(tname.indexOf(",") != -1) //如果有\n
    {
        tname.replace(","," "); //将每个\n都替换为空
    }

    /*
    if(condition.indexOf(" ") != -1) //如果有\n
    {
        condition.replace(" ",""); //将每个\n都替换为空
    }*/

    if(condition.indexOf("where") != -1) //如果有\n
    {
        condition.replace("where",","); //将每个\n都替换为空
    }
    if(condition.indexOf("and") != -1) //如果有\n
    {
        condition.replace("and","&"); //将每个\n都替换为空
    }

    if(condition.indexOf("or") != -1) //如果有\n
    {
        condition.replace("or","|"); //将每个\n都替换为空
    }

    if(condition.indexOf(",") != -1) //如果有\n
    {
        condition.replace(",",""); //将每个\n都替换为空
    }
    if(uname.indexOf(".") != -1) //如果有\n
    {
        uname.replace(".",""); //将每个\n都替换为空
        flag=cd.permission(uname,"update",tname);
    }
    qDebug() << uname;







    qDebug() << newdata;

     qDebug() << tname;

     qDebug() <<condition;

     QStringList list1 = condition.split("&");
     qDebug() <<list1;


     if(flag==true){
         if(uname==NULL){
             uname=username;
         }
         ut.update(tname,newdata,condition,uname);
     }else{
         QMessageBox msgBox;
         msgBox.setInformativeText("您没有该操作的权限");
         msgBox.exec();
     }

    return 0;
}

int data::datainsert(char* str){//插入
    bool flag=true;
    QVector<string> record;
    string table_name;

    string attribute;
    string newContent;
    smatch result;
    string s=str;

    regex Exp("(insert +into +)((\\w+\\.)?)(\\w+) +(\\(\\w+( *, *\\w+)*\\))( +values *)(\\( *)('?\\w+'?( *, *'?\\w+'?)*)( *\\) *) *;?");//提取关键内容

    regex_match(s,result,Exp);

    QString tname,linename,newdata;

    string usern;
    QString uname;
    usern=result[3];
    uname=QString::fromStdString(usern);
    table_name=result[4];
    attribute=result[5];
    newContent=result[9];

    //qDebug()<<QString::fromStdString(result[3]);

    tname=QString::fromStdString(table_name);
    newdata=QString::fromStdString(newContent);
    linename=QString::fromStdString(attribute);
    qDebug() << linename;

    if(newdata.indexOf(",") != -1) //如果有\n
    {
        newdata.replace(","," "); //将每个\n都替换为空
    }
    if(linename.indexOf(",") != -1) //如果有\n
    {
        linename.replace(","," "); //将每个\n都替换为空
    }
    if(linename.indexOf("(") != -1) //如果有\n
    {
        linename.replace("(",""); //将每个\n都替换为空
    }
    if(linename.indexOf(")") != -1) //如果有\n
    {
        linename.replace(")",""); //将每个\n都替换为空
    }

    if(tname.indexOf(",") != -1) //如果有\n
    {
        tname.replace(","," "); //将每个\n都替换为空
    }
    if(uname.indexOf(".") != -1) //如果有\n
    {
        uname.replace(".",""); //将每个\n都替换为空
        flag=cd.permission(uname,"insert",tname);
    }
    qDebug() << uname;





     qDebug() << tname;
     qDebug() << linename;

     qDebug() <<newdata;
     qDebug() << "----------------------------";

     QStringList list1 = newdata.split(" ");
     qDebug() <<list1;
     QStringList list2 = linename.split(" ");
     qDebug() <<list2;

     if(flag==true){
         if(uname==NULL){
             uname=username;
         }
         it.inserttb(tname,list2,list1,uname);
     }else{
         QMessageBox msgBox;
         msgBox.setInformativeText("您没有该操作的权限");
         msgBox.exec();
     }



    return 0;
}

int data::datainsert2(char* str){//插入
    bool flag=true;
    QVector<string> record;
    string table_name;

    string newContent;
    smatch result;
    string s=str;
    regex Exp("(insert +into +)((\\w+\\.)?)(\\w+)( +values *)(\\( *)('?\\w+'?( *, *'?\\w+'?)*)( *\\) *) *;?");//提取关键内容

    regex_match(s,result,Exp);

    QString tname,newdata;

    string usern;
    QString uname;
    usern=result[3];
    uname=QString::fromStdString(usern);
    table_name=result[4];
    newContent=result[7];

    tname=QString::fromStdString(table_name);
    newdata=QString::fromStdString(newContent);

    if(newdata.indexOf(",") != -1) //如果有\n
    {
        newdata.replace(","," "); //将每个\n都替换为空
    }

    if(tname.indexOf(",") != -1) //如果有\n
    {
        tname.replace(","," "); //将每个\n都替换为空
    }
    if(uname.indexOf(".") != -1) //如果有\n
    {
        uname.replace(".",""); //将每个\n都替换为空
        flag=cd.permission(uname,"insert",tname);
    }
    qDebug() << uname;



     qDebug() << tname;

     qDebug() <<newdata;

     QStringList list1 = newdata.split(" ");
     qDebug() <<list1;
     //QString empty=NULL;
     //QStringList list2 =empty.split(" ");
     QStringList list2;
     qDebug() <<list2;

     if(flag==true){
         if(uname==NULL){
             uname=username;
         }
         it.inserttb(tname,list2,list1,uname);
     }else{
         QMessageBox msgBox;
         msgBox.setInformativeText("您没有该操作的权限");
         msgBox.exec();
     }

    return 0;
}

int data::dataselectall(char* str){ //查询
    bool flag=true;
    string table_name;
    string judge="";
    smatch result;
    string s=str;
    regex Exp("( *select *\\* *from +)((\\w+\\.)?\\w+( *, *(\\w+\\.)?\\w+)*)(( +where +)((\\w+\\.+)?\\w+[><=]=?'?(\\w+\\.+)?\\w+'?)( +and +(\\w+\\.+)?\\w+[><=]=?'?(\\w+\\.+)?\\w+'?)*)?( +orderby +(\\w+\\.)?\\w+( *, *(\\w+\\.)?\\w+)* +(desc)?(asc)?)? *;?");//提取关键内容
   // " *select *\\* *from +\\w+( *, *\\w+)* +(*where +\\w+='?\\w+'?( +and +\\w+='?\\w+'?)*)? *;?"

        //regex Exp("(select *\\* *from +)(\\w+) *((where +)(\\w+='?\\w+'?))? *;?");//提取关键内容

    regex_match(s,result,Exp);

    QString tname,condition,ordername;

    string usern,oname;
    QString uname;
    usern=result[3];
    table_name=result[2];
    judge=result[6];
    oname=result[14];
    tname=QString::fromStdString(table_name);
    condition=QString::fromStdString(judge);
    uname=QString::fromStdString(usern);
    ordername=QString::fromStdString(oname);

    if(tname.indexOf(uname) != -1) //如果有\n
    {
        tname.replace(uname,""); //将每个\n都替换为空
    }
    if(tname.indexOf(",") != -1) //如果有\n
    {
        tname.replace(","," "); //将每个\n都替换为空
    }

    /*   为解析where暂时不替换空格
    if(condition.indexOf(" ") != -1) //如果有\n
    {
        condition.replace(" ",""); //将每个\n都替换为空
    }*/

    if(condition.indexOf("where") != -1) //如果有\n
    {
        condition.replace("where",","); //将每个\n都替换为空
    }
    if(condition.indexOf("and") != -1) //如果有\n
    {
        condition.replace("and","&"); //将每个\n都替换为空
    }    
    if(condition.indexOf("or") != -1) //如果有\n
    {
        condition.replace("or","|"); //将每个\n都替换为空
    }
    if(condition.indexOf(",") != -1) //如果有\n
    {
        condition.replace(",",""); //将每个\n都替换为空
    }

    if(uname.indexOf(".") != -1) //如果有\n
    {
        uname.replace(".",""); //将每个\n都替换为空
        flag=cd.permission(uname,"select",tname);
    }

//        string a0,b1,c2,d3,e4,f5,g6,h7,i8,j9,k10,l11,m12,n13,o14;
//        a0=result[0];b1=result[1];c2=result[2];d3=result[3];e4=result[4];
//        f5=result[5];g6=result[6];h7=result[7];i8=result[8];j9=result[9];
//        k10=result[10];l11=result[11];m12=result[12];n13=result[13];o14=result[14];
//        qDebug() << QString::fromStdString(a0);
//        qDebug() << QString::fromStdString(b1);
//        qDebug() << QString::fromStdString(c2);
//        qDebug() << QString::fromStdString(d3);
//        qDebug() << QString::fromStdString(e4);
//        qDebug() << QString::fromStdString(f5);
//        qDebug() << QString::fromStdString(g6);
//        qDebug() << QString::fromStdString(h7);
//        qDebug() << QString::fromStdString(i8);
//        qDebug() << QString::fromStdString(j9);
//        qDebug() << QString::fromStdString(k10);
//        qDebug() << QString::fromStdString(l11);
//        qDebug() << QString::fromStdString(m12);
//        qDebug() << QString::fromStdString(n13);
//        qDebug() << QString::fromStdString(o14);
//        qDebug() << "----------------------------";

    qDebug() << uname;
     qDebug() << tname;
     qDebug() <<condition;
     //qDebug()<<"order:";
     //qDebug() <<ordername;

     QStringList list0 = tname.split(" ");
     qDebug() <<list0;
     QStringList list1 = condition.split("&");
     qDebug() <<list1;

//     if(ordername!=NULL)
//         st.setOrder(ordername);

     if(flag==true){
         if(uname==NULL){
             uname=username;
         }
         st.selectAll(tname,condition,ordername,uname);
     }else{
         QMessageBox msgBox;
         msgBox.setInformativeText("您没有该操作的权限");
         msgBox.exec();
     }



    return 0;

}

int data::dataselectsome(char *str){
    bool flag=true;
    string table_name,oname;
    string judge="";
    smatch result;
    string s=str;
    QVector<string> select_col;
    string some_col;
    regex Exp("( *select +)((\\w+\\.)?\\w+( *, *(\\w+\\.)?\\w+)*)( +from +)((\\w+\\.)?\\w+( *, *(\\w+\\.)?\\w+)*)(( +where +)((\\w+\\.+)?\\w+[><=]=?'?(\\w+\\.+)?\\w+'?)( +and +(\\w+\\.+)?\\w+[><=]=?'?(\\w+\\.+)?\\w+'?)*)?( +orderby +(\\w+\\.)?\\w+( *, *(\\w+\\.)?\\w+)* +(desc)?(asc)?)? *;?");//提取关键内容

    //" *select +\\w+( *, *\\w+)* +from +\\w+( *, *\\w+)* +(where +\\w+='?\\w+'?( +and +\\w+='?\\w+'?)*)? *;?"

    regex_match(s,result,Exp);

    QString col,tname,condition;

    some_col=result[2];
    table_name=result[7];
    judge=result[11];
    oname=result[19];

    string usern;
    QString uname,ordername;
    usern=result[8];
    uname=QString::fromStdString(usern);

    col=QString::fromStdString(some_col);
    tname=QString::fromStdString(table_name);
    condition=QString::fromStdString(judge);
    ordername=QString::fromStdString(oname);

qDebug() << tname;

    if(tname.indexOf(uname) != -1) //如果有\n
        {
            tname.replace(uname,""); //将每个\n都替换为空
        }
    qDebug() << tname;
    if(col.indexOf(",") != -1) //如果有\n
    {
        col.replace(","," "); //将每个\n都替换为空
    }

    if(tname.indexOf(",") != -1) //如果有\n
    {
        tname.replace(","," "); //将每个\n都替换为空
    }
    /*
    if(condition.indexOf(" ") != -1) //如果有\n
    {
        condition.replace(" ",""); //将每个\n都替换为空
    }*/

    if(condition.indexOf("where") != -1) //如果有\n
    {
        condition.replace("where",","); //将每个\n都替换为空
    }
    if(condition.indexOf("and") != -1) //如果有\n
    {
        condition.replace("and","/"); //将每个\n都替换为空
    }
    if(condition.indexOf("or") != -1) //如果有\n
    {
        condition.replace("or","|"); //将每个\n都替换为空
    }
    if(condition.indexOf(",") != -1) //如果有\n
    {
        condition.replace(",",""); //将每个\n都替换为空
    }


        if(uname.indexOf(".") != -1) //如果有\n
        {
            uname.replace(".",""); //将每个\n都替换为空
            flag=cd.permission(uname,"select",tname);
        }
        qDebug() << uname;




    qDebug() << col;

     qDebug() << tname;

     qDebug() <<condition;
     qDebug() <<ordername;

     QStringList list2 = col.split(" ");
     qDebug() <<list2;

     QStringList list0 = tname.split(" ");
     qDebug() <<list0;

     QStringList list1 = condition.split("&");
     qDebug() <<list1;

     if(flag==true){
         if(uname==NULL){
             uname=username;
         }
         //it.inserttb(tname,list2,list1,uname);
         st.select(tname,col,condition,ordername,uname);
     }else{
         QMessageBox msgBox;
         msgBox.setInformativeText("您没有该操作的权限");
         msgBox.exec();
     }

    //st.select(tname,col,condition);


    return 0;
}

int data::createtable(char *str){
    string table_name,col_name;
    smatch result;
    string s=str;

    regex Exp("( *create +table) +(\\w+) *\\( *(\\w+ +\\w+(\\((\\d*)\\)){1} *(primarykey)?(unique)?(notnull)?( *default +\\d+)? *(, *\\w+ +\\w+(\\(\\d*\\)){1} *(primarykey)?(unique)?(notnull)?( *default +\\d+)? *)*)\\) *;?");//提取关键内容
    regex_match(s,result,Exp);


    QString tname,newcol;

    table_name=result[2];
    col_name=result[3];
    tname=QString::fromStdString(table_name);
    newcol=QString::fromStdString(col_name);


    qDebug() << tname;
    qDebug() << newcol;

//    QStringList list1 = newcol.split(",");
//    qDebug() <<list1;

    ct.createtable(tname,newcol);
    return 0;
}

int data::droptable(char *str){
    bool flag=true;
    string table_name;
    string usern;
    smatch result;
    string s=str;

    regex Exp("( *drop +table) +((\\w+\\.)?)(\\w+) *;?");//提取关键内容
    regex_match(s,result,Exp);

    QString tname;
    QString uname;


    usern=result[3];
    table_name=result[4];
    uname=QString::fromStdString(usern);
    tname=QString::fromStdString(table_name);

    if(uname.indexOf(".") != -1) //如果有\n
    {
        uname.replace(".",""); //将每个\n都替换为空
        flag=cd.permission(uname,"drop",tname);
    }




    if(flag==true){
        if(uname==NULL){
            uname=username;
        }
        ct.droptable(tname,uname);
    }else{
        QMessageBox msgBox;
        msgBox.setInformativeText("您没有该操作的权限");
        msgBox.exec();
    }


    qDebug() << uname;
     qDebug() << tname;

       return 0;
}

int data::alteradd(char *str){
    bool flag=true;
    string table_name;
    string col_name;
    string type_name;
    smatch result;
    string s=str;

    //提取关键字
    regex Exp("alter +table +((\\w+\\.)?)(\\w+) +add +(\\w+) +(\\w+(\\(\\d*\\)){1} *(primarykey)?(unique)?(notnull)?( *default +\\d+)?) *;?");

    regex_match(s,result,Exp);



    QString tname,newcol,newtype;

    string usern;
    QString uname;
    usern=result[2];
    uname=QString::fromStdString(usern);
    table_name=result[3];
    col_name=result[4];
    type_name=result[5];
    //type_name2=result[4];
    //type_name3=result[5];
    tname=QString::fromStdString(table_name);
    newcol=QString::fromStdString(col_name);
    newtype=QString::fromStdString(type_name);

    if(uname.indexOf(".") != -1) //如果有\n
    {

        uname.replace(".",""); //将每个\n都替换为空
        flag=cd.permission(uname,"alter",tname);
    }
    qDebug() << uname;


    qDebug() << tname;
    qDebug() << newcol;
    qDebug() << newtype;




    if(flag==true){
        if(uname==NULL){
            uname=username;
        }
        at.alter_add(tname,newcol,newtype,uname);
    }else{
        QMessageBox msgBox;
        msgBox.setInformativeText("您没有该操作的权限");
        msgBox.exec();
    }

    return 0;
}

int data::altermodify1(char *str){
    bool flag=true;
    string table_name;
    string col_name;
    string type_name;
    smatch result;
    string s=str;

    //提取关键字
    regex Exp(" *alter +table +((\\w+\\.)?)(\\w+) +modify +(\\w+) +(\\w+(\\(\\d*\\))?) *;?");
    regex_match(s,result,Exp);

    QString tname,newcol,newtype;

    string usern;
    QString uname;
    usern=result[2];
    uname=QString::fromStdString(usern);

    table_name=result[3];
    col_name=result[4];
    type_name=result[5];
    tname=QString::fromStdString(table_name);
    newcol=QString::fromStdString(col_name);
    newtype=QString::fromStdString(type_name);
    if(uname.indexOf(".") != -1) //如果有\n
    {
        uname.replace(".",""); //将每个\n都替换为空
        flag=cd.permission(uname,"alter",tname);
    }
    qDebug() << uname;



     qDebug() << tname;
     qDebug() << newcol;
     qDebug() << newtype;

     if(flag==true){
         if(uname==NULL){
             uname=username;
         }
         at.alter_modify_typelen(tname,newcol,newtype,uname);
     }else{
         QMessageBox msgBox;
         msgBox.setInformativeText("您没有该操作的权限");
         msgBox.exec();
     }



        return 0;
}

int data::altermodify2(char *str){
    bool flag=true;
    string table_name;
    string col_name;
    string type_name;
    smatch result;
    string s=str;

    //提取关键字
    regex Exp(" *alter +table +((\\w+\\.)?)(\\w+) +modify +(\\w+) +((primarykey)?(unique)?(notnull)?( *default +\\d+)?) *;?");

    regex_match(s,result,Exp);

    QString tname,colname,constriant;

    string usern;
    QString uname;
    usern=result[2];
    uname=QString::fromStdString(usern);
    table_name=result[3];
    col_name=result[4];
    type_name=result[5];
    tname=QString::fromStdString(table_name);
    colname=QString::fromStdString(col_name);
    constriant=QString::fromStdString(type_name);
    if(uname.indexOf(".") != -1) //如果有\n
    {
        uname.replace(".",""); //将每个\n都替换为空
        flag=cd.permission(uname,"alter",tname);
    }
    qDebug() << uname;

    if(flag==true){
        if(uname==NULL){
            uname=username;
        }
        at.alter_modify_tic(tname,colname,constriant,uname);

    }else{
        QMessageBox msgBox;
        msgBox.setInformativeText("您没有该操作的权限");
        msgBox.exec();
    }




    qDebug() << tname;
    qDebug() << colname;
    qDebug() << constriant;
    qDebug() << "----------------";
//    at.alter_modify_tic(tname,colname,constriant);
    return 0;
}

int data::alterdrop(char *str){
     bool flag=true;
    string table_name;
    string col_name;
    smatch result;
    string s=str;

    //提取关键字
    regex Exp(" *alter +table +((\\w+\\.)?)(\\w+) +drop column +(\\w+) *;?");
    // *alter +table +\\w+ +drop +\\w+;*
    regex_match(s,result,Exp);
    QString tname,colname;

    string usern;
    QString uname;
    usern=result[2];
    uname=QString::fromStdString(usern);
    table_name=result[3];
    col_name=result[4];;
    tname=QString::fromStdString(table_name);
    colname=QString::fromStdString(col_name);
    if(uname.indexOf(".") != -1) //如果有\n
    {
        uname.replace(".",""); //将每个\n都替换为空
        flag=cd.permission(uname,"alter",tname);
    }
    qDebug() << uname;




    qDebug() << tname;
    qDebug() << colname;

    if(flag==true){
        if(uname==NULL){
            uname=username;
        }
        at.alter_drop(tname,colname,uname);
    }else{
        QMessageBox msgBox;
        msgBox.setInformativeText("您没有该操作的权限");
        msgBox.exec();
    }




    return 0;
}

int data::alterrename(char *str){
    bool flag=true;
    string table_name;
    string old_name;
    string new_name;
    smatch result;
    string s=str;

    qDebug() <<str;

    //提取关键字
    regex Exp(" *alter +table +((\\w+\\.)?)(\\w+) +rename column +(\\w+) +to +(\\w+) *;?");
// *alter +table +\\w+ +rename column +\\w+ +to +\\w+ *;?
    regex_match(s,result,Exp);


    QString tname,oldname,newname;

    string usern;
    QString uname;
    usern=result[2];
    uname=QString::fromStdString(usern);
    table_name=result[3];
    old_name=result[4];
    new_name=result[5];
    tname=QString::fromStdString(table_name);
    oldname=QString::fromStdString(old_name);
    newname=QString::fromStdString(new_name);

    if(uname.indexOf(".") != -1) //如果有\n
    {
        uname.replace(".",""); //将每个\n都替换为空
        flag=cd.permission(uname,"alter",tname);
    }
    qDebug() << uname;

    if(flag==true){
        if(uname==NULL){
            uname=username;
        }
        at.alter_rename(tname,oldname,newname,uname);
    }else{
        QMessageBox msgBox;
        msgBox.setInformativeText("您没有该操作的权限");
        msgBox.exec();
    }


     qDebug() << tname;
     qDebug() << oldname;
     qDebug() << newname;

     return 0;
}

int data::createdatabse(char *str){
    string database_name;
    smatch result;
    string s=str;

    regex Exp("( *create +database) +(\\w+) *;?");//提取关键内容
    regex_match(s,result,Exp);

    QString dname;

    database_name=result[2];
    dname=QString::fromStdString(database_name);
    cd.createdb(dname);

    qDebug() << dname;


    return 0;
}

int data::dropdatabse(char *str){
    string database_name;
    smatch result;
    string s=str;

    regex Exp("( *drop +database) +(\\w+) *;?");//提取关键内容
    regex_match(s,result,Exp);

    QString dname;

    database_name=result[2];
    dname=QString::fromStdString(database_name);

    cd.dropdb(dname);

    qDebug() << dname;
    return 0;
}

int data::usedatabse(char *str){
    string database_name;
    smatch result;
    string s=str;

    regex Exp("( *use) +(\\w+) *;?");//提取关键内容
    regex_match(s,result,Exp);


    database_name=result[2];


    QString folderPath =QCoreApplication::applicationDirPath()+"/"+username+"/"+QString::fromStdString(database_name);
    qDebug() << folderPath;
    QDir dir;

    if(!dir.exists(folderPath)){
        qDebug() << "dir not found!";
        QMessageBox msgBox;
        msgBox.setText("目标database不存在");
        msgBox.exec();
    }else{
        databasename=QString::fromStdString(database_name);
        QMessageBox msgBox;
        msgBox.setText("目标database已连接");
        msgBox.exec();
    }



    qDebug() << databasename;
    return 0;
}

int data::grant1(char *str){
    string actions,usern;
    smatch result;
    string s=str;

    regex Exp("( *grant) +(\\w+( *, *\\w+)*) +to +(\\w+) *;?");//提取关键内容
    regex_match(s,result,Exp);


    QString action,tname,uname;

    actions=result[2];
    usern=result[4];
    action=QString::fromStdString(actions);
    uname=QString::fromStdString(usern);
    tname="any";

    cd.grantuser(uname,action,tname);

    qDebug() << action;
    qDebug() << uname;


    return 0;
}

int data::grant2(char *str){
    string actions,tablen,usern;
    smatch result;
    string s=str;

    regex Exp("( *grant) +(\\w+( *, *\\w+)*) +on +(\\w+( *, *\\w+)*) +to +(\\w+) *;?");//提取关键内容
    // *grant +\\w+( *, *\\w+)* +on +\\w+( *, *\\w+)* +to +\\w+ *;?
    regex_match(s,result,Exp);


    QString action,tname,uname;

    actions=result[2];
    tablen=result[4];
    usern=result[6];
    action=QString::fromStdString(actions);
    uname=QString::fromStdString(usern);
    tname=QString::fromStdString(tablen);

    cd.grantuser(uname,action,tname);

    qDebug() << action;
    qDebug() << tname;
    qDebug() << uname;


    return 0;
}

int data::revoke1(char *str){
    string actions,usern;
    smatch result;
    string s=str;

    regex Exp("( *revoke) +(\\w+( *, *\\w+)*) +from +(\\w+) *;?");//提取关键内容
    regex_match(s,result,Exp);


    QString action,tname,uname;

    actions=result[2];
    usern=result[4];
    action=QString::fromStdString(actions);
    uname=QString::fromStdString(usern);
    tname="any";

    qDebug() << action;
    qDebug() << uname;
    cd.revokeuser(uname,action,tname);

    return 0;
}

int data::revoke2(char *str){
    string actions,tablen,usern;
    smatch result;
    string s=str;

    regex Exp("( *revoke) +(\\w+( *, *\\w+)*) +on +(\\w+( *, *\\w+)*) +from +(\\w+) *;?");//提取关键内容
    regex_match(s,result,Exp);


    QString action,tname,uname;

    actions=result[2];
    tablen=result[4];
    usern=result[6];
    action=QString::fromStdString(actions);
    uname=QString::fromStdString(usern);
    tname=QString::fromStdString(tablen);

    cd.revokeuser(uname,action,tname);

    qDebug() << action;
    qDebug() << tname;
    qDebug() << uname;


    return 0;
}

selecttable* data::getST()
{
    return &this->st;
}
