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

#include <gtkmm.h>
#include <stdint.h>

/** Creates a filename from two elements using the correct separator for filenames.
 * No attempt is made to force the resulting filename to be an absolute path.
 * If the first element is a relative path, the result will be a relative path.
 * @param elem1 First path element.
 * @param elem2 Second path element.
 * @return The resulting path.
 */
std::string build_filename(const std::string& elem1, const std::string& elem2);

/** Creates a filename from three elements using the correct separator for filenames.
 * No attempt is made to force the resulting filename to be an absolute path.
 * If the first element is a relative path, the result will be a relative path.
 * @param elem1 First path element.
 * @param elem2 Second path element.
 * @param elem3 Third path element.
 * @return The resulting path.
 */
std::string build_filename(const std::string& elem1, const std::string& elem2,
                           const std::string& elem3);


/** Creates a filename from four elements using the correct separator for filenames.
 * No attempt is made to force the resulting filename to be an absolute path.
 * If the first element is a relative path, the result will be a relative path.
 * @param elem1 First path element.
 * @param elem2 Second path element.
 * @param elem3 Third path element.
 * @param elem4 Fourth path element.
 * @return The resulting path.
 */
std::string build_filename(const std::string& elem1, const std::string& elem2,
                           const std::string& elem3, const std::string& elem4);

/** Creates a filename from five elements using the correct separator for filenames.
 * No attempt is made to force the resulting filename to be an absolute path.
 * If the first element is a relative path, the result will be a relative path.
 * @param elem1 First path element.
 * @param elem2 Second path element.
 * @param elem3 Third path element.
 * @param elem4 Fourth path element.
 * @param elem5 Fifth path element.
 * @return The resulting path.
 */
std::string build_filename(const std::string& elem1, const std::string& elem2,
                           const std::string& elem3, const std::string& elem4,
                           const std::string& elem5);

/** Creates a filename from six elements using the correct separator for filenames.
 * No attempt is made to force the resulting filename to be an absolute path.
 * If the first element is a relative path, the result will be a relative path.
 * @param elem1 First path element.
 * @param elem2 Second path element.
 * @param elem3 Third path element.
 * @param elem4 Fourth path element.
 * @param elem5 Fifth path element.
 * @param elem6 Sixth path element.
 * @return The resulting path.
 */
std::string build_filename(const std::string& elem1, const std::string& elem2,
                           const std::string& elem3, const std::string& elem4,
                           const std::string& elem5, const std::string& elem6);

/** Creates a filename from seven elements using the correct separator for filenames.
 * No attempt is made to force the resulting filename to be an absolute path.
 * If the first element is a relative path, the result will be a relative path.
 * @param elem1 First path element.
 * @param elem2 Second path element.
 * @param elem3 Third path element.
 * @param elem4 Fourth path element.
 * @param elem5 Fifth path element.
 * @param elem6 Sixth path element.
 * @param elem7 Seventh path element.
 * @return The resulting path.
 */
std::string build_filename(const std::string& elem1, const std::string& elem2,
                           const std::string& elem3, const std::string& elem4,
                           const std::string& elem5, const std::string& elem6,
                           const std::string& elem7);

/** Creates a filename from eight elements using the correct separator for filenames.
 * No attempt is made to force the resulting filename to be an absolute path.
 * If the first element is a relative path, the result will be a relative path.
 * @param elem1 First path element.
 * @param elem2 Second path element.
 * @param elem3 Third path element.
 * @param elem4 Fourth path element.
 * @param elem5 Fifth path element.
 * @param elem6 Sixth path element.
 * @param elem7 Seventh path element.
 * @param elem8 Eighth path element.
 * @return The resulting path.
 */
std::string build_filename(const std::string& elem1, const std::string& elem2,
                           const std::string& elem3, const std::string& elem4,
                           const std::string& elem5, const std::string& elem6,
                           const std::string& elem7, const std::string& elem8);

/** Creates a filename from nine elements using the correct separator for filenames.
 * No attempt is made to force the resulting filename to be an absolute path.
 * If the first element is a relative path, the result will be a relative path.
 * @param elem1 First path element.
 * @param elem2 Second path element.
 * @param elem3 Third path element.
 * @param elem4 Fourth path element.
 * @param elem5 Fifth path element.
 * @param elem6 Sixth path element.
 * @param elem7 Seventh path element.
 * @param elem8 Eighth path element.
 * @param elem9 Ninth path element.
 * @return The resulting path.
 */
std::string build_filename(const std::string& elem1, const std::string& elem2,
                           const std::string& elem3, const std::string& elem4,
                           const std::string& elem5, const std::string& elem6,
                           const std::string& elem7, const std::string& elem8,
                           const std::string& elem9);

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

#endif /* _FUNCTIONS_H */
