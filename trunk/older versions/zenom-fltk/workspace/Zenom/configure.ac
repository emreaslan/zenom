AC_INIT(Zenom,0.1)
AM_INIT_AUTOMAKE()
AC_CONFIG_HEADER(config.h)
AC_PREFIX_DEFAULT([/usr/local/zenom])
AC_PREREQ([0.01])

if test \! -f /usr/xenomai/include/xenomai/nucleus/version.h; then
        AC_MSG_ERROR([*** RT-extended kernel not found in /usr/xenomai])
    fi

if test \! -f /usr/local/rtnet/include/rtnet.h; then
        AC_MSG_ERROR([*** RTNET not found in /usr/local/rtnet])
    fi

if test \! -f /usr/local/rtnet/include/rtnet_config.h; then
        AC_MSG_ERROR([*** rtnet_config.h not found in /usr/local/rtnet/include])
    fi

if test \! -f /usr//include/GL/gl.h; then
        AC_MSG_ERROR([*** GL not found in /usr/include/GL])
fi

if test \! -f /usr/local/include/fltk/FL_VERSION.h; then
        AC_MSG_ERROR([*** FLTK2 not found in /usr/local/include/fltk])
    fi

if test \! -f /usr/local/lib/libfltk2.a; then
        AC_MSG_ERROR([*** FLTK2 not found])
    fi

if test \! -f /usr/local/include/QMath/Matrix.hpp; then
        AC_MSG_ERROR([*** QMath not found in /usr/local/include/QMath])
    fi

RTNET_FLAG=/usr/local/rtnet/include
AC_SUBST(RTNET_FLAG)

AC_PROG_LIBTOOL
AC_PROG_CC
AC_PROG_CXX
AM_SANITY_CHECK

AC_PROG_INSTALL

AC_OUTPUT(Makefile src/Makefile src/ConfigDummies/Makefile src/XenoTools/Makefile src/Zenom/Makefile src/ZenomGUI/Makefile src/ZenomGUIBin/Makefile src/ZenomProjeBin/Makefile)
