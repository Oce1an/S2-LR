QT -= gui
TARGET = StringLib
TEMPLATE = lib
CONFIG += dll

DEFINES += STRINGLIB_EXPORTS

SOURCES += ../mystring.cpp
HEADERS += ../mystring.h

win32: DESTDIR = ../bin
unix:  DESTDIR = ../bin