QT      += testlib core
CONFIG  += qt console warn_on testcase
CONFIG  -= app_bundle

TARGET   = tst_task3
TEMPLATE = app

SOURCES += tst_task3.cpp \
           mybitset.cpp

HEADERS += mybitset.h
