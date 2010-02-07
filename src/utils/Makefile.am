# vim:set ts=8 sw=8 noexpandtab nowrap textwidth=80
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

AM_CFLAGS = -Wall
AM_CXXFLAGS = -Wall

noinst_LTLIBRARIES = libnetutils-@LIBUTILS_RELEASE@.la

libnetutils_@LIBUTILS_RELEASE@_la_SOURCES = \
	functions.hpp \
	functions.cpp \
	i18n.hpp \
	windowsdef.h \
	windowsdef.c

libnetutils_@LIBUTILS_RELEASE@_la_LIBADD = \
	$(UTILS_DEPS_C_LIBS) \
	$(UTILS_DEPS_CXX_LIBS)
libnetutils_@LIBUTILS_RELEASE@_la_CFLAGS = \
	$(UTILS_DEPS_C_CFLAGS)
libnetutils_@LIBUTILS_RELEASE@_la_CXXFLAGS = \
	$(UTILS_DEPS_CXX_CFLAGS)
libnetutils_@LIBUTILS_RELEASE@_la_LDFLAGS = -version-info $(LIBUTILS_VERSION)

if OS_WIN32
libnetutils_@LIBUTILS_RELEASE@_la_LIBADD += -lintl
endif

MAINTAINERCLEANFILES = \
	Makefile.in

