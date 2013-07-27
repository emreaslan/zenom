lib_LIBRARIES = libXenoTools.a

NATIVEPATH = ../../include/XenoTools/native
POSIXPATH = ../../include/XenoTools/posix

NATIVE_HPPS = $(NATIVEPATH)/AlarmXn.hpp \
$(NATIVEPATH)/EventXn.hpp \
$(NATIVEPATH)/HeapXn.hpp \
$(NATIVEPATH)/InterruptXn.hpp \
$(NATIVEPATH)/MessageQueueXn.hpp \
$(NATIVEPATH)/MutexXn.hpp \
$(NATIVEPATH)/PipeXn.hpp \
$(NATIVEPATH)/SemaphoreXn.hpp \
$(NATIVEPATH)/TaskXn.hpp \
$(NATIVEPATH)/UDPXn.hpp

POSIX_HPPS = $(POSIXPATH)/ErrnoExceptionXp.hpp \
$(POSIXPATH)/InterruptXp.hpp \
$(POSIXPATH)/MessageQueueXp.hpp \
$(POSIXPATH)/PtBarrierXp.hpp \
$(POSIXPATH)/RecursiveMutexXp.hpp \
$(POSIXPATH)/RWLockXp.hpp \
$(POSIXPATH)/SemaphoreXp.hpp \
$(POSIXPATH)/ShMemXp.hpp \
$(POSIXPATH)/StatusReportXp.hpp \
$(POSIXPATH)/ThreadXp.hpp \
$(POSIXPATH)/TimerXp.hpp 


XenoToolsNativedir = $(includedir)/XenoTools/native
XenoToolsNative_HEADERS = $(NATIVE_HPPS)

XenoToolsPosixdir = $(includedir)/XenoTools/posix
XenoToolsPosix_HEADERS = $(POSIX_HPPS)


NATIVE_SOURCES = native/AlarmXn.cpp native/EventXn.cpp native/HeapXn.cpp native/InterruptXn.cpp native/MessageQueueXn.cpp native/MutexXn.cpp native/PipeXn.cpp native/SemaphoreXn.cpp native/TaskXn.cpp native/UDPXn.cpp

POSIX_SOURCES = posix/InterruptXp.cpp posix/MessageQueueXp.cpp posix/SemaphoreXp.cpp posix/ShMemXp.cpp posix/StatusReportXp.cpp posix/ThreadXp.cpp posix/TimerXp.cpp

XenoToolsNativeSourcedir = ${prefix}/src/XenoTools/native
XenoToolsNativeSource_HEADERS = $(NATIVE_SOURCES)
XenoToolsPosixSourcedir = ${prefix}/src/XenoTools/posix
XenoToolsPosixSource_HEADERS = $(POSIX_SOURCES)


GENERAL_CFLAGS = -W -Wall -fexceptions -fno-builtin -O2 -fpic -D_REENTRANT -c -g
XENOMAI_CFLAGS = $(shell /usr/xenomai/bin/xeno-config --posix-cflags) $(shell /usr/xenomai/bin/xeno-config --xeno-cflags)
XENOMAI_LFLAGS = $(shell /usr/xenomai/bin/xeno-config --posix-ldflags) $(shell /usr/xenomai/bin/xeno-config --xeno-ldflags)


NATIVE_INCLUDE_FLAG= -I ../../include/XenoTools/native
POSIX_INCLUDE_FLAG= -I ../../include/XenoTools/posix

libXenoTools_a_SOURCES = $(NATIVE_SOURCES) $(POSIX_SOURCES)

XENOTOOLS_FLAGS = $(XENOMAI_CFLAGS) $(NATIVE_INCLUDE_FLAG) $(POSIX_INCLUDE_FLAG) -I @RTNET_FLAG@ 
 
libXenoTools_a_INCLUDES = $(XENOTOOLS_FLAGS) $(GENERAL_CFLAGS)
LIBS = $(XENOMAI_LFLAGS)
INCLUDES =  $(XENOTOOLS_FLAGS)

