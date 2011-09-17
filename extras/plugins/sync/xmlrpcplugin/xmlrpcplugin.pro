QT       += core gui
TEMPLATE        = lib
CONFIG         += plugin
INCLUDEPATH    += ./
HEADERS         = xmlrpcplugin.h \
    xmlrpcdialog.h
SOURCES         = xmlrpcplugin.cpp \
    xmlrpcdialog.cpp
TARGET          = xmlrpcplugin

unix:OBJECTS_DIR = ./obj/
unix:MOC_DIR = ./obj/
unix:DESTDIR = ../../../../bin/plugins/sync
unix:UI_DIR = ./obj/

FORMS += \
    xmlrpcdialog.ui








