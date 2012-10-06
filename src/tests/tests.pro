QT       += testlib

TARGET = tst_CodeCoverageTest
DESTDIR = ./../../bin/

CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += tst_CodeCoverageTest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

OBJECTS_DIR = .obj/debug-shared
MOC_DIR = .moc/debug-shared

QTCREATOR_SOURCES = $$(QTC_SOURCE)
isEmpty(QTCREATOR_SOURCES):QTCREATOR_SOURCES=/home/evgeny/Documents/qt-creator-2.5.2-src
#isEmpty(QTCREATOR_SOURCES):QTCREATOR_SOURCES=/opt/qt-creator-2.5.1-src

IDE_BUILD_TREE = $$(QTC_BUILD)
isEmpty(IDE_BUILD_TREE):IDE_BUILD_TREE=/home/evgeny/Documents/qt-creator-2.5.2-src/build
#isEmpty(IDE_BUILD_TREE):IDE_BUILD_TREE=/opt/qt-creator-2.5.1-src/build

#TEST_DIR =
DEFINES += \
    TEST_DIR=\\\"/home/evgeny/Dropbox/QtSandbox/CodeCoverage/other/TestDir\\\"

include(../lib/codecoverage.pri)

INCLUDEPATH += ../lib
DEPENDPATH += ../lib

#LIBS += -lgcov
#QMAKE_CXXFLAGS += -g -Wall -fprofile-arcs -ftest-coverage -O0

QMAKE_CXXFLAGS += -std=c++0x
CXXFLAGS="-std=c++0x" ./configure
