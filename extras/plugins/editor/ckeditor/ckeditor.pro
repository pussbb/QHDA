QT       += core gui webkit
TEMPLATE        = lib
CONFIG         += plugin
INCLUDEPATH    += ./
HEADERS         = ckeditor.h \
    editor.h
SOURCES         = ckeditor.cpp \
    editor.cpp
TARGET          = ckeditor

unix:OBJECTS_DIR = ./obj/
unix:MOC_DIR = ./obj/
unix:DESTDIR = ../../../../bin/plugins/editor
unix:UI_DIR = ./obj/

FORMS += \
    editor.ui

RESOURCES += \
    res.qrc
TRANSLATIONS = ./lang/libckeditor_qhda_ru.ts \
                ./lang/libckeditor_qhda_def.ts \
                ./lang/libckeditor_qhda_en.ts \
