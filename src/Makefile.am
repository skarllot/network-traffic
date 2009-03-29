bin_PROGRAMS = network-logger
network_logger_SOURCES = \
	main.cpp \
	networkinfo.h \
	networkinfo.cpp

if PLATFORM_WIN32
EXTRALIBADD = -liphlpapi
endif
network_logger_LDADD = \
	$(EXTRALIBADD)

CLEANFILES = *~
MAINTAINERCLEANFILES = \
	Makefile.in
