#-------------------------------------------------
#
# Project created by QtCreator 2012-01-06T07:56:02
#
#-------------------------------------------------

QT       += core gui xml

TARGET = StreamControl
TEMPLATE = app


CONFIG += static
static { // Everything below takes effect with CONFIG += static
    CONFIG += static
    DEFINES += STATIC
    message("Static build.")
}

SOURCES += main.cpp\
        mainwindow.cpp \
    configwindow.cpp

HEADERS  += mainwindow.h \
    configwindow.h \
    config.h

FORMS    += mainwindow.ui \
    configwindow.ui

RESOURCES += \
    resources.qrc
