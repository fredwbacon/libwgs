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

linux-g++ {
  DESTDIR      = ../../Linux-x86_64/SWFView/lib64
}

win32 {
  TARGET    = libwgs
  TEMPLATE  = vclib
}
