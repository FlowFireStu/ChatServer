QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    abstractprocess.cpp \
    account.cpp \
    accountmanager.cpp \
    addfriendprocess.cpp \
    createaccountprocess.cpp \
    getofflinemessageprocess.cpp \
    loginprocess.cpp \
    logoutprocess.cpp \
    main.cpp \
    offlinemessagemanager.cpp \
    onlinestatemanager.cpp \
    processfactory.cpp \
    sendmessageprocess.cpp \
    widget.cpp \
    workthread.cpp

HEADERS += \
    abstractprocess.h \
    account.h \
    accountmanager.h \
    addfriendprocess.h \
    createaccountprocess.h \
    getofflinemessageprocess.h \
    loginprocess.h \
    logoutprocess.h \
    offlinemessagemanager.h \
    onlinestatemanager.h \
    processfactory.h \
    sendmessageprocess.h \
    widget.h \
    workthread.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target