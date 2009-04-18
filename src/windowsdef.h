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

#ifndef _WINDOWSDEF_H
#define	_WINDOWSDEF_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifndef WINVER
#define WINVER 0x0502   // Windows Server 2003 with SP1, Windows XP with SP2
// See http://msdn.microsoft.com/en-us/library/aa383745(VS.85).aspx
#endif /* WINVER */

// Workarounds
#ifndef GETTEXT_PACKAGE
#define GETTEXT_PACKAGE "network-logger"
#endif
#ifndef NETWORK_LOGGER_LOCALEDIR
#define NETWORK_LOGGER_LOCALEDIR "/usr/local/share/locale"
#endif

#include <windows.h>

#endif	/* _WINDOWSDEF_H */

