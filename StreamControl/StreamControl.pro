#-------------------------------------------------
#
# Project created by QtCreator 2012-01-06T07:56:02
#
#-------------------------------------------------

QT       += core gui xml widgets network script

TARGET = StreamControl
TEMPLATE = app

SOURCES += *.cpp \
    $$files(o2/*.cpp) \
    $$files(dialogs/*.cpp) \
    $$files(widgets/*.cpp)

HEADERS  += *.h \
    $$files(o2/*.h) \
    $$files(dialogs/*.h) \
    $$files(widgets/*.h)

FORMS    += \
    configwindow.ui

RESOURCES += \
    resources.qrc

RC_FILE = streamcontrol.rc

OTHER_FILES += \
    o2/o2.pri

win32{
    SOURCES += windows/win_keyhelper.cpp

    HEADERS += windows/win_keyhelper.h
}

macx {
    LIBS += -framework Carbon
}

CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT
