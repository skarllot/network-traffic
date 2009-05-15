if PLATFORM_WIN32
if WINVISTA
all:
        dlltool --as=as -k -l libiphlpapi2.a --def iphlpapi.def
endif
endif

EXTRA_DIST = \
        iphlpapi.def

CLEANFILES = \
        libiphlpapi2.a
