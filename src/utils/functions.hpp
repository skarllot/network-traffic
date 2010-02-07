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

#ifndef _FUNCTIONS_H
#define	_FUNCTIONS_H

#define __FUNCTIONS_H_INSIDE__

#include <gtkmm.h>
#include <stdint.h>

// Based on http://git.gnome.org/cgit/gnome-system-monitor/tree/src/util.cpp
/** Formats the file size passed in @bytes in a way that is easy for
 * the user to read. Gives the size in bytes, kibibytes, mebibytes or
 * gibibytes, choosing whatever is appropriate.
 *
 * @size A size in bytes.
 * @max_size A size to adjust unit
 * @to_bits A value to indicates whether should use bits instead of bytes.
 * @return A string with the size ready to be shown.
 */
Glib::ustring
format_bytes(uint64_t size, uint64_t max_size = 0, bool to_bits = false);

// Based on http://git.gnome.org/cgit/gnome-system-monitor/tree/src/util.cpp
/** Formats the rate passed in @bytes in a way that is easy for the user to
 * read.
 *
 * @rate A rate in bytes per second.
 * @max_size A size to adjust unit
 * @to_bits A value to indicates whether should use bits instead of bytes.
 * @return A string with the rate ready to be shown.
 */
Glib::ustring
format_bytes_rate(uint64_t rate, uint64_t max_size = 0, bool to_bits = false);

// Based on http://git.gnome.org/cgit/hardware-monitor/tree/src/helpers.cpp
// (Copyright (c) 2003 Ole Laursen)
/** Shows an error message dialog.
 *
 * @param msg Message to show in dialog.
 * @param canexit True whether should call program exit.
 */
void show_error(const Glib::ustring& msg, bool canexit = false);

/** Creates a filename from a series of elements using the correct separator
 * for filenames.
 *
 * @param str1 The first element in the path.
 * @param str2 The second element in the path.
 */
template <class T1, class T2>
Glib::ustring build_filename(const T1& str1, const T2& str2);

/** Creates a filename from a series of elements using the correct separator
 * for filenames.
 *
 * @param str1 The first element in the path.
 * @param str2 The second element in the path.
 * @param str3 The third element in the path.
 */
template <class T1, class T2, class T3>
Glib::ustring build_filename(const T1& str1, const T2& str2, const T3& str3);

/** Creates a filename from a series of elements using the correct separator
 * for filenames.
 *
 * @param str1 The first element in the path.
 * @param str2 The second element in the path.
 * @param str3 The third element in the path.
 * @param str4 The fourth element in the path.
 */
template <class T1, class T2, class T3, class T4>
Glib::ustring build_filename(const T1& str1, const T2& str2, const T3& str3,
        const T4& str4);

/** Creates a filename from a series of elements using the correct separator
 * for filenames.
 *
 * @param str1 The first element in the path.
 * @param str2 The second element in the path.
 * @param str3 The third element in the path.
 * @param str4 The fourth element in the path.
 * @param str5 The fifth element in the path.
 */
template <class T1, class T2, class T3, class T4, class T5>
Glib::ustring build_filename(const T1& str1, const T2& str2, const T3& str3,
        const T4& str4, const T5& str5);

/** Creates a filename from a series of elements using the correct separator
 * for filenames.
 *
 * @param str1 The first element in the path.
 * @param str2 The second element in the path.
 * @param str3 The third element in the path.
 * @param str4 The fourth element in the path.
 * @param str5 The fifth element in the path.
 * @param str6 The sixth element in the path.
 */
template <class T1, class T2, class T3, class T4, class T5, class T6>
Glib::ustring build_filename(const T1& str1, const T2& str2, const T3& str3,
        const T4& str4, const T5& str5, const T6& str6);

/** Creates a filename from a series of elements using the correct separator
 * for filenames.
 *
 * @param str1 The first element in the path.
 * @param str2 The second element in the path.
 * @param str3 The third element in the path.
 * @param str4 The fourth element in the path.
 * @param str5 The fifth element in the path.
 * @param str6 The sixth element in the path.
 * @param str7 The seventh element in the path.
 */
template <class T1, class T2, class T3, class T4, class T5, class T6, class T7>
Glib::ustring build_filename(const T1& str1, const T2& str2, const T3& str3,
        const T4& str4, const T5& str5, const T6& str6, const T7& str7);

/** Creates a filename from a series of elements using the correct separator
 * for filenames.
 *
 * @param str1 The first element in the path.
 * @param str2 The second element in the path.
 * @param str3 The third element in the path.
 * @param str4 The fourth element in the path.
 * @param str5 The fifth element in the path.
 * @param str6 The sixth element in the path.
 * @param str7 The seventh element in the path.
 * @param str8 The eighth element in the path.
 */
template <class T1, class T2, class T3, class T4, class T5, class T6, class T7,
class T8>
Glib::ustring build_filename(const T1& str1, const T2& str2, const T3& str3,
        const T4& str4, const T5& str5, const T6& str6, const T7& str7,
        const T8& str8);

/** Creates a filename from a series of elements using the correct separator
 * for filenames.
 *
 * @param str1 The first element in the path.
 * @param str2 The second element in the path.
 * @param str3 The third element in the path.
 * @param str4 The fourth element in the path.
 * @param str5 The fifth element in the path.
 * @param str6 The sixth element in the path.
 * @param str7 The seventh element in the path.
 * @param str8 The eighth element in the path.
 * @param str9 The ninth element in the path.
 */
template <class T1, class T2, class T3, class T4, class T5, class T6, class T7,
class T8, class T9>
Glib::ustring build_filename(const T1& str1, const T2& str2, const T3& str3,
        const T4& str4, const T5& str5, const T6& str6, const T7& str7,
        const T8& str8, const T9& str9);

#include "functions_templates.hpp"

#undef __FUNCTIONS_H_INSIDE__

#endif /* _FUNCTIONS_H */
