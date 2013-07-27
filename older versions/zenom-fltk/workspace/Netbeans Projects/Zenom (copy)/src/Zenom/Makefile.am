lib_LIBRARIES = libZenom.a

ZENOMPATH = ../../include/Zenom
COMMONPATH = ../../include/Common

ZENOM_HS = $(ZENOMPATH)/ControlBase.h \
$(ZENOMPATH)/RTMessage.h \
$(ZENOMPATH)/RTMessageRecv.h \
$(ZENOMPATH)/RTMessageSend.h

COMMON_HS = $(COMMONPATH)/Array.h \
$(COMMONPATH)/Config.h \
$(COMMONPATH)/Constants.h \
$(COMMONPATH)/ControlVariable.h \
$(COMMONPATH)/guiMessenger.h \
$(COMMONPATH)/LogVariable.h \
$(COMMONPATH)/LogVariableBase.h \
$(COMMONPATH)/LogVariableGUI.h \
$(COMMONPATH)/Variable.h

ZenomHSdir = $(includedir)/Zenom
ZenomHS_HEADERS = $(ZENOM_HS)

CommonHSdir = $(includedir)/Common
CommonHS_HEADERS = $(COMMON_HS)

ZENOM_SOURCES = ControlBase.cpp RTMessage.cpp RTMessageRecv.cpp RTMessageSend.cpp 

COMMON_SOURCES = ../Common/Config.cpp ../Common/ControlVariable.cpp  ../Common/LogVariable.cpp ../Common/LogVariableBase.cpp ../Common/../Common/LogVariableGUI.cpp ../Common/Variable.cpp ../Common/guiMessenger.cpp



ZenomSourcedir = ${prefix}/src/Zenom
ZenomSource_HEADERS = $(ZENOM_SOURCES)
CommonSourcedir = ${prefix}/src/Common
CommonSource_HEADERS = $(COMMON_SOURCES)




libZenom_a_SOURCES = $(ZENOM_SOURCES) $(COMMON_SOURCES)

XENOMAI_CFLAGS = -I /usr/xenomai/include -D_GNU_SOURCE -D_REENTRANT -Wall -pipe -D__XENO__ -I /usr/xenomai/include -I /usr/xenomai/include/posix -D_GNU_SOURCE -D_REENTRANT -Wall -pipe -D__XENO__

RTNET_FLAG = -I /usr/local/rtnet/include
ZENOM_FLAG = -I ../../include/Zenom
COMMON_FLAG= -I ../../include/Common
QMATH_FLAG = -I ../../include/QMath
NATIVE_INCLUDE_FLAG = -I ../../include/XenoTools/native
POSIX_INCLUDE_FLAG = -I ../../include/XenoTools/posix

ZENOMLIB_FLAGS = $(NATIVE_INCLUDE_FLAG) $(POSIX_INCLUDE_FLAG) $(COMMON_FLAG) $(QMATH_FLAG) $(XENOMAI_CFLAGS) $(ZENOM_FLAG) $(RTNET_FLAG)
 
libZenom_a_INCLUDES = $(ZENOMLIB_FLAGS) 
INCLUDES =  $(ZENOMLIB_FLAGS) 
