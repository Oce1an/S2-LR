QT      += testlib core
CONFIG  += qt console warn_on testcase
CONFIG  -= app_bundle

TARGET   = tst_task2
TEMPLATE = app

SOURCES += tst_task2.cpp \
           mystring.cpp

HEADERS += mystring.h
