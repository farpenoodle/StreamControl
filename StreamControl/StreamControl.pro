#-------------------------------------------------
#
# Project created by QtCreator 2012-01-06T07:56:02
#
#-------------------------------------------------

QT       += core gui xml widgets network script

TARGET = StreamControl
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    configwindow.cpp \
    csv.cpp \
    ScCompleter.cpp \
    ScLineEdit.cpp \
    ScComboBox.cpp \
    errorchecking.cpp \
    scradiogroup.cpp \
    twitterwidget.cpp \
    o2/simplecrypt.cpp \
    o2/oxtwitter.cpp \
    o2/o2skydrive.cpp \
    o2/o2requestor.cpp \
    o2/o2replyserver.cpp \
    o2/o2reply.cpp \
    o2/o2gft.cpp \
    o2/o2facebook.cpp \
    o2/o2.cpp \
    o2/o1requestor.cpp \
    o2/o1.cpp \
    o2twitter.cpp \
    o2/o2settingsstore.cpp \
    sctsbutton.cpp \
    twitterhandler.cpp \
    win_keyhelper.cpp \
    scsetbutton.cpp

HEADERS  += mainwindow.h \
    configwindow.h \
    config.h \
    csv.h \
    ScCompleter.h \
    ScLineEdit.h \
    ScComboBox.h \
    scradiogroup.h \
    twitterwidget.h \
    twitterOauth.h \
    o2/simplecrypt.h \
    o2/oxtwitter.h \
    o2/o2skydrive.h \
    o2/o2requestor.h \
    o2/o2replyserver.h \
    o2/o2reply.h \
    o2/o2globals.h \
    o2/o2gft.h \
    o2/o2facebook.h \
    o2/o2.h \
    o2/o1twitter.h \
    o2/o1requestor.h \
    o2/o1flickr.h \
    o2/o1dropbox.h \
    o2/o1.h \
    o2twitter.h \
    o2/o2abstractstore.h \
    o2/o2settingsstore.h \
    sctsbutton.h \
    twitterhandler.h \
    win_keyhelper.h \
    scsetbutton.h

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
