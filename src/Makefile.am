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
AM_CPPFLAGS = \
    -I $(top_srcdir) \
    -DGLADEDIR=\""$(gladedir)"\"

bin_PROGRAMS = network-logger
network_logger_SOURCES = \
    functions.hpp \
    functions.cpp \
	i18n.hpp \
	main.cpp \
	networkinterface.hpp \
	networkinterface.cpp \
    wndmain.hpp \
    wndmain.cpp
if !OS_WIN32
network_logger_SOURCES += \
	nix_networkinterface.hpp \
	nix_networkinterface.cpp
else
network_logger_SOURCES += \
	win_networkinterface.hpp \
	win_networkinterface.cpp \
	windowsdef.h \
	windowsdef.c
if OS_WINVISTA
network_logger_SOURCES += \
	$(top_builddir)/mingw32-extension/iphlpapi2.h
endif
endif

network_logger_LDADD = \
    $(DEPS_CXX_LIBS)
network_logger_CFLAGS = \
    $(DEPS_C_CFLAGS)
network_logger_CXXFLAGS = \
    $(DEPS_CXX_CFLAGS)

if OS_WIN32
network_logger_LDADD += -liphlpapi -lintl
if OS_WINVISTA
network_logger_LDADD += $(top_builddir)/mingw32-extension/libiphlpapi2.a
endif
endif

glade_DATA = ui.glade
gladedir = $(datadir)/$(PACKAGE)/glade

CLEANFILES = *~

EXTRA_DIST = $(glade_DATA)

MAINTAINERCLEANFILES = \
	Makefile.in
