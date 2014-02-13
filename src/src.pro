TEMPLATE     = lib
TARGET       = wgs
CONFIG      += staticlib debug
CONFIG      -= qt
INCLUDEPATH += ../include
LANGUAGE     = C

# Input
HEADERS += svm.h \
           wgs.h
SOURCES += svm.c \
           wgs.c


linux-g++ {
  DESTDIR      = ../../Linux-x86_64/SWFView/lib
}

win32 {
  TEMPLATE         = vclib
  TARGET           = wgs
  DEFINES         += _CRT_SECURE_NO_DEPRECATE
  GUID             = B2FA754D-5959-37D7-B1CC-96888E0AFE82
  CONFIG(release, debug|release) {
    DESTDIR        = release
  }
  CONFIG(debug, debug|release) {
    TARGET         = wgsd
    DESTDIR        = debug
  }
}