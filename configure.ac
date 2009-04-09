#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.54])
AC_INIT([Network Logger],[0.1.0],
        [http://code.google.com/p/network-logger/issues],
        [network-logger])

AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_SRCDIR([src])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([1.9 -Wall -Werror])
AM_MAINTAINER_MODE
AC_SUBST([ACLOCAL_AMFLAGS], ["\${ACLOCAL_FLAGS}"])

# Check build environment
AC_CANONICAL_HOST

# Checks for programs.
AC_PROG_CC
AC_PROG_CXX
#AC_PROG_CXXCPP
AC_PROG_INSTALL
#AC_PROG_LIBTOOL
#AC_PROG_INTLTOOL([0.23])
#AM_SANITY_CHECK
#AC_LANG_CPLUSPLUS

# Checks for libraries.
PKG_CHECK_MODULES([GLIB_MODULES],[glibmm-2.4])
AC_SUBST(GLIB_MODULES_CFLAGS)
AC_SUBST(GLIB_MODULES_LIBS)

# I18n
GETTEXT_PACKAGE=network-logger
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED([GETTEXT_PACKAGE], ["$GETTEXT_PACKAGE"],
                   [the gettext translation domain])

AM_GLIB_GNU_GETTEXT
GLIB_DEFINE_LOCALEDIR(NETWORK_LOGGER_LOCALEDIR)

IT_PROG_INTLTOOL([0.40.1])

# ------------------------------------------------------------------------------
# Check OS-specific platform
# ------------------------------------------------------------------------------
AC_MSG_CHECKING([for native Win32])
case "$host_os" in
  *mingw*)
    iswin32=1
    AC_MSG_RESULT(yes)
    ;;
  *)
    iswin32=0
    AC_MSG_RESULT(no)
    ;;
esac

AM_CONDITIONAL(PLATFORM_WIN32, test "x$iswin32" = "x1")

# ------------------------------------------------------------------------------
# Target compile to Windows Vista
# ------------------------------------------------------------------------------

AC_ARG_ENABLE(winvista,
    AC_HELP_STRING([--enable-winvista],[Target compile to Windows Vista]),[
    AC_DEFINE(WINVER,0x0600,[Define minimum Windows version])
])

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 po/Makefile.in
                 src/Makefile])
AC_OUTPUT

dnl ==========================================================================
echo "
network-logger-$VERSION:

	prefix:			${prefix}
	source code location:	${srcdir}
	compilers:		${CC}, ${CXX}
"
