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

#ifndef _FUNCTIONS_TEMPLATES_H
#define	_FUNCTIONS_TEMPLATES_H

#ifndef __FUNCTIONS_H_INSIDE__
#error "Only <functions.hpp> can be included directly."
#endif

#include <gtkmm.h>

#define NULLPOINTER static_cast<void*>(0)

template <class T1, class T2>
Glib::ustring build_filename(const T1& str1, const T2& str2)
{
    Glib::ustring ustr1 = Glib::ustring::compose("%1", str1);
    Glib::ustring ustr2 = Glib::ustring::compose("%1", str2);

    gchar* path;

    path = g_build_filename(ustr1.c_str(), ustr2.c_str(), NULLPOINTER);

    Glib::ustring r_path(path);
    g_free(path);
    return r_path;
};

template <class T1, class T2, class T3>
Glib::ustring build_filename(const T1& str1, const T2& str2, const T3& str3)
{
    Glib::ustring ustr1 = Glib::ustring::compose("%1", str1);
    Glib::ustring ustr2 = Glib::ustring::compose("%1", str2);
    Glib::ustring ustr3 = Glib::ustring::compose("%1", str3);

    gchar* path;

    path = g_build_filename(ustr1.c_str(), ustr2.c_str(), ustr3.c_str(),
            NULLPOINTER);

    Glib::ustring r_path(path);
    g_free(path);
    return r_path;
};

template <class T1, class T2, class T3, class T4>
Glib::ustring build_filename(const T1& str1, const T2& str2, const T3& str3,
        const T4& str4)
{
    Glib::ustring ustr1 = Glib::ustring::compose("%1", str1);
    Glib::ustring ustr2 = Glib::ustring::compose("%1", str2);
    Glib::ustring ustr3 = Glib::ustring::compose("%1", str3);
    Glib::ustring ustr4 = Glib::ustring::compose("%1", str4);

    gchar* path;

    path = g_build_filename(ustr1.c_str(), ustr2.c_str(), ustr3.c_str(),
            ustr4.c_str(), NULLPOINTER);

    Glib::ustring r_path(path);
    g_free(path);
    return r_path;
};

template <class T1, class T2, class T3, class T4, class T5>
Glib::ustring build_filename(const T1& str1, const T2& str2, const T3& str3,
        const T4& str4, const T5& str5)
{
    Glib::ustring ustr1 = Glib::ustring::compose("%1", str1);
    Glib::ustring ustr2 = Glib::ustring::compose("%1", str2);
    Glib::ustring ustr3 = Glib::ustring::compose("%1", str3);
    Glib::ustring ustr4 = Glib::ustring::compose("%1", str4);
    Glib::ustring ustr5 = Glib::ustring::compose("%1", str5);

    gchar* path;

    path = g_build_filename(ustr1.c_str(), ustr2.c_str(), ustr3.c_str(),
            ustr4.c_str(), ustr5.c_str(), NULLPOINTER);

    Glib::ustring r_path(path);
    g_free(path);
    return r_path;
};

template <class T1, class T2, class T3, class T4, class T5, class T6>
Glib::ustring build_filename(const T1& str1, const T2& str2, const T3& str3,
        const T4& str4, const T5& str5, const T6& str6)
{
    Glib::ustring ustr1 = Glib::ustring::compose("%1", str1);
    Glib::ustring ustr2 = Glib::ustring::compose("%1", str2);
    Glib::ustring ustr3 = Glib::ustring::compose("%1", str3);
    Glib::ustring ustr4 = Glib::ustring::compose("%1", str4);
    Glib::ustring ustr5 = Glib::ustring::compose("%1", str5);
    Glib::ustring ustr6 = Glib::ustring::compose("%1", str6);

    gchar* path;

    path = g_build_filename(ustr1.c_str(), ustr2.c_str(), ustr3.c_str(),
            ustr4.c_str(), ustr5.c_str(), ustr6.c_str(), NULLPOINTER);

    Glib::ustring r_path(path);
    g_free(path);
    return r_path;
};

template <class T1, class T2, class T3, class T4, class T5, class T6, class T7>
Glib::ustring build_filename(const T1& str1, const T2& str2, const T3& str3,
        const T4& str4, const T5& str5, const T6& str6, const T7& str7)
{
    Glib::ustring ustr1 = Glib::ustring::compose("%1", str1);
    Glib::ustring ustr2 = Glib::ustring::compose("%1", str2);
    Glib::ustring ustr3 = Glib::ustring::compose("%1", str3);
    Glib::ustring ustr4 = Glib::ustring::compose("%1", str4);
    Glib::ustring ustr5 = Glib::ustring::compose("%1", str5);
    Glib::ustring ustr6 = Glib::ustring::compose("%1", str6);
    Glib::ustring ustr7 = Glib::ustring::compose("%1", str7);

    gchar* path;

    path = g_build_filename(ustr1.c_str(), ustr2.c_str(), ustr3.c_str(),
            ustr4.c_str(), ustr5.c_str(), ustr6.c_str(), ustr7.c_str(),
            NULLPOINTER);

    Glib::ustring r_path(path);
    g_free(path);
    return r_path;
};

template <class T1, class T2, class T3, class T4, class T5, class T6, class T7,
class T8>
Glib::ustring build_filename(const T1& str1, const T2& str2, const T3& str3,
        const T4& str4, const T5& str5, const T6& str6, const T7& str7,
        const T8& str8)
{
    Glib::ustring ustr1 = Glib::ustring::compose("%1", str1);
    Glib::ustring ustr2 = Glib::ustring::compose("%1", str2);
    Glib::ustring ustr3 = Glib::ustring::compose("%1", str3);
    Glib::ustring ustr4 = Glib::ustring::compose("%1", str4);
    Glib::ustring ustr5 = Glib::ustring::compose("%1", str5);
    Glib::ustring ustr6 = Glib::ustring::compose("%1", str6);
    Glib::ustring ustr7 = Glib::ustring::compose("%1", str7);
    Glib::ustring ustr8 = Glib::ustring::compose("%1", str8);

    gchar* path;

    path = g_build_filename(ustr1.c_str(), ustr2.c_str(), ustr3.c_str(),
            ustr4.c_str(), ustr5.c_str(), ustr6.c_str(), ustr7.c_str(),
            ustr8.c_str(), NULLPOINTER);

    Glib::ustring r_path(path);
    g_free(path);
    return r_path;
};

template <class T1, class T2, class T3, class T4, class T5, class T6, class T7,
class T8, class T9>
Glib::ustring build_filename(const T1& str1, const T2& str2, const T3& str3,
        const T4& str4, const T5& str5, const T6& str6, const T7& str7,
        const T8& str8, const T9& str9)
{
    Glib::ustring ustr1 = Glib::ustring::compose("%1", str1);
    Glib::ustring ustr2 = Glib::ustring::compose("%1", str2);
    Glib::ustring ustr3 = Glib::ustring::compose("%1", str3);
    Glib::ustring ustr4 = Glib::ustring::compose("%1", str4);
    Glib::ustring ustr5 = Glib::ustring::compose("%1", str5);
    Glib::ustring ustr6 = Glib::ustring::compose("%1", str6);
    Glib::ustring ustr7 = Glib::ustring::compose("%1", str7);
    Glib::ustring ustr8 = Glib::ustring::compose("%1", str8);
    Glib::ustring ustr9 = Glib::ustring::compose("%1", str9);

    gchar* path;

    path = g_build_filename(ustr1.c_str(), ustr2.c_str(), ustr3.c_str(),
            ustr4.c_str(), ustr5.c_str(), ustr6.c_str(), ustr7.c_str(),
            ustr8.c_str(), ustr9.c_str(), NULLPOINTER);

    Glib::ustring r_path(path);
    g_free(path);
    return r_path;
};

#endif	/* _FUNCTIONS_TEMPLATES_HPP */

