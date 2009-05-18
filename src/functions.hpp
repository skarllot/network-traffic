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

#include <gtkmm.h>

// Based on http://git.gnome.org/cgit/hardware-monitor/tree/src/helpers.cpp
// (Copyright (c) 2003 Ole Laursen)
/** Shows an error message dialog.
 *
 * @param msg Message to show in dialog.
 * @param canexit True whether should call program exit.
 */
void show_error(const Glib::ustring& msg, bool canexit = false);