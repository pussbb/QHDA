#-------------------------------------------------
#
# Project created by QtCreator 2011-04-06T20:49:33
#
#-------------------------------------------------

QT       += core gui webkit

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
    src/databasemanager.cpp

HEADERS  += headers/qhda.h \
    headers/qcorewindow.h \
    headers/databasemanager.h

FORMS    += ui/qhda.ui
