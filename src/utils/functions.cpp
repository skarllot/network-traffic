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

#define BYTE_UNITS_COUNT 4
#define NULLPOINTER static_cast<void*>(0)

#if __WORDSIZE == 64
#define NUM_1TiB 1UL << 40
#define NUM_1Tbit 1000000000000UL
#else
#define NUM_1TiB 1ULL << 40
#define NUM_1Tbit 1000000000000ULL
#endif


std::string build_filename(const std::string& elem1, const std::string& elem2)
{
  return Glib::convert_return_gchar_ptr_to_stdstring(g_build_filename(
          elem1.c_str(), elem2.c_str(), NULLPOINTER));
}

std::string build_filename(const std::string& elem1, const std::string& elem2,
                           const std::string& elem3)
{
  return Glib::convert_return_gchar_ptr_to_stdstring(g_build_filename(
          elem1.c_str(), elem2.c_str(), elem3.c_str(), NULLPOINTER));
}

std::string build_filename(const std::string& elem1, const std::string& elem2,
                           const std::string& elem3, const std::string& elem4)
{
  return Glib::convert_return_gchar_ptr_to_stdstring(g_build_filename(
          elem1.c_str(), elem2.c_str(), elem3.c_str(), elem4.c_str(),
          NULLPOINTER));
}

std::string build_filename(const std::string& elem1, const std::string& elem2,
                           const std::string& elem3, const std::string& elem4,
                           const std::string& elem5)
{
  return Glib::convert_return_gchar_ptr_to_stdstring(g_build_filename(
          elem1.c_str(), elem2.c_str(), elem3.c_str(), elem4.c_str(),
          elem5.c_str(), NULLPOINTER));
}

std::string build_filename(const std::string& elem1, const std::string& elem2,
                           const std::string& elem3, const std::string& elem4,
                           const std::string& elem5, const std::string& elem6)
{
  return Glib::convert_return_gchar_ptr_to_stdstring(g_build_filename(
          elem1.c_str(), elem2.c_str(), elem3.c_str(), elem4.c_str(),
          elem5.c_str(), elem6.c_str(), NULLPOINTER));
}

std::string build_filename(const std::string& elem1, const std::string& elem2,
                           const std::string& elem3, const std::string& elem4,
                           const std::string& elem5, const std::string& elem6,
                           const std::string& elem7)
{
  return Glib::convert_return_gchar_ptr_to_stdstring(g_build_filename(
          elem1.c_str(), elem2.c_str(), elem3.c_str(), elem4.c_str(),
          elem5.c_str(), elem6.c_str(), elem7.c_str(), NULLPOINTER));
}

std::string build_filename(const std::string& elem1, const std::string& elem2,
                           const std::string& elem3, const std::string& elem4,
                           const std::string& elem5, const std::string& elem6,
                           const std::string& elem7, const std::string& elem8)
{
  return Glib::convert_return_gchar_ptr_to_stdstring(g_build_filename(
          elem1.c_str(), elem2.c_str(), elem3.c_str(), elem4.c_str(),
          elem5.c_str(), elem6.c_str(), elem7.c_str(), elem8.c_str(),
          NULLPOINTER));
}

std::string build_filename(const std::string& elem1, const std::string& elem2,
                           const std::string& elem3, const std::string& elem4,
                           const std::string& elem5, const std::string& elem6,
                           const std::string& elem7, const std::string& elem8,
                           const std::string& elem9)
{
  return Glib::convert_return_gchar_ptr_to_stdstring(g_build_filename(
          elem1.c_str(), elem2.c_str(), elem3.c_str(), elem4.c_str(),
          elem5.c_str(), elem6.c_str(), elem7.c_str(), elem8.c_str(),
          elem9.c_str(), NULLPOINTER));
}

Glib::ustring
format_bytes(uint64_t size, uint64_t max_size, bool to_bits)
{
    gchar* retp;

    struct Format
    {
        uint64_t factor;
        const char* string;
    };
    
    const Format all_formats[2][BYTE_UNITS_COUNT] = {
        {
            { 1 << 10, N_("%.1f KiB") },
            { 1 << 20, N_("%.1f MiB") },
            { 1 << 30, N_("%.1f GiB") },
            { NUM_1TiB, N_("%.1f TiB") }
        },
        {
            { 1000, N_("%.1f kbit") },
            { 1000000, N_("%.1f Mbit") },
            { 1000000000, N_("%.1f Gbit") },
            { NUM_1Tbit, N_("%.1f Tbit") }
        }
    };

    const Format(&formats)[BYTE_UNITS_COUNT] = all_formats[to_bits ? 1 : 0];

    if (to_bits)
    {
        size *= 8;
        max_size *= 8;
    }

    if (max_size == 0)
        max_size = size;

    if (max_size < formats[0].factor)
    {
        const char *format = (to_bits
                ? dngettext(GETTEXT_PACKAGE, "%u bit", "%u bits", (guint) size)
                : dngettext(GETTEXT_PACKAGE, "%u byte", "%u bytes", (guint) size));
        retp = g_strdup_printf(format, (guint) size);
    }
    else
    {
        uint64_t factor;
        const char* format = NULL;

        for (int i = 1; i < BYTE_UNITS_COUNT; i++)
        {
            if (max_size < formats[i].factor)
            {
                factor = formats[i - 1].factor;
                format = formats[i - 1].string;
                break;
            }
        }
        if (format == NULL)
        {
            factor = formats[BYTE_UNITS_COUNT - 1].factor;
            format = formats[BYTE_UNITS_COUNT - 1].string;
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
