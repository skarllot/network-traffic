/*
 * Copyright (C) 2009 Fabrício Godoy <skarllot@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * Authors: Fabrício Godoy <skarllot@gmail.com>
 *
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <glibmm/i18n.h>
#include "networkinterface.h"

#ifndef WINNT
#include "nix_networkinterface.h"
#include <sys/socket.h>
#include <netdb.h>
#include <dirent.h>
#include <ifaddrs.h>
#include <fstream>
//#include <arpa/inet.h>
#else
#include "win_networkinterface.h"
#endif

int main(int argc, char** argv)
{
    // Gettext initialization
    bindtextdomain(GETTEXT_PACKAGE, NETWORK_LOGGER_LOCALEDIR);
    bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
    textdomain(GETTEXT_PACKAGE);

    // A text to test whether gettext is working
    std::cout << _("This is a test text") << std::endl;

#ifndef WINNT
    return nix_NetworkInterface::test_code();
#else
    return win_NetworkInterface::test_code();
#endif

    return (EXIT_SUCCESS);
}

