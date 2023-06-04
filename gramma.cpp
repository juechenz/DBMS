#include "gramma.h"
#include <QRegExp>
#include <QRegularExpression>
#include <regex>
using namespace std;

int gramma::translate(int model,QString str)

{

    if(str.indexOf("primary ") != -1)
    {
        str.replace("primary ","primary");
    }

    if(str.indexOf("not ") != -1)
    {
        str.replace("not ","not");
    }
    if(str.indexOf(" by") != -1)
    {
        str.replace(" by","by");
    }


    QByteArray ba=str.toLatin1();
    char *s=ba.data();

    switch(model)
    {

    case CREATETABLE:{
        qDebug() << "CREATETABLE";
        qDebug() <<s;
        model=99;



        if(regex_match(s,regex(" *create +table +\\w+ *\\( *\\w+ +\\w+(\\(\\d*\\)){1} *(primarykey)?(unique)?(notnull)?( *default +\\d+)? *(, *\\w+ +\\w+(\\(\\d*\\)){1} *(primarykey)?(unique)?(notnull)?( *default +\\d+)? *)*\\) *;?"))){


            qDebug() << "CREATETABLE";
            model=CREATETABLE;
            da.createtable(s);

            }
        }
        break;
    case DROPTABLE:{
        model=99;

        if(regex_match(s,regex(" *drop +table +(\\w+\\.)?\\w+ *;?"))){
            //" *drop +table +[\\xe4b880-e9bea50-9.a-zA-Z-+]+ *;?"

            qDebug() << "DROPTABLE";
            model=DROPTABLE;
            da.droptable(s);
        }

        }
        break;
    case ALTERTABLEADD:{
        model=99;
        if(regex_match(s, regex(" *alter +table +(\\w+\\.)?\\w+ +add +\\w+ +\\w+(\\(\\d*\\)){1} *(primarykey)?(unique)?(notnull)?( *default +\\d+)? *;?")))//增加字段语句
        {
            qDebug() << "ALTERTABLEADD";
            model=ALTERTABLEADD;
            da.alteradd(s);
        }

        }
        break;
    case ALTERTABLEMODIFY:{
        model=99;
        if(regex_match(s, regex(" *alter +table +(\\w+\\.)?\\w+ +modify +\\w+ +\\w+(\\(\\d*\\))+ *;?")))//修改字段语句
        {
            qDebug() << "ALTERTABLEMODIFY1";
            model=ALTERTABLEMODIFY;
            da.altermodify1(s);
        }else if(regex_match(s, regex(" *alter +table +(\\w+\\.)?\\w+ +modify +\\w+ *(primarykey)?(unique)?(notnull)?( *default +\\d+)? *;?")))//修改字段语句
        {
            qDebug() << "ALTERTABLEMODIFY2";
            model=ALTERTABLEMODIFY;
            da.altermodify2(s);
        }

        }
        break;
    case ALTERTABLEDROP:{
        model=99;
        if(regex_match(s, regex(" *alter +table +(\\w+\\.)?\\w+ +drop column +\\w+ *;?")))//删除字段语句
        {
            qDebug() << "ALTERTABLEDROP";
            model=ALTERTABLEDROP;
            da.alterdrop(s);
        }

        }
        break;
    case RENAME:{
        model=99;
        if(regex_match(s, regex(" *alter +table +(\\w+\\.)?\\w+ +rename column +\\w+ +to +\\w+ *;?")))//删除字段语句
        {//
            qDebug() << "RENAME";
            model=RENAME;
            da.alterrename(s);
        }

        }
        break;
    case INSERT:{
        model=99;
        if(regex_match(s, regex(" *insert +into +(\\w+\\.)?\\w+ +\\(\\w+( *, *\\w+)*\\) +values *\\( *'?\\w+'?( *, *'?\\w+'?)* *\\) *;?")))
        {
            qDebug() << "INSERT";
            model=INSERT;
            da.datainsert(s);
        }
        if(regex_match(s, regex(" *insert +into +(\\w+\\.)?\\w+ +values *\\( *'?\\w+'?( *, *'?\\w+'?)* *\\) *;?")))
        {
            qDebug() << "INSERT";
            model=INSERT;
            da.datainsert2(s);
        }

        }
        break;
    case UPDATE:{
        model=99;
        if(regex_match(s, regex(" *update +(\\w+\\.)?\\w+ +set +\\w+='?\\w+'?( +where +\\w+[><=]=?'?\\w+'?( +and +\\w+[><=]=?'?\\w+'?)*)? *;?"))){
            qDebug() << "UPDATE";
            model=UPDATE;
            da.dataupdate(s);
            }

        }
        break;
    case SELECTWHERE:{
        model=99;
        if(regex_match(s, regex(" *select *\\* *from +(\\w+\\.)?\\w+( *, *(\\w+\\.)?\\w+)*( +where +(\\w+\\.)?\\w+[><=]=?'?(\\w+\\.)?\\w+?'?( +and +(\\w+\\.)?\\w+?[><=]=?'?(\\w+\\.)?\\w+?'?)*)?( +orderby +(\\w+\\.)?\\w+( *, *(\\w+\\.)?\\w+)* +(desc)?(asc)?)? *;?")))
            //
             // *select *\\* *from (\\w+.)?w+( *, *(\\w+.)?\\w+)* +(*where +\\w+='?\\w+'?( +and +\\w+='?\\w+'?)*)? *;?
        {
            qDebug() << "SELECT*WHERE";
            model=SELECTWHERE;
            da.dataselectall(s);
        }
        else if(regex_match(s, regex(" *select +(\\w+\\.)?\\w+( *, *(\\w+\\.)?\\w+)* +from +(\\w+\\.)?\\w+( *, *(\\w+\\.)?\\w+)*( +where +(\\w+\\.)?\\w+?='?(\\w+\\.)?\\w+?'?( +and +(\\w+\\.)?\\w+?='?(\\w+\\.)?\\w+?'?)*)?( +orderby +(\\w+\\.)?\\w+( *, *(\\w+\\.)?\\w+)* +(desc)?(asc)?)? *;?")))
        {
            qDebug() << "SELECTWHERE";
            model=SELECTWHERE;
            da.dataselectsome(s);
        }

        }
        break;
    case DELETE:{
        model=99;
        if(regex_match(s, regex(" *delete +from +(\\w+\\.)?\\w+( +where +\\w+[><=]=?'?\\w+'?( +and +\\w+[><=]=?'?\\w+'?)*)? *;?"))){
            qDebug() << "DELETE";
            model=DELETE;
            da.datadelete(s);
         }

        }
        break;

    case CREATEDATABASE:{
        model=99;
        if(regex_match(s, regex(" *create +database +\\w+ *;?"))){
            qDebug() << "CREATEDATABASE";
            model=CREATEDATABASE;
            da.createdatabse(s);
         }

        }
        break;
    case DROPDATABASE:{
        model=99;
        if(regex_match(s,regex(" *drop +database +\\w+ *;?"))){
            qDebug() << "DROPDATABASE";
            model=DROPDATABASE;
            da.dropdatabse(s);
         }

        }
        break;

    case USEDATABASE:{
        model=99;
        if(regex_match(s,regex(" *use +\\w+ *;?"))){
            qDebug() << "USEDATABASE";
            model=USEDATABASE;
            da.usedatabse(s);
         }

        }
        break;

    case GRANT:{
        model=99;



        if(regex_match(s,regex(" *grant +\\w+( *, *\\w+)* +to +\\w+ *;?"))){
            //" *grant +\\w+( *, *\\w+)* +on +\\w+( *, *\\w+)* +to +\\w+ *;?"
            qDebug() << "GRANT";
            model=GRANT;
            da.grant1(s);
         }
        else if(regex_match(s,regex(" *grant +\\w+( *, *\\w+)* +on +\\w+( *, *\\w+)* +to +\\w+ *;?"))){
            //" *grant +\\w+( *, *\\w+)* +on +\\w+( *, *\\w+)* +to +\\w+ *;?"
            qDebug() << "GRANT";
            model=GRANT;
            da.grant2(s);
         }

        }
        break;

    case REVOKE:{
        model=99;
        if(regex_match(s,regex(" *revoke +\\w+( *, *\\w+)* +from +\\w+ *;?"))){
            qDebug() << "REVOKE";
            model=REVOKE;
            da.revoke1(s);
         }
        else if(regex_match(s,regex(" *revoke +\\w+( *, *\\w+)* +on +\\w+( *, *\\w+)* +from +\\w+ *;?"))){
            qDebug() << "REVOKE";
            model=REVOKE;
            da.revoke2(s);
         }

        }
        break;
    case WRONGREGEX:{
        qDebug() << "WRONGREGEX";

        }
        break;
    }
    return model;

}

