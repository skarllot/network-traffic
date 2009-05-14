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

#ifndef _I18N_H
#define	_I18N_H

#include <glibmm/i18n.h>
#include <glibmm/ustring.h>

// ustring text = ustring::compose("%1 of %2 done (%3%%)", 7, 20, 35);
// -> text = "7 of 20 done (35%)"
#define COMPOSE Glib::ustring::compose

// ustring text = ustring::format(std::setfill(L'0'), std::setw(6), 123);
// -> text = "000123"
#define FORMAT Glib::ustring::format

#endif	/* _I18N_H */

