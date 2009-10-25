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

#include "functions.hpp"

#include "i18n.hpp"
#include <gtk/gtk.h>


Glib::ustring
format_bytes(uint64_t size, uint64_t max_size, bool to_bits)
{
    gchar* retp;

    enum
    {
        K_INDEX,
        M_INDEX,
        G_INDEX,
        T_INDEX
    };

    struct Format
    {
        uint64_t factor;
        const char* string;
    };

    const Format all_formats[2][4] = {
        {
            { 1UL << 10, N_("%.1f KiB")},
            { 1UL << 20, N_("%.1f MiB")},
            { 1UL << 30, N_("%.1f GiB")},
            { 1UL << 40, N_("%.1f TiB")}
        },
        {
            { 1000, N_("%.1f kbit")},
            { 1000000, N_("%.1f Mbit")},
            { 1000000000, N_("%.1f Gbit")},
            { 1000000000000, N_("%.1f Tbit")}
        }
    };

    const Format(&formats)[4] = all_formats[to_bits ? 1 : 0];

    if (to_bits)
    {
        size *= 8;
        max_size *= 8;
    }

    if (max_size == 0)
        max_size = size;

    if (max_size < formats[K_INDEX].factor)
    {
        const char *format = (to_bits
                ? dngettext(GETTEXT_PACKAGE, "%u bit", "%u bits", (guint) size)
                : dngettext(GETTEXT_PACKAGE, "%u byte", "%u bytes", (guint) size));
        retp = g_strdup_printf(format, (guint) size);
    }
    else
    {
        guint64 factor;
        const char* format = NULL;

        if (max_size < formats[M_INDEX].factor)
        {
            factor = formats[K_INDEX].factor;
            format = formats[K_INDEX].string;
        }
        else if (max_size < formats[G_INDEX].factor)
        {
            factor = formats[M_INDEX].factor;
            format = formats[M_INDEX].string;
        }
        else if (max_size < formats[T_INDEX].factor)
        {
            factor = formats[G_INDEX].factor;
            format = formats[G_INDEX].string;
        }
        else
        {
            factor = formats[T_INDEX].factor;
            format = formats[T_INDEX].string;
        }

        retp = g_strdup_printf(_(format), size / (double) factor);
    }

    Glib::ustring ret(retp);
    g_free(retp);
    return ret;
}

Glib::ustring
format_bytes_rate(uint64_t rate, uint64_t max_size, bool to_bits)
{
    Glib::ustring f_bytes = format_bytes(rate, max_size, to_bits);
    // TRANSLATORS: rate as 10MiB/s or 10Mbit/s
    Glib::ustring f_rate = COMPOSE(_("%1/s"), f_bytes);
    return f_rate;
}

void show_error(const Glib::ustring& msg, bool canexit)
{
    Gtk::MessageDialog d(msg, Gtk::MESSAGE_ERROR);

    d.set_modal();
    // TRANSLATORS: Title from error dialog.
    d.set_title(_("Fatal error"));

    d.run();

    if (canexit)
        exit(EXIT_FAILURE);
}
