#Warning: this file should must be run " sudo make "

XML_INCLUDES:= -I /usr/local/include/QMath -I /usr/local/rtnet/include -I /usr/local/Zenom/include/ConfigDummies
XML_LIBS:= -L /usr/local/Zenom/lib -lConfigDummies

XENO_DESTDIR:=
XENO_CONFIG:=/usr/xenomai/bin/xeno-config

#--- POSIX ---
XENO_POSIX_CFLAGS:=$(shell DESTDIR=$(XENO_DESTDIR) $(XENO_CONFIG) --posix-cflags)
XENO_POSIX_LIBS:=$(shell DESTDIR=$(XENO_DESTDIR) $(XENO_CONFIG) --posix-ldflags)

#--- NATIVE ---
XENO_NATIVE_CFLAGS:=$(shell DESTDIR=$(XENO_DESTDIR) $(XENO_CONFIG) --xeno-cflags)
XENO_NATIVE_LIBS:= -lnative $(shell DESTDIR=$(XENO_DESTDIR) $(XENO_CONFIG) --xeno-ldflags)

CC= g++
LD= g++
CFLAGS = $(XENO_NATIVE_CFLAGS) $(FLTK_CFLAGS) $(XENO_POSIX_CFLAGS) -W -Wall -fexceptions -fno-builtin -O2 -fpic -D_REENTRANT -c -g
LDFLAGS = -fexceptions -O2 -lrtdk -lrtdm
INCLUDEHEADERS = -I /usr/local/Zenom/include/ -I /usr/local/Zenom/include/Common -I /usr/local/Zenom/include/Zenom -I /usr/local/Zenom/include/ZenomGUI -I /usr/local/include/QMath/ -I /usr/local/rtnet/include -I /usr/local/Zenom/include/XenoTools/native -I /usr/local/Zenom/include/XenoTools/posix
INCLUDELIBS = -L $(XENO_POSIX_LIBS) $(XENO_NATIVE_LIBS) -lX11 -lGL -lGLU -L /usr/local/Zenom/lib/ -L /usr/xenomai/lib -lZenom -lZenomGUI -lXenoTools
OBJS= 

TARGET= BounceBall.o 
RUN= run
CLEAN= rm -rf $(TARGET) BounceBall.znm BounceBall.cfc

# ========== Targets ==========
targets: $(TARGET) $(RUN)

# ----- BounceBall -----
BounceBall.o: BounceBall.cpp
	$(CC) $(CFLAGS) BounceBall.cpp $(INCLUDEHEADERS)
	$(LD) -o BounceBall.znm BounceBall.o $(OBJ) $(INCLUDELIBS) $(LDFLAGS)
	rm BounceBall.o
	$(CC) $(CFLAGS) BounceBall.cpp $(XML_INCLUDES)
	$(LD) -o BounceBall.cfc BounceBall.o $(XML_LIBS)

run:
	./BounceBall.cfc
	rm BounceBall.o
	rm BounceBall.cfc

clean:
	$(CLEAN) 