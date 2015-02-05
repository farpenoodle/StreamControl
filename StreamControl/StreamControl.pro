#-------------------------------------------------
#
# Project created by QtCreator 2012-01-06T07:56:02
#
#-------------------------------------------------

QT       += core gui xml widgets network script

TARGET = StreamControl
TEMPLATE = app

SOURCES += *.cpp\
    o2/*.cpp \
    dialogs/*.cpp \
    widgets/*.cpp

HEADERS  += *.h \
    o2/*.h \
    dialogs/*.h \
    widgets/*.h

FORMS    += \
    configwindow.ui

RESOURCES += \
    resources.qrc

RC_FILE = streamcontrol.rc

OTHER_FILES += \
    o2/o2.pri

macx {
    LIBS += -framework Carbon
}

CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT
