TEMPLATE = lib

TARGET = CodeCoverage

DEFINES += CODECOVERAGE_LIBRARY

WORK_DIR = /opt/qt-creator-2.5.1-src
#WORK_DIR = /home/evgeny/Documents/qt-creator-2.5.2-src

# Qt Creator linking

## set the QTC_SOURCE environment variable to override the setting here
QTCREATOR_SOURCES = $$(QTC_SOURCE)
isEmpty(QTCREATOR_SOURCES):QTCREATOR_SOURCES=$$WORK_DIR

## set the QTC_BUILD environment variable to override the setting here
IDE_BUILD_TREE = $$(QTC_BUILD)
isEmpty(IDE_BUILD_TREE):IDE_BUILD_TREE=$$WORK_DIR/build

## uncomment to build plugin into user config directory
## <localappdata>/plugins/<ideversion>
##    where <localappdata> is e.g.
##    "%LOCALAPPDATA%\Nokia\qtcreator" on Windows Vista and later
##    "$XDG_DATA_HOME/Nokia/qtcreator" or "~/.local/share/data/Nokia/qtcreator" on Linux
##    "~/Library/Application Support/Nokia/Qt Creator" on Mac
# USE_USER_DESTDIR = yes

PROVIDER = VendorName

LIBS += -L$$IDE_PLUGIN_PATH/Nokia

# CodeCoverage files
include(codecoverage.pri)

QMAKE_CXXFLAGS += -std=c++0x
CXXFLAGS="-std=c++0x" ./configure
