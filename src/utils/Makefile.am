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

noinst_LIBRARIES = libnettraffic-utils.a

libnettraffic_utils_a_SOURCES = \
	functions.hpp \
	functions_templates.hpp \
	functions.cpp \
	i18n.hpp
if OS_WIN32
libnettraffic_utils_a_SOURCES += \
	windowsdef.h \
	windowsdef.c
endif

libnettraffic_utils_a_CFLAGS = \
	$(UTILS_DEPS_C_CFLAGS)
libnettraffic_utils_a_CXXFLAGS = \
	$(UTILS_DEPS_CXX_CFLAGS)

MAINTAINERCLEANFILES = \
	Makefile.in

