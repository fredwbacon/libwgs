TEMPLATE     = app
TARGET       = wgsreader
INCLUDEPATH += ../include
CONFIG      += debug
CONFIG      -= qt
LIBS        += -L../../Linux-x86_64/SWFView/lib -lwgs -lm

# Input
SOURCES += main.c

