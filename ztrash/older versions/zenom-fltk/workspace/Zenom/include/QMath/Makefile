#======================================================================== 
# Package	: Math Library
# Authors	: Vilas kumar Chitrakaran  
# Start Date	: Wed Dec 20 11:06:55 GMT 2000
# ----------------------------------------------------------------------  
# File: makefile
#========================================================================  

#Name of the package
PKG = QMath
#usegsl=no

# ----- Directories -----
INSTALLDIR = /usr/local
INSTALLHEADERPATH= $(INSTALLDIR)/include/
ifneq ($(INSTALLDIR),$(QRTS))
 INSTALLHEADERPATH= $(INSTALLDIR)/include/$(PKG)
endif
INSTALLLIBPATH= $(INSTALLDIR)/lib/
INSTALLBINPATH =
INSTALLBSRCPATH = 

# ----- Doxygen documentation parameters -----
DOCNAME = Math Library
DOCSOURCE = *.hpp
DOCTARGET = 

# Libraries, headers, and binaries that will be installed.
LIBS = lib$(PKG).so lib$(PKG).a
HDRS = MatrixBase.hpp VectorBase.hpp Matrix.hpp MatrixInitializer.hpp \
	   ColumnVector.hpp RowVector.hpp Vector.hpp Transform.hpp \
	   Differentiator.hpp Integrator.hpp MathException.hpp \
	   LowpassFilter.hpp HighpassFilter.hpp Adams3Integrator.hpp \
	   ODESolverRK4.hpp Differentiator4O.hpp
#SRC = *.cpp

# ---- compiler options ----
CC = g++
LD = g++
CFLAGS = -W -Wall -fexceptions -fno-builtin -O2 -fpic -D_REENTRANT -c
LDFLAGS =
INCLUDEHEADERS = -I /usr/local/include
INCLUDELIBS =
OBJ = Transform.o 
ifeq ($(usegsl),yes)
 OBJ += GSLCompat.o
 HDRS += GSLCompat.hpp
endif
ALL = $(LIBS)
TARGET = $(LIBS) copy_process
CLEAN = rm -rf *.o lib* *.dat
ALLRECURSIVE = $(LIBS)

# ========== Targets ==========
all-recursive: $(ALLRECURSIVE)
all: $(ALL)
targets: $(TARGET)

lib$(PKG).a: $(OBJ)
	ar crv $@ $(OBJ)
	ranlib $@

lib$(PKG).so: $(OBJ)
	$(LD) -shared -o $@ $(OBJ)
	
# ----- Transform -----
Transform.o:	Transform.hpp Transform.cpp
	$(CC) $(CFLAGS) Transform.cpp $(INCLUDEHEADERS)

# ----- GSLCompat -----
GSLCompat.o:	GSLCompat.hpp GSLCompat.cpp
	$(CC) $(CFLAGS) GSLCompat.cpp $(INCLUDEHEADERS)

# ---- make rules ----


clean:
	@echo
	@echo ----- Package $(PKG), Cleaning -----
	@echo
	@$(CLEAN)
	@if (test -d examples) ; then (cd examples; make clean);fi
	rm -rf ../../lib/libQMath.*

copy_process:
	cp libQMath.* ../../lib/

install:
	@echo
	@echo ----- Package $(PKG), Installing to $(INSTALLDIR) -----
	@echo
	if ! (test -d $(INSTALLLIBPATH)); then (mkdir -p $(INSTALLLIBPATH)); fi
	for i in ${LIBS}; do (cp $$i $(INSTALLLIBPATH)); done
	if ! (test -d $(INSTALLHEADERPATH)); then (mkdir -p $(INSTALLHEADERPATH)); fi
	for i in ${HDRS}; do (cp $$i $(INSTALLHEADERPATH)); done

