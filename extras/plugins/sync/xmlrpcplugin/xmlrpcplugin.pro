QT       += core gui network xml

TEMPLATE        = lib

CONFIG         += plugin

INCLUDEPATH    += ./

HEADERS         = xmlrpcplugin.h \
    xmlrpcdialog.h

SOURCES         = xmlrpcplugin.cpp \
    xmlrpcdialog.cpp

TARGET          = xmlrpcplugin

unix {
    OBJECTS_DIR = ./obj/
    MOC_DIR = ./obj/
    DESTDIR = ../../../../bin/plugins/sync
    UI_DIR = ./obj/
}

TRANSLATIONS = ./lang/libxmlrpcplugin_qhda_ru.ts \
                ./lang/libxmlrpcplugin_qhda_def.ts \
                ./lang/libxmlrpcplugin_qhda_en.ts \

FORMS += \
    xmlrpcdialog.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/qxmlrpc_lib/ -lqxmlrpc
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/qxmlrpc_lib/ -lqxmlrpcd
else:unix:!macx:!symbian: LIBS += -L$$PWD/qxmlrpc_lib/ -lqxmlrpc

INCLUDEPATH += $$PWD/qxmlrpc_lib/
DEPENDPATH += $$PWD/qxmlrpc_lib/

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/qxmlrpc_lib/qxmlrpc.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/qxmlrpc_lib/qxmlrpcd.lib
else:unix:!macx:!symbian: PRE_TARGETDEPS += $$PWD/qxmlrpc_lib/libqxmlrpc.a

RESOURCES += \
    ./res/res.qrc

