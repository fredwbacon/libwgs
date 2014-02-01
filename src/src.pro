TEMPLATE     = lib
TARGET       = wgs
CONFIG      += staticlib debug
CONFIG      -= qt
INCLUDEPATH += ../include

# Input
HEADERS += svm.h \
           wgs.h
SOURCES += svm.c \
           wgs.c

DESTDIR      = ../../Linux-x86_64/SWFView/lib

