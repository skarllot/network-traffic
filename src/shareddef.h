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

#ifndef _SHAREDDEF_H
#define	_SHAREDDEF_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <glib.h>

extern gchar* glade_dir;
extern gchar* locale_dir;
#ifdef TEST
extern gchar* local_path;
#endif

#ifdef __cplusplus
// Avoid C++ name mangling
extern "C" {
#endif

// Based on http://git.gnome.org/cgit/glade3/tree/gladeui/glade-app.c
// (Copyright (C) 2001 Ximian, Inc.)
/** Build package paths at runtime.
 */
void build_package_paths(void);

#ifdef __cplusplus
}
#endif

#endif	/* _SHAREDDEF_H */

