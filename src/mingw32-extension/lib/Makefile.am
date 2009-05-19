if PLATFORM_WIN32
if WINVISTA
all-local:
	@DLLTOOL@ -k -l libiphlpapi2.a --def iphlpapi.def


CLEANFILES = \
        libiphlpapi2.a
endif
endif

EXTRA_DIST = \
        iphlpapi.def

