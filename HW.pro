# -------------------------------------------------
# Project created by QtCreator 2009-12-02T17:08:35
# -------------------------------------------------
QT += network \
    sql \
    webkit \
    xml
TARGET = HW
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    aliasgui/newbook/newbook.cpp \
    aliasgui/inserttable/inserttable.cpp \
    aliasgui/imgprop.cpp \
    aliasgui/settings.cpp \
    aliasgui/href.cpp \
    aliasgui/syncmain.cpp \
    aliasgui/syntaxhilight.cpp \
    aliasgui/adifference.cpp \
    aliasgui/about.cpp
HEADERS += mainwindow.h \
    aliasgui/newbook/newbook.h \
    aliasgui/inserttable/inserttable.h \
    aliasgui/imgprop.h \
    aliasgui/settings.h \
    aliasgui/href.h \
    aliasgui/syncmain.h \
    aliasgui/syntaxhilight.h \
    aliasgui/adifference.h \
    aliasgui/about.h
FORMS += mainwindow.ui \
    aliasgui/newbook/newbook.ui \
    aliasgui/inserttable/inserttable.ui \
    aliasgui/imgprop.ui \
    aliasgui/settings.ui \
    aliasgui/href.ui \
    aliasgui/syncmain.ui \
    aliasgui/syntaxhilight.ui \
    aliasgui/adifference.ui \
    aliasgui/about.ui
RESOURCES += res/main.qrc
OTHER_FILES += newbook.sql
unix { 
    CONFIG(debug, debug|release):LIBS += ./lib/libqxmlrpc_debug.a
    else:LIBS += ./lib/libqxmlrpc.a
}
