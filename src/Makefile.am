bin_PROGRAMS = network-logger
network_logger_SOURCES = \
	i18n.h \
	main.cpp \
	networkinterface.h \
	networkinterface.cpp
if !PLATFORM_WIN32
network_logger_SOURCES += \
	nix_networkinterface.h \
	nix_networkinterface.cpp
else
network_logger_SOURCES += \
	win_networkinterface.h \
	win_networkinterface.cpp \
	windowsdef.h
endif

network_logger_LDADD = \
	$(GLIB_MODULES_LIBS)
network_logger_CPPFLAGS = \
	$(GLIB_MODULES_CFLAGS)

if PLATFORM_WIN32
network_logger_LDADD += -liphlpapi -lintl
endif

CLEANFILES = *~

MAINTAINERCLEANFILES = \
	Makefile.in
