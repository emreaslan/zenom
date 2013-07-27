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


XENOMAI_CFLAGS= -I /usr/xenomai/include -D_GNU_SOURCE -D_REENTRANT -Wall -pipe -D__XENO__ -I /usr/xenomai/include -I /usr/xenomai/include/posix -D_GNU_SOURCE -D_REENTRANT -Wall -pipe -D__XENO__
RTNET_FLAG= -I /usr/local/rtnet/include
NATIVE_INCLUDE_FLAG= -I ../../include/XenoTools/native
POSIX_INCLUDE_FLAG= -I ../../include/XenoTools/posix

libXenoTools_a_SOURCES = $(NATIVE_SOURCES) $(POSIX_SOURCES)

XENOTOOLS_FLAGS = $(XENOMAI_CFLAGS) $(NATIVE_INCLUDE_FLAG) $(POSIX_INCLUDE_FLAG) $(RTNET_FLAG)
 
libXenoTools_a_INCLUDES = $(XENOTOOLS_FLAGS)
INCLUDES =  $(XENOTOOLS_FLAGS)

