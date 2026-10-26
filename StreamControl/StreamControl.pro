#-------------------------------------------------
#
# Project created by QtCreator 2012-01-06T07:56:02
#
#-------------------------------------------------

QT       += core gui xml widgets network websockets

TARGET = StreamControl
TEMPLATE = app

SOURCES += *.cpp \
    $$files(dialogs/*.cpp) \
    $$files(widgets/*.cpp)

HEADERS  += *.h \
    $$files(dialogs/*.h) \
    $$files(widgets/*.h)

FORMS    += \
    configwindow.ui

RESOURCES += \
    resources.qrc

RC_FILE = streamcontrol.rc

macx {
    LIBS += -framework Carbon
}


win32 {
    LIBS += -luser32
}

CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT
