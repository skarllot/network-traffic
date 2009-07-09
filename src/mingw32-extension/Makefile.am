# vim:set ts=8 sw=8 noexpandtab nowrap textwidth=80
#

if OS_WIN32
if OS_WINVISTA
libiphlpapi2.a: iphlpapi.def
	$(DLLTOOL) -k -l libiphlpapi2.a --def iphlpapi.def

BUILT_SOURCES = libiphlpapi2.a

CLEANFILES = libiphlpapi2.a
endif
endif

EXTRA_DIST = \
	iphlpapi2.h \
	iphlpapi.def

MAINTAINERCLEANFILES = \
	Makefile.in

