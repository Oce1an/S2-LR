QT      += testlib core
CONFIG  += qt console warn_on testcase
CONFIG  -= app_bundle

TARGET   = tst_task1
TEMPLATE = app

SOURCES += tst_task1.cpp \
           trainer.cpp

HEADERS += trainer.h
