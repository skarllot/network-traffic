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