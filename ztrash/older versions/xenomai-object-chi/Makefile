#======================================================================== 
# Package	: POSIX Utilities Library
# ----------------------------------------------------------------------  
# File: makefile
#========================================================================  


#Name of the package
PKG = putils deneme

# ----- Directories -----
INSTALLDIR = /usr
INSTALLHEADERPATH= $(INSTALLDIR)/include/$(PKG)
INSTALLLIBPATH= $(INSTALLDIR)/lib
INSTALLBINPATH =
INSTALLBSRCPATH = 

# ----- Doxygen documentation parameters -----
DOCNAME = POSIX Utilities Library
DOCSOURCE = *.hpp
DOCTARGET = 

# Libraries, headers, and binaries that will be installed.
LIBS = lib$(PKG).so lib$(PKG).a
HDRS = ErrnoException.hpp RecursiveMutex.hpp MessageQueue.hpp \
       ShMem.hpp StatusReport.hpp PtBarrier.hpp RWLock.hpp \
       UDPClientServer.hpp Thread.hpp
#SRC = *.cpp

# ---- compiler options ----
CC = g++
LD = g++
CFLAGS = -W -Wall -fexceptions -fno-builtin -O2 -fpic -D_REENTRANT -c
LDFLAGS = 
INCLUDEHEADERS = -I ./ -I /usr/include/nptl -I /usr/xenomai/include
INCLUDELIBS = -L ../ -L /usr/xenomai/lib -lpthread_rt  -lrt 
OBJ = StatusReport.o MessageQueue.o ShMem.o UDPClientServer.o \
      Thread.o
TARGET = $(LIBS)
CLEAN = rm -rf *.o *.dat $(TARGET)


# ========== Targets ==========
targets: $(TARGET)

# ----- lib -----
lib$(PKG).a: $(OBJ)
	ar cr $@ $(OBJ)
	ranlib $@

lib$(PKG).so: $(OBJ)
	$(LD) -shared -o $@ $(OBJ)

# ----- ShMem -----
ShMem.o: ShMem.cpp
	$(CC) $(CFLAGS) ShMem.cpp $(INCLUDEHEADERS)

# ----- StatusReport -----
StatusReport.o: StatusReport.cpp
	$(CC) $(CFLAGS) StatusReport.cpp $(INCLUDEHEADERS)

# ----- MessageQueue -----
MessageQueue.o: MessageQueue.cpp
	$(CC) $(CFLAGS) MessageQueue.cpp $(INCLUDEHEADERS)

# ----- UDPClientServer -----
UDPClientServer.o: UDPClientServer.cpp
	$(CC) $(CFLAGS) UDPClientServer.cpp $(INCLUDEHEADERS)

# ----- Thread -----
Thread.o: Thread.cpp
	$(CC) $(CFLAGS) Thread.cpp $(INCLUDEHEADERS)

# ---- make rules ----
clean:
	@echo
	@echo ----- Package $(PKG), Cleaning -----
	@echo
	$(CLEAN)
	if (test -d examples) ; then (cd examples; make clean);fi

install:
	@echo
	@echo ----- Package $(PKG), Installing to $(INSTALLDIR) -----
	@echo
	if ! test -d $(INSTALLLIBPATH) ; then (mkdir $(INSTALLLIBPATH)); fi
	for i in ${LIBS}; do (cp $$i $(INSTALLLIBPATH)); done
	if ! test -d $(INSTALLHEADERPATH) ; then (mkdir $(INSTALLHEADERPATH)); fi
	for i in ${HDRS}; do (cp $$i $(INSTALLHEADERPATH)); done

