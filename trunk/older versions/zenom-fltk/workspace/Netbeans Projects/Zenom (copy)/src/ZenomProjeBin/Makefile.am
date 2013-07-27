bin_PROGRAMS = zenomProje
zenomProje_SOURCES = createZnm.cpp createZnm.h zenomProje.cpp

zenomProjeSourcedir = ${prefix}/src/ZenomProjeBin
zenomProjeSource_HEADERS = $(ZenomProjebin_SOURCES)

XENOMAI_CFLAGS = -I /usr/xenomai/include -D_GNU_SOURCE -D_REENTRANT -Wall -pipe -D__XENO__ -I /usr/xenomai/include -I /usr/xenomai/include/posix -D_GNU_SOURCE -D_REENTRANT -Wall -pipe -D__XENO__

ZENOMGUI_FLAG = -I ../../include/ZenomGUI
RTNET_FLAG = -I /usr/local/rtnet/include
COMMON_FLAG= -I ../../include/Common
QMATH_FLAG = -I ../../include/QMath
NATIVE_INCLUDE_FLAG = -I ../../include/XenoTools/native
POSIX_INCLUDE_FLAG = -I ../../include/XenoTools/posix
FLTK_INCLUDE_FLAG = -I/usr/local/include
FLTK_FLAGS = -L/usr/local/lib -lfltk2 -lX11 -lXi -lXinerama -lXcursor -lXft -lXext -lfltk2_gl -lfltk2_glut
ZENOMGUIBIN_FLAGS = $(ZENOMGUI_FLAG) $(COMMON_FLAG) $(FLTK_FLAGS) $(NATIVE_INCLUDE_FLAG) $(POSIX_INCLUDE_FLAG) $(RTNET_FLAG) $(XENOMAI_CFLAGS)

INCLUDES = $(ZENOMGUIBIN_FLAGS)
LDADD = ../ZenomGUI/libZenomGUI.a ../XenoTools/libXenoTools.a ../Zenom/libZenom.a
LIBS = -L/usr/local/lib -lfltk2 -lX11 -lXi -lXinerama -lXcursor -lXft -lXext -lfltk2_gl -lfltk2_glut -lglut -L/usr/xenomai/lib -lpthread -L/usr/xenomai/lib -lpthread -Wl,@/usr/xenomai/lib/posix.wrappers -L/usr/xenomai/lib -lpthread_rt -lpthread -lrt -lrtdk -lrtdm -lnative 


