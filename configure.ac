#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.54])
AC_INIT([Network Logger],[0.1.0],
        [http://code.google.com/p/network-logger/issues],
        [network-logger])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_SRCDIR([src/main.cpp])
AM_INIT_AUTOMAKE([1.9 -Wall -Werror])
AC_CONFIG_HEADERS([config.h])

# ------------------------------------------------------------------------------
# In order to enable this mode, you must first add AM_MAINTAINER_MODE to
# `configure.in'. This will add the `--enable-maintainer-mode' option to 
# `configure'; when specified this flag will cause these so-called 
# `maintainer rules' to be enabled.
# ------------------------------------------------------------------------------
#AM_MAINTAINER_MODE

# ------------------------------------------------------------------------------
# Check build environment
# ------------------------------------------------------------------------------
AC_CANONICAL_HOST

# Checks for programs.
AC_PROG_CC
AC_PROG_CXX
#AC_PROG_CXXCPP
#AC_PROG_INSTALL
#AC_PROG_LIBTOOL
#AC_PROG_INTLTOOL([0.23], [no-xml])
#AM_SANITY_CHECK
#AC_LANG_CPLUSPLUS

# Checks for libraries.

# ------------------------------------------------------------------------------
# Check OS-specific platform
# ------------------------------------------------------------------------------
AC_MSG_CHECKING([for native Win32])
case "$host_os" in
  *mingw*)
    AM_CONDITIONAL(PLATFORM_WIN32, test xtrue = xtrue)
    AC_MSG_RESULT(yes)
    ;;
  *)
    AM_CONDITIONAL(PLATFORM_WIN32, test xtrue = xfalse)
    AC_MSG_RESULT(no)
    ;;
esac

# ------------------------------------------------------------------------------
# Target compile to Windows Vista
# ------------------------------------------------------------------------------

AC_ARG_ENABLE(winvista,
    AC_HELP_STRING([--enable-winvista],[Target compile to Windows Vista]),[
    if test "x$enableval" = "xyes"; then
	AC_DEFINE(WINVER,0x0600,[Define minimum Windows version])
    fi
])

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
