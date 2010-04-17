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
AM_CPPFLAGS = -I $(top_srcdir)/src

noinst_LTLIBRARIES = libnetcore-@LIBCORE_RELEASE@.la

libnetcore_@LIBCORE_RELEASE@_la_SOURCES = \
	networkinterface.hpp \
	networkinterface.cpp \
	linux_networkinterface.hpp \
	linux_networkinterface.cpp \
	win_networkinterface.hpp \
	win_networkinterface.cpp

libnetcore_@LIBCORE_RELEASE@_la_LIBADD = \
	$(CORE_DEPS_LIBS) \
	$(top_builddir)/src/utils/libnetutils-@LIBUTILS_RELEASE@.la
libnetcore_@LIBCORE_RELEASE@_la_CXXFLAGS = \
	$(CORE_DEPS_CFLAGS)
libnetcore_@LIBCORE_RELEASE@_la_LDFLAGS = -version-info $(LIBCORE_VERSION)

if OS_WIN32
libnetcore_@LIBCORE_RELEASE@_la_LIBADD += -lintl -liphlpapi
endif

MAINTAINERCLEANFILES = \
	Makefile.in

