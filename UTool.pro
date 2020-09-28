#-------------------------------------------------
#
# Project created by QtCreator 2018-10-27T21:06:36
#
#-------------------------------------------------

QT += core gui
QT -= network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UTool
TEMPLATE = app

DESTDIR += $${PWD}/output

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
    main.cpp

HEADERS +=

FORMS += \
    hsaeencrypttool.ui \
    hsaemessagebox.ui

RESOURCES += \
        $$PWD/image/main.qrc \
        $$PWD/qss/qss.qrc \
        $$PWD/icon/icon.qrc

include ($$PWD/src/src.pri)

RC_ICONS += $$PWD/icon/logo.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += $$PWD/lib/openssl/include
DEPENDPATH  += $$PWD/lib/openssl/include

win32 {
    LIBS += -L$$PWD/lib/openssl/lib32 -llibeay32
    LIBS += -L$$PWD/lib/openssl/lib32 -lssleay32
}
