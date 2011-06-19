#############################################################################
# Makefile for building: bin/QHDA
# Generated by qmake (2.01a) (Qt 4.7.2) on: ?? ???? 19 15:40:35 2011
# Project:  QHDA.pro
# Template: app
# Command: /usr/bin/qmake-qt4 -spec /usr/share/qt4/mkspecs/linux-g++ CONFIG+=debug QMLJSDEBUGGER_PATH=/usr/share/qtcreator/qml/qmljsdebugger -o Makefile QHDA.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_WEBKIT_LIB -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4/QtWebKit -I/usr/include/qt4 -Iobj -Iobj
LINK          = g++
LFLAGS        = 
LIBS          = $(SUBLIBS)  -L/usr/lib -lQtWebKit -lQtGui -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake-qt4
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = obj/

####### Files

SOURCES       = main.cpp \
		src/qhda.cpp \
		src/qcorewindow.cpp \
		src/databasemanager.cpp \
		src/bookwizard.cpp \
		src/tabelofcontent.cpp \
		src/tabedwebbrowser.cpp obj/moc_qhda.cpp \
		obj/moc_qcorewindow.cpp \
		obj/moc_databasemanager.cpp \
		obj/moc_bookwizard.cpp \
		obj/moc_tabelofcontent.cpp \
		obj/moc_tabedwebbrowser.cpp \
		qrc_qhda.cpp
OBJECTS       = obj/main.o \
		obj/qhda.o \
		obj/qcorewindow.o \
		obj/databasemanager.o \
		obj/bookwizard.o \
		obj/tabelofcontent.o \
		obj/tabedwebbrowser.o \
		obj/moc_qhda.o \
		obj/moc_qcorewindow.o \
		obj/moc_databasemanager.o \
		obj/moc_bookwizard.o \
		obj/moc_tabelofcontent.o \
		obj/moc_tabedwebbrowser.o \
		obj/qrc_qhda.o
DIST          = /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		QHDA.pro
QMAKE_TARGET  = QHDA
DESTDIR       = bin/
TARGET        = bin/QHDA

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET): obj/ui_qhda.h obj/ui_bookwizard.h $(OBJECTS)  
	@$(CHK_DIR_EXISTS) bin/ || $(MKDIR) bin/ 
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: QHDA.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/lib/libQtWebKit.prl \
		/usr/lib/libQtGui.prl \
		/usr/lib/libQtCore.prl
	$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ CONFIG+=debug QMLJSDEBUGGER_PATH=/usr/share/qtcreator/qml/qmljsdebugger -o Makefile QHDA.pro
/usr/share/qt4/mkspecs/common/g++.conf:
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/debug.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/lib/libQtWebKit.prl:
/usr/lib/libQtGui.prl:
/usr/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ CONFIG+=debug QMLJSDEBUGGER_PATH=/usr/share/qtcreator/qml/qmljsdebugger -o Makefile QHDA.pro

dist: 
	@$(CHK_DIR_EXISTS) obj/QHDA1.0.0 || $(MKDIR) obj/QHDA1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) obj/QHDA1.0.0/ && $(COPY_FILE) --parents headers/qhda.h headers/qcorewindow.h headers/databasemanager.h extras/dbmanagerinterface.h headers/bookwizard.h headers/tabelofcontent.h headers/tabedwebbrowser.h extras/editorinterface.h obj/QHDA1.0.0/ && $(COPY_FILE) --parents resource/qhda.qrc obj/QHDA1.0.0/ && $(COPY_FILE) --parents main.cpp src/qhda.cpp src/qcorewindow.cpp src/databasemanager.cpp src/bookwizard.cpp src/tabelofcontent.cpp src/tabedwebbrowser.cpp obj/QHDA1.0.0/ && $(COPY_FILE) --parents ui/qhda.ui ui/bookwizard.ui obj/QHDA1.0.0/ && $(COPY_FILE) --parents lang/qhda_ru.ts lang/qhda_def.ts lang/qhda_en.ts obj/QHDA1.0.0/ && (cd `dirname obj/QHDA1.0.0` && $(TAR) QHDA1.0.0.tar QHDA1.0.0 && $(COMPRESS) QHDA1.0.0.tar) && $(MOVE) `dirname obj/QHDA1.0.0`/QHDA1.0.0.tar.gz . && $(DEL_FILE) -r obj/QHDA1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: obj/moc_qhda.cpp obj/moc_qcorewindow.cpp obj/moc_databasemanager.cpp obj/moc_bookwizard.cpp obj/moc_tabelofcontent.cpp obj/moc_tabedwebbrowser.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) obj/moc_qhda.cpp obj/moc_qcorewindow.cpp obj/moc_databasemanager.cpp obj/moc_bookwizard.cpp obj/moc_tabelofcontent.cpp obj/moc_tabedwebbrowser.cpp
obj/moc_qhda.cpp: headers/qcorewindow.h \
		headers/databasemanager.h \
		extras/dbmanagerinterface.h \
		extras/editorinterface.h \
		headers/qhda.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) headers/qhda.h -o obj/moc_qhda.cpp

obj/moc_qcorewindow.cpp: headers/qcorewindow.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) headers/qcorewindow.h -o obj/moc_qcorewindow.cpp

obj/moc_databasemanager.cpp: extras/dbmanagerinterface.h \
		headers/databasemanager.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) headers/databasemanager.h -o obj/moc_databasemanager.cpp

obj/moc_bookwizard.cpp: extras/dbmanagerinterface.h \
		headers/bookwizard.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) headers/bookwizard.h -o obj/moc_bookwizard.cpp

obj/moc_tabelofcontent.cpp: headers/tabelofcontent.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) headers/tabelofcontent.h -o obj/moc_tabelofcontent.cpp

obj/moc_tabedwebbrowser.cpp: headers/tabedwebbrowser.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) headers/tabedwebbrowser.h -o obj/moc_tabedwebbrowser.cpp

compiler_rcc_make_all: qrc_qhda.cpp
compiler_rcc_clean:
	-$(DEL_FILE) qrc_qhda.cpp
qrc_qhda.cpp: resource/qhda.qrc \
		resource/qhda.png \
		resource/actions/folder_grey.png \
		resource/actions/folder_sent_mail.png \
		resource/actions/viewmag1.png \
		resource/actions/wizard.png \
		resource/actions/contexthelp.png \
		resource/actions/db_status.png \
		resource/actions/webexport.png \
		resource/actions/folder.png \
		resource/actions/find.png \
		resource/actions/fileprint.png \
		resource/actions/db_remove.png \
		resource/actions/tab_new.png \
		resource/actions/filesave.png \
		resource/actions/folder_new.png \
		resource/actions/edit_add.png \
		resource/actions/db_update.png \
		resource/actions/edit.png \
		resource/actions/filequickprint.png \
		resource/actions/signature.png \
		resource/actions/folder_green.png \
		resource/actions/tab_new_raised.png \
		resource/actions/viewmag-.png \
		resource/actions/tab_duplicate.png \
		resource/actions/db_comit.png \
		resource/actions/db.png \
		resource/actions/tab.png \
		resource/actions/findf.png \
		resource/actions/edit_remove.png \
		resource/actions/folder_documents.png \
		resource/actions/db_add.png \
		resource/actions/viewmag+.png \
		resource/actions/mime_postscript.png
	/usr/bin/rcc -name qhda resource/qhda.qrc -o qrc_qhda.cpp

compiler_image_collection_make_all: obj/qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) obj/qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: obj/ui_qhda.h obj/ui_bookwizard.h
compiler_uic_clean:
	-$(DEL_FILE) obj/ui_qhda.h obj/ui_bookwizard.h
obj/ui_qhda.h: ui/qhda.ui \
		headers/tabelofcontent.h \
		headers/tabedwebbrowser.h
	/usr/bin/uic-qt4 ui/qhda.ui -o obj/ui_qhda.h

obj/ui_bookwizard.h: ui/bookwizard.ui
	/usr/bin/uic-qt4 ui/bookwizard.ui -o obj/ui_bookwizard.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_rcc_clean compiler_uic_clean 

####### Compile

obj/main.o: main.cpp headers/qhda.h \
		headers/qcorewindow.h \
		headers/databasemanager.h \
		extras/dbmanagerinterface.h \
		extras/editorinterface.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/main.o main.cpp

obj/qhda.o: src/qhda.cpp headers/qhda.h \
		headers/qcorewindow.h \
		headers/databasemanager.h \
		extras/dbmanagerinterface.h \
		extras/editorinterface.h \
		obj/ui_qhda.h \
		headers/tabedwebbrowser.h \
		headers/tabelofcontent.h \
		headers/bookwizard.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/qhda.o src/qhda.cpp

obj/qcorewindow.o: src/qcorewindow.cpp headers/qcorewindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/qcorewindow.o src/qcorewindow.cpp

obj/databasemanager.o: src/databasemanager.cpp headers/databasemanager.h \
		extras/dbmanagerinterface.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/databasemanager.o src/databasemanager.cpp

obj/bookwizard.o: src/bookwizard.cpp headers/bookwizard.h \
		extras/dbmanagerinterface.h \
		obj/ui_bookwizard.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/bookwizard.o src/bookwizard.cpp

obj/tabelofcontent.o: src/tabelofcontent.cpp headers/tabelofcontent.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/tabelofcontent.o src/tabelofcontent.cpp

obj/tabedwebbrowser.o: src/tabedwebbrowser.cpp headers/tabedwebbrowser.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/tabedwebbrowser.o src/tabedwebbrowser.cpp

obj/moc_qhda.o: obj/moc_qhda.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_qhda.o obj/moc_qhda.cpp

obj/moc_qcorewindow.o: obj/moc_qcorewindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_qcorewindow.o obj/moc_qcorewindow.cpp

obj/moc_databasemanager.o: obj/moc_databasemanager.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_databasemanager.o obj/moc_databasemanager.cpp

obj/moc_bookwizard.o: obj/moc_bookwizard.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_bookwizard.o obj/moc_bookwizard.cpp

obj/moc_tabelofcontent.o: obj/moc_tabelofcontent.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_tabelofcontent.o obj/moc_tabelofcontent.cpp

obj/moc_tabedwebbrowser.o: obj/moc_tabedwebbrowser.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_tabedwebbrowser.o obj/moc_tabedwebbrowser.cpp

obj/qrc_qhda.o: qrc_qhda.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/qrc_qhda.o qrc_qhda.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

