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

SUBDIRS = \
	mingw32-extension \
	utils \
	core

gladedir = $(datadir)/$(PACKAGE)/glade

AM_CFLAGS = -Wall
AM_CXXFLAGS = -Wall
AM_CPPFLAGS = -DGLADEDIR=\""$(gladedir)"\"

bin_PROGRAMS = network-traffic
network_traffic_SOURCES = \
	main.cpp \
	shareddef.h \
	shareddef.c \
	wndmain.hpp \
	wndmain.cpp

network_traffic_LDADD = \
	$(top_srcdir)/src/utils/libnettraffic-utils.a \
	$(top_srcdir)/src/core/libnettraffic-core.a \
	$(DEPS_CXX_LIBS)
network_traffic_CFLAGS = \
	$(DEPS_C_CFLAGS)
network_traffic_CXXFLAGS = \
	$(DEPS_CXX_CFLAGS)

if OS_WIN32
network_traffic_LDADD += -lintl
if !TEST
network_traffic_LDFLAGS = -mwindows
endif
# ----- libnettraffic-core -----
network_traffic_LDADD += -liphlpapi
if OS_WINVISTA
network_traffic_LDADD += $(top_srcdir)/src/mingw32-extension/libiphlpapi2.a
endif
endif

CLEANFILES = *~

MAINTAINERCLEANFILES = \
	Makefile.in

