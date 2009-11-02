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

noinst_LTLIBRARIES = libnettraffic-core.la

libnettraffic_core_la_LIBADD = \
	$(CORE_DEPS_LIBS)
libnettraffic_core_la_SOURCES = \
	networkinterface.hpp \
	networkinterface.cpp \
	linux_networkinterface.hpp \
	linux_networkinterface.cpp \
	win_networkinterface.hpp \
	win_networkinterface.cpp

libnettraffic_core_la_CXXFLAGS = \
	$(CORE_DEPS_CFLAGS)

if OS_WIN32
libnettraffic_core_la_LIBADD += -lintl -liphlpapi
if OS_WINVISTA
libnettraffic_core_la_LIBADD += \
	$(top_builddir)/src/mingw32-extension/libiphlpapi2.a
endif
endif

MAINTAINERCLEANFILES = \
	Makefile.in

