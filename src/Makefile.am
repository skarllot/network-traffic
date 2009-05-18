SUBDIRS = \
	mingw32-extension

AM_CFLAGS = -Wall

AM_CXXFLAGS = -Wall

AM_CPPFLAGS = \
-DNETWORK_LOGGER_GLADEDIR=\""$(gladedir)/"\"

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
if !PLATFORM_WIN32
network_logger_SOURCES += \
	nix_networkinterface.hpp \
	nix_networkinterface.cpp
else
network_logger_SOURCES += \
	win_networkinterface.hpp \
	win_networkinterface.cpp \
	windowsdef.h \
	windowsdef.c
if WINVISTA
network_logger_SOURCES += \
	mingw32-extension/iphlpapi2.h
endif
endif

network_logger_LDADD = \
    $(DEPS_CXX_LIBS)
network_logger_CFLAGS = \
    $(DEPS_C_CFLAGS)
network_logger_CXXFLAGS = \
	$(DEPS_CXX_CFLAGS)

if PLATFORM_WIN32
network_logger_LDADD += -liphlpapi -lintl
if WINVISTA
network_logger_LDADD += mingw32-extension/lib/libiphlpapi2.a
endif
endif

glade_DATA = ui.glade
gladedir = $(datadir)/$(PACKAGE)/glade

CLEANFILES = *~

EXTRA_DIST = $(glade_DATA)

MAINTAINERCLEANFILES = \
	Makefile.in
