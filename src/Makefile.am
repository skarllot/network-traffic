SUBDIRS = \
	mingw32-extension

bin_PROGRAMS = network-logger
network_logger_SOURCES = \
	i18n.hpp \
	main.cpp \
	networkinterface.hpp \
	networkinterface.cpp
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
	$(GLIB_MODULES_LIBS)
network_logger_CPPFLAGS = \
	$(GLIB_MODULES_CFLAGS)

if PLATFORM_WIN32
network_logger_LDADD += -liphlpapi -lintl
if WINVISTA
LIBS += -Lmingw32-extension/lib
network_logger_LDADD += -liphlpapi2
endif
endif

CLEANFILES = *~

MAINTAINERCLEANFILES = \
	Makefile.in
