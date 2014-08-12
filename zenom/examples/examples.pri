include( ../zenom.pri )

# Xenomai
INCLUDEPATH +=  $${XENOMAI_HEADERS}
DEPENDPATH += $${XENOMAI_HEADERS}
LIBS += -L$${XENOMAI_LIBS} -lnative -lxenomai

# ControlBase
INCLUDEPATH += ../../zenom/znm-controlbase
DEPENDPATH += ../../zenom/znm-controlbase

INCLUDEPATH += ../../zenom/znm-core
DEPENDPATH += ../../zenom/znm-core

INCLUDEPATH += ../../zenom/znm-tools
DEPENDPATH += ../../zenom/znm-tools

INCLUDEPATH += ../../zenom/znm-arduino
DEPENDPATH += ../../zenom/znm-arduino

LIBS += -L../../lib -lznm-controlbase -lznm-core -lznm-tools -lznm-target 

