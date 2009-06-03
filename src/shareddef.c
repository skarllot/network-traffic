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
 * Authors:
 *      Fabrício Godoy <skarllot@gmail.com>
 *
 */

#include "shareddef.h"

#include "windowsdef.h"

gchar* glade_dir = NULL;
gchar* locale_dir = NULL;
#ifdef TEST
gchar* local_path = NULL;
#endif

void build_package_paths(void)
{
#ifdef WINNT

    gchar* prefix;
    prefix = g_win32_get_package_installation_directory_of_module(NULL);

    glade_dir = g_build_filename(prefix, "share", PACKAGE, "glade", NULL);
    locale_dir = g_build_filename(prefix, "share", "locale", NULL);
#ifdef TEST
    local_path = g_build_filename(prefix, "..", NULL);
#endif
    
    g_free(prefix);

#else /* WINNT */

    glade_dir = g_strdup(GLADEDIR);
    locale_dir = g_strdup(NETWORK_LOGGER_LOCALEDIR);
#ifdef TEST
    local_path = g_strdup(LOCALPATH);
#endif

#endif /* WINNT */
}
