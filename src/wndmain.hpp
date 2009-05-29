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

#ifndef _WNDMAIN_H
#define	_WNDMAIN_H

#include <gtkmm.h>
#include <libglademm.h>

class wndMain
{
public:
    wndMain();
    virtual ~wndMain();

    Gtk::ComboBox* get_cbointerfaces();
    Gtk::Window* get_root();

private:

    class ModelColumns : public Gtk::TreeModel::ColumnRecord
    {
    public:
        ModelColumns()
        {
            add(m_col_name);
        }

        Gtk::TreeModelColumn<Glib::ustring> m_col_name;
    };

    Gtk::ComboBox* cbo_interfaces;
    ModelColumns m_columns;
    Glib::RefPtr<Gnome::Glade::Xml> refXml;
    Gtk::Window* wnd_root;

    void fill_cbointerfaces();
};

#endif	/* _WNDMAIN_H */
