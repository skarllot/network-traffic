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
AM_CPPFLAGS = -I $(top_srcdir)/src/core

check_PROGRAMS = list-interfaces

list_interfaces_SOURCES = main.cpp
list_interfaces_LDADD = \
	$(top_builddir)/src/utils/libnettraffic-utils.la \
	$(top_builddir)/src/core/libnettraffic-core.la \
	$(DEPS_CXX_LIBS)
list_interfaces_CXXFLAGS = \
	$(DEPS_CXX_CFLAGS)

CLEANFILES = *~

MAINTAINERCLEANFILES = \
	Makefile.in

