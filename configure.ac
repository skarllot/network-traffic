# vim:set ts=4 sw=4 expandtab nowrap textwidth=80
#
# Copyright (C) 2009 Fabrício Godoy <skarllot@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.
#
# Authors:
#   Fabrício Godoy <skarllot@gmail.com>
#

AC_PREREQ([2.54])
AC_INIT([Network Logger],[0.1.0],
        [http://code.google.com/p/network-logger/issues],
        [network-logger])

AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_SRCDIR([src])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([1.9 -Wall -Werror -Woverride dist-zip])

# Check build environment
AC_CANONICAL_HOST

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_CPP
AC_PROG_LN_S
AC_PROG_RANLIB
AC_CHECK_TOOL([DLLTOOL], [dlltool], [:])
#AC_PROG_LIBTOOL
#AC_LIBTOOL_WIN32_DLL
AM_PROG_CC_C_O

AC_LANG([C++])

# Checks for libraries.
PKG_CHECK_MODULES([DEPS_C],[glib-2.0])
AC_SUBST(DEPS_C_CFLAGS)
AC_SUBST(DEPS_C_LIBS)

PKG_CHECK_MODULES([DEPS_CXX],[gtkmm-2.4 \
    libglademm-2.4])
AC_SUBST(DEPS_CXX_CFLAGS)
AC_SUBST(DEPS_CXX_LIBS)

# I18n
#AC_PROG_INTLTOOL([0.35.5])
GETTEXT_PACKAGE=network-logger
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED([GETTEXT_PACKAGE], ["$GETTEXT_PACKAGE"],
                   [the gettext translation domain])

AM_GLIB_GNU_GETTEXT
GLIB_DEFINE_LOCALEDIR(NETWORK_LOGGER_LOCALEDIR)

IT_PROG_INTLTOOL([0.35.1])

# ------------------------------------------------------------------------------
# Check OS-specific platform
# ------------------------------------------------------------------------------
AC_MSG_CHECKING([for native Win32])
case "$host_os" in
  *mingw*)
    iswin32=yes
    AC_MSG_RESULT(yes)
    ;;
  *)
    iswin32=no
    AC_MSG_RESULT(no)
    ;;
esac

AM_CONDITIONAL(OS_WIN32, [test "$iswin32" = "yes"])

# ------------------------------------------------------------------------------
# Target compile to Windows Vista
# ------------------------------------------------------------------------------

AC_ARG_ENABLE(winvista,
    AC_HELP_STRING([--enable-winvista],[Target compile to Windows Vista]),[
	iswinvista=1
    AC_DEFINE(WINVER,0x0600,[Define minimum Windows version])
])
AM_CONDITIONAL(OS_WINVISTA, test "x$iswinvista" = "x1")

# Enable code testing without install (can load local glade file)
AC_ARG_ENABLE(testing,
    AC_HELP_STRING([--enable-testing],[Enable code testing without install]),[
    enabletest=1
    AC_DEFINE(TEST,,[Code for testing purposes])
    AC_DEFINE_UNQUOTED(LOCALPATH, "$PWD", [Defines local compile path])
])

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_UINT64_T

# Checks for library functions.
AC_CHECK_FUNCS([memset strtoull])

AC_CONFIG_FILES([Makefile
                 mingw32-extension/Makefile
                 data/Makefile
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
