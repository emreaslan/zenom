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

TARGET = znm-target-project
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    cppparser.cpp \
    targetprojectmanager.cpp \
    arduinoprojectcreator.cpp \
    targetprojectcreator.cpp \
    inogenerator.cpp \
    arduinobuilder.cpp \
    arduinouploader.cpp

# build directory
DESTDIR = ../../bin

# install
target.path = $${ZENOM_INSTALL_BINS}

arduino_template.files += ../../bin/zenomarduinomanager.h
arduino_template.path = $${ZENOM_INSTALL_BINS}


INSTALLS += target arduino_template

HEADERS += \
    cppparser.h \
    targetprojectbase.h \
    targetprojectmanager.h \
    targetprojectcreator.h \
    arduinoprojectcreator.h \
    inogenerator.h \
    arduinobuilder.h \
    arduinouploader.h
