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

TARGET = znm-arduino-project
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    cppparser.cpp

# build directory
DESTDIR = ../../bin

# install
target.path = $${ZENOM_INSTALL_BINS}


INSTALLS += target

HEADERS += \
    cppparser.h
