lib_LIBRARIES = libConfigDummies.a

CONFIGDUMMIES_HPPS = ../../include/ConfigDummies/ControlBase.h \
../../include/ConfigDummies/ControlVariable.h \
../../include/ConfigDummies/LogVariable.h \
../../include/ConfigDummies/LogVariableBase.h \
../../include/ConfigDummies/LogVariableGUI.h \
../../include/ConfigDummies/Variable.h \
../../include/ConfigDummies/Array.h \
../../include/ConfigDummies/Config.h \
../../include/ConfigDummies/Constants.h \
../../include/ConfigDummies/pugiconfig.hpp \
../../include/ConfigDummies/pugixml.hpp


ConfigDummiesdir = $(includedir)/ConfigDummies
ConfigDummies_HEADERS = $(CONFIGDUMMIES_HPPS)


CONFIGDUMMIES_SOURCES = ControlBase.cpp \
ControlVariable.cpp \
LogVariable.cpp \
LogVariableBase.cpp \
LogVariableGUI.cpp \
Variable.cpp \
Config.cpp \
pugixml.cpp

ConfigDummiesSourcedir = ${prefix}/src/ConfigDummies
ConfigDummiesSource_HEADERS = $(CONFIGDUMMIES_SOURCES)
libConfigDummies_a_SOURCES = $(CONFIGDUMMIES_SOURCES)

QMATH_FLAG = -I ../../include/QMath
CONFIGDUMMY = -I ../../include/ConfigDummies

CONFIGDUMMIESLIB_FLAGS = $(QMATH_FLAG) $(CONFIGDUMMY)
 
libConfigDummies_a_INCLUDES = $(CONFIGDUMMIESLIB_FLAGS)
INCLUDES =  $(CONFIGDUMMIESLIB_FLAGS)

