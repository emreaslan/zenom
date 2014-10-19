bin_PROGRAMS = zenom
zenom_SOURCES = ZenomGUI.cpp

zenomSourcedir = ${prefix}/src/ZenomGUIBin
zenomSource_HEADERS = $(ZenomGUIbin_SOURCES)


GENERAL_CFLAGS = -W -Wall -fexceptions -fno-builtin -O2 -fpic -D_REENTRANT -c -g
XENOMAI_CFLAGS = $(shell /usr/xenomai/bin/xeno-config --posix-cflags) $(shell /usr/xenomai/bin/xeno-config --xeno-cflags)
XENOMAI_LFLAGS = $(shell /usr/xenomai/bin/xeno-config --posix-ldflags) $(shell /usr/xenomai/bin/xeno-config --xeno-ldflags)
FLTK_INCLUDE_FLAG = $(shell fltk2-config --cxxflags)
FLTK_FLAGS = $(shell fltk2-config --ldflags --use-gl --use-images --use-glut)

OPENVRML_FLAG = -I /usr/include/openvrml/ -DBOOST_SPIRIT_THREADSAFE -DBOOST_SPIRIT_CLOSURE_LIMIT=6 -DPHOENIX_LIMIT=6
SCENE_FLAG = -I ../../include/ZenomGUI/Scene
ZENOMGUI_FLAG = -I ../../include/ZenomGUI
COMMON_FLAG= -I ../../include/Common
QMATH_FLAG = -I ../../include/QMath
NATIVE_INCLUDE_FLAG = -I ../../include/XenoTools/native
POSIX_INCLUDE_FLAG = -I ../../include/XenoTools/posix
OPENVRML_LIB_FLAG = -L/usr/lib64 -lopenvrml

ZENOMGUIBIN_FLAGS = $(SCENE_FLAG) $(ZENOMGUI_FLAG) $(COMMON_FLAG) $(FLTK_FLAGS) $(NATIVE_INCLUDE_FLAG) $(POSIX_INCLUDE_FLAG) -I @RTNET_FLAG@ $(XENOMAI_CFLAGS) $(OPENVRML_FLAG) 

INCLUDES = $(ZENOMGUIBIN_FLAGS) $(GENERAL_CFLAGS)
LDADD = ../ZenomGUI/libZenomGUI.a ../XenoTools/libXenoTools.a ../Zenom/libZenom.a
LIBS = $(FLTK_FLAGS)  $(XENOMAI_LFLAGS) -lrtdk -lrtdm -lnative $(OPENVRML_LIB_FLAG)

