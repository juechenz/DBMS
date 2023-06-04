QT       += core gui
QT += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    altertable.cpp \
    cddatabase.cpp \
    data.cpp \
    deletetable.cpp \
    gramma.cpp \
    inserttable.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    newtable.cpp \
    selecttable.cpp \
    updatetable.cpp \
    utils.cpp

HEADERS += \
    altertable.h \
    cddatabase.h \
    data.h \
    deletetable.h \
    gramma.h \
    info.h \
    inserttable.h \
    login.h \
    mainwindow.h \
    newtable.h \
    selecttable.h \
    updatetable.h \
    utils.h

FORMS += \
    altertable.ui \
    cddatabase.ui \
    deletetable.ui \
    inserttable.ui \
    login.ui \
    mainwindow.ui \
    newtable.ui \
    selecttable.ui \
    updatetable.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    pic.qrc
