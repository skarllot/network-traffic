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

ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}

SUBDIRS = \
	data \
	src \
	po \
	tests

INTLTOOL_FILES = \
	intltool-extract.in \
	intltool-merge.in \
	intltool-update.in

EXTRA_DIST = \
	HACKING \
	intltool-extract.in \
	intltool-merge.in \
	intltool-update.in

CLEANFILES = *~

DISTCLEANFILES = \
	mingw32-config.cache \
	po/.intltool-merge-cache

MAINTAINERCLEANFILES = \
	build-aux/compile \
	build-aux/config.guess \
	build-aux/config.sub \
	build-aux/depcomp \
	build-aux/install-sh \
	build-aux/ltmain.sh \
	build-aux/missing \
	build-aux/mkinstalldirs \
	m4/intltool.m4 \
	m4/libtool.m4 \
	m4/lt~obsolete.m4 \
	m4/ltoptions.m4 \
	m4/ltsugar.m4 \
	m4/ltversion.m4 \
	po/Makefile.in.in \
	aclocal.m4 \
	autoscan.log \
	config.h.in \
	configure \
	configure.scan \
	intltool-extract.in \
	intltool-merge.in \
	intltool-update.in \
	Makefile.in \
	po/missing

# Rule to build RPM distribution package
rpm: $(PACKAGE)-$(VERSION).tar.gz
	cp $(PACKAGE)-$(VERSION).tar.gz ~/rpmbuild/SOURCES
	rpmbuild -ba network-traffic.spec


