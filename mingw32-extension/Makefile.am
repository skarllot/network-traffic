if OS_WIN32
if OS_WINVISTA
all-local:
	@DLLTOOL@ -k -l libiphlpapi2.a --def iphlpapi.def


CLEANFILES = \
    libiphlpapi2.a
endif
endif

EXTRA_DIST = \
    iphlpapi2.h \
    iphlpapi.def

MAINTAINERCLEANFILES = \
    Makefile.in

