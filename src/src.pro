TEMPLATE     = lib
TARGET       = wgs
CONFIG      += staticlib 
INCLUDEPATH += ../include
VERSION      = 1.0.0

include(../share/wgsbuild.pri)
include(../share/wgsconfig.pri)

# Input
HEADERS += ../include/svm.h \
           ../include/wgs.h
SOURCES += svm.c \
           wgs.c

linux {
  DESTDIR       = ${SOLUTIONDIR}/Linux-x86_64/libwgs/lib
}


win32 {
  TARGET        = libwgs
  CONFIG(debug, debug|release) {
    TARGET      = $$join(TARGET,,,d)
  }

  DEFINES      += _CRT_SECURE_NO_DEPRECATE
  GUID          = B2FA754D-5959-37D7-B1CC-96888E0AFE82
}


macx {
  TARGET        = wgs
  CONFIG(debug, debug|release) {
   TARGET       = $$join(TARGET,,,_debug)
  }

  DESTDIR       = ${SOLUTIONDIR}/Darwin-x86_64/libwgs/lib
}

target.path     = $${WGS_INSTALL_LIBS}
INSTALLS       += target

CONFIG(release,debug|release) {
  help.path     = $${WGS_INSTALL_DOCS}/html
  help.files    = ../doc/api/html/*

  tags.path     = $${WGS_INSTALL_DOCS}
  tags.files    = ../doc/libwgs.tag

  pdf.path      = $${WGS_INSTALL_DOCS}
  pdf.files     = ../doc/libwgs.pdf

  qch.path      = $${WGS_INSTALL_DOCS}
  qch.files     = ../doc/libwgs.qch

  prf.path      = $${WGS_FEATURES_PATH}
  prf.files     = ../share/wgs.prf ../share/wgsconfig.pri

  headers.path  = $${WGS_INSTALL_HEADERS}
  headers.files = $${HEADERS}

  INSTALLS     += headers prf help tags pdf qch
}

