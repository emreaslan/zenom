#--------------------------------------------------------------
#
# Zenom Hard Real-Time Simulation Enviroment
# Copyright (C) 2013
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the Zenom License, Version 1.0
#
#--------------------------------------------------------------

include( ../../zenom.pri )

QT       += core
QT       -= gui

TARGET = znm-target
TEMPLATE = lib

DEFINES += ZNMTARGET_LIBRARY

SOURCES += arduinomanager.cpp \
    targetmanager.cpp \
    targetreaderwritertask.cpp

HEADERS += arduinomanager.h\
    targetmanager.h \
    znm-target_global.h \
    targetreaderwritertask.h


# Xenomai
#INCLUDEPATH +=  $${XENOMAI_HEADERS}
#DEPENDPATH += $${XENOMAI_HEADERS}
#LIBS += -L$${XENOMAI_LIBS} -lnative


# Zenom Tools Library
INCLUDEPATH += ../znm-tools
DEPENDPATH += ../znm-tools
LIBS += -L../../lib -lznm-tools



# build directory
DESTDIR = ../../lib

# install
target.path = $${ZENOM_INSTALL_LIBS}
INSTALLS += target

headers.files  = $${HEADERS}
headers.path   = $${ZENOM_INSTALL_HEADERS}
INSTALLS += headers

