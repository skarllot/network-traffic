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

#include "windowsdef.h"

#include <stdlib.h>
#include <stdio.h>
#include <glib/gi18n.h>

int check_version(void)
{
#if (WINVER < 0x0600)
    char msg[] = N_("Windows version not supported, requires at least "
                    "Windows XP with SP2");
#else
    char msg[] = N_("Windows version not supported, requires at least "
                    "Windows Vista");
#endif

#ifdef WINNT
    // http://msdn.microsoft.com/en-us/library/ms724833.aspx
    OSVERSIONINFOEX os_version;
    ZeroMemory(&os_version, sizeof (OSVERSIONINFOEX));
    os_version.dwOSVersionInfoSize = sizeof (OSVERSIONINFOEX);
    GetVersionEx((OSVERSIONINFO*) &os_version);

#if (WINVER < 0x0600)
    if (
            // Less than Windows XP
            (os_version.dwMajorVersion == 5 && os_version.dwMinorVersion < 1) ||
            // Windows XP less than SP2
            (os_version.dwMajorVersion == 5 && os_version.dwMinorVersion == 1 &&
            os_version.wServicePackMajor < 2) ||
            // Windows Server 2003 less than SP1
            (os_version.dwMajorVersion = 5 && os_version.dwMinorVersion == 2 &&
            os_version.wServicePackMajor < 1))
    {
#else
    // Less than Windows Vista
    if (os_version.dwMajorVersion < 6)
    {
#endif /* WINVER */

#endif /* WINNT */

        printf(_(msg));
        return (EXIT_FAILURE);

#ifdef WINNT
    }

    return NO_ERROR;
#endif /* WINNT */
}
