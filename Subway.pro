#-------------------------------------------------
#
# Project created by QtCreator 2024-05-18T21:04:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Subway
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
    widget_log.cpp \
    widget.cpp \
    widget_sign.cpp \
    user_widget.cpp \
    userinformation.cpp \
    userpay_widget.cpp \
    userbuyticket_widget.cpp \
    adm_mainwindow.cpp \
    subwayline.cpp \
    subschedule_widget.cpp

HEADERS += \
    widget_log.h \
    widget.h \
    widget_sign.h \
    user_widget.h \
    userinformation.h \
    userpay_widget.h \
    userbuyticket_widget.h \
    adm_mainwindow.h \
    subwayline.h \
    subschedule_widget.h

FORMS += \
    widget_log.ui \
    widget.ui \
    widget_sign.ui \
    user_widget.ui \
    userpay_widget.ui \
    userbuyticket_widget.ui \
    adm_mainwindow.ui \
    subschedule_widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    pic.qrc

DISTFILES +=
