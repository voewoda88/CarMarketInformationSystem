QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    additemwindow.cpp \
    admin.cpp \
    allwindows.cpp \
    authwindow.cpp \
    checkint.cpp \
    database.cpp \
    deletewindow.cpp \
    editwindow.cpp \
    exception.cpp \
    items.cpp \
    list.cpp \
    main.cpp \
    mainwindow.cpp \
    registerwindow.cpp \
    resultwindow.cpp \
    searchwindow.cpp \
    user.cpp \
    userwindow.cpp

HEADERS += \
    additemwindow.h \
    admin.h \
    allwindows.h \
    authwindow.h \
    checkint.h \
    database.h \
    deletewindow.h \
    editwindow.h \
    exception.h \
    items.h \
    list.h \
    mainwindow.h \
    registerwindow.h \
    resultwindow.h \
    searchwindow.h \
    user.h \
    userwindow.h

FORMS += \
    additemwindow.ui \
    authwindow.ui \
    deletewindow.ui \
    editwindow.ui \
    mainwindow.ui \
    registerwindow.ui \
    resultwindow.ui \
    searchwindow.ui \
    userwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
