QT       += core sql
TEMPLATE        = lib
CONFIG         += plugin
INCLUDEPATH    += ./
HEADERS         = sqliteplugin.h
SOURCES         = sqliteplugin.cpp
TARGET          = sqliteplugin

unix:OBJECTS_DIR = ./obj/
unix:MOC_DIR = ./obj/
unix:DESTDIR = ../../../../bin/plugins/db
unix:UI_DIR = ./obj/

RESOURCES += \
    sqlite_res.qrc
