#-------------------------------------------------
#
# Project created by QtCreator 2016-06-19T15:48:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyQiniu
TEMPLATE = app

LIBS += -lcurl -lssl -lcrypto -lm

SOURCES += main.cpp\
        myqiniu.cpp\
        sdk/b64/urlsafe_b64.c\
        sdk/cJSON/cJSON.c\
        sdk/qiniu/conf.c\
        sdk/qiniu/base.c\
        sdk/qiniu/base_io.c\
        sdk/qiniu/http.c\
        sdk/qiniu/auth_mac.c\
        sdk/qiniu/rs.c\
        sdk/qiniu/io.c \
    setdialog.cpp

HEADERS  += myqiniu.h \
    qiniuinit.h \
    setdialog.h \
    configfile.h

FORMS    += myqiniu.ui \
    setdialog.ui
