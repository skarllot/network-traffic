bin_PROGRAMS = network-logger
network_logger_SOURCES = \
	ucompose.hpp \
	main.cpp \
	networkinterface.h \
	networkinterface.cpp \
	nix_networkinterface.h \
	nix_networkinterface.cpp \
	win_networkinterface.h \
	win_networkinterface.cpp

network_logger_LDADD = \
	$(GLIB_MODULES_LIBS)
network_logger_CPPFLAGS = \
	$(GLIB_MODULES_CFLAGS)

if PLATFORM_WIN32
network_logger_LDADD += -liphlpapi
endif

AM_CPPFLAGS = -DNETWORK_LOGGER_LOCALEDIR=\"${NETWORK_LOGGER_LOCALEDIR}\"

EXTRA_DIST = \
	README.compose

CLEANFILES = *~

MAINTAINERCLEANFILES = \
	Makefile.in
