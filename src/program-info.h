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

#include <glib/gi18n-lib.h>

#define PROGRAM_ARTISTS artists

#define PROGRAM_AUTHORS authors

// TRANSLATORS: Program comment
#define PROGRAM_COMMENTS N_("Network Traffic Meter keep logs from your network traffic")

#define PROGRAM_COPYRIGHT "Copyright \xc2\xa9 2009 Fabrício Godoy"

#define PROGRAM_DOCUMENTERS documenters

#define PROGRAM_ICON_NAME "netspeed-applet"

#define PROGRAM_LICENSE license

// TRANSLATORS: Program name
#define PROGRAM_NAME N_("Network Traffic Meter")

#define PROGRAM_TRANSLATORS N_("translator-credits")

#define PROGRAM_WEBSITE "http://github.com/skarllot/network-traffic"

#define PROGRAM_WEBSITE_LABEL N_("Network Traffic Meter Web Site")

const char *artists[] = {
    NULL
};

const char *authors[] = {
    "Fabrício Godoy <skarllot@gmail.com>",
    NULL
};

const char *documenters[] = {
    NULL
};

const char *license = {
    N_("Network Traffic is free software; you can redistribute it and/or\n"
       "modify it under the terms of the GNU General Public License as\n"
       "published by the Free Software Foundation; either version 3 of the\n"
       "License, or (at your option) any later version.\n\n"
    "Network Traffic is distributed in the hope that it will be useful,\n"
       "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
       "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
       "GNU General Public License for more details.\n\n"
    "You should have received a copy of the GNU General Public License\n"
       "along with Network Traffic; if not, write to the Free Software\n"
       "Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,\n"
       "MA 02110-1301 USA")
};

