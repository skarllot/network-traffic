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
#include <iostream>
#include <glibmm/i18n.h>
#include "networkinterface.h"

#ifndef WINNT
#include "nix_networkinterface.h"
#else
#include "windowsdef.h"
#include "win_networkinterface.h"

int check_version();
#endif

int main(int argc, char** argv)
{
#ifdef WINNT
    int retval = check_version();
    if (retval != NO_ERROR)
        return retval;
#endif

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

#ifdef WINNT

/** Check whether running Windows version is supported.
 */
int check_version()
{
    // http://msdn.microsoft.com/en-gb/library/ms724833(VS.85).aspx
    OSVERSIONINFOEX os_version;
    ZeroMemory(&os_version, sizeof (OSVERSIONINFOEX));
    os_version.dwOSVersionInfoSize = sizeof (OSVERSIONINFOEX);
    GetVersionEx((OSVERSIONINFO*) & os_version);

    if (os_version.dwMajorVersion < 5 ||
            (os_version.dwMajorVersion == 5 && os_version.dwMinorVersion < 1) ||
            (os_version.dwMajorVersion == 5 && os_version.dwMinorVersion == 1 &&
            os_version.wServicePackMajor < 2) ||
            (os_version.dwMajorVersion = 5 && os_version.dwMinorVersion == 2 &&
            os_version.wServicePackMajor < 1))
    {
        std::cout << _("Windows version not supported, requires at least Windows XP with SP2")
                << std::endl;
        return (EXIT_FAILURE);
    }

    return NO_ERROR;
}
#endif

