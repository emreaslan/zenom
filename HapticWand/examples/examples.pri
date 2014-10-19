include( ../HapticWand.pri )

# Xenomai
INCLUDEPATH +=  $${XENOMAI_HEADERS}
DEPENDPATH += $${XENOMAI_HEADERS}
LIBS += -L$${XENOMAI_LIBS} -lxenomai -lrtdm

# HapticWand
INCLUDEPATH += ../../HapticWand
DEPENDPATH += ../../HapticWand
LIBS += -L../../lib -lHapticWand


