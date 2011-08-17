#-------------------------------------------------
#
# Project created by QtCreator 2011-04-06T20:49:33
#
#-------------------------------------------------


QT       += core gui webkit help

TARGET = QHDA
TEMPLATE = app
unix:OBJECTS_DIR = ./obj/
unix:MOC_DIR = ./obj/
unix:DESTDIR = ./bin/
unix:UI_DIR = ./obj/

TRANSLATIONS = ./lang/qhda_ru.ts \
                ./lang/qhda_def.ts \
                ./lang/qhda_en.ts \

SOURCES += main.cpp\
        src/qhda.cpp \
    src/qcorewindow.cpp \
    src/databasemanager.cpp \
    src/bookwizard.cpp \
    src/tabelofcontent.cpp \
    src/tabedwebbrowser.cpp \
    src/templateengine.cpp \
    src/settings.cpp \
    src/plugininfo.cpp \
    src/about.cpp \
    src/renderpdf.cpp

HEADERS  += headers/qhda.h \
    headers/qcorewindow.h \
    headers/databasemanager.h \
    extras/dbmanagerinterface.h \
    headers/bookwizard.h \
    headers/tabelofcontent.h \
    headers/tabedwebbrowser.h \
    extras/editorinterface.h \
    extras/widgets/treebox.h \
    headers/templateengine.h \
    headers/settings.h \
    headers/plugininfo.h \
    headers/about.h \
    headers/renderpdf.h

FORMS    += ui/qhda.ui \
    ui/bookwizard.ui \
    ui/settings.ui \
    ui/plugininfo.ui \
    ui/about.ui

RESOURCES += \
    resource/qhda.qrc
