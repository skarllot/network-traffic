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

#include "wndmain.hpp"

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifdef WINNT
#include "windowsdef.h"
#endif
#include "functions.hpp"

#define GLADEFILE "ui.glade"
#define GLADEROOT "wndMain"

wndMain::wndMain()
{
    try
    {
#ifndef TEST
        refXml = Gnome::Glade::Xml::create(
                GLADEDIR "/" GLADEFILE, GLADEROOT);
#else
        refXml = Gnome::Glade::Xml::create(
                LOCALPATH "/src/" GLADEFILE, GLADEROOT);
#endif
    }
    catch (Gnome::Glade::XmlError& error)
    {
        show_error(error.what(), true);
    }

    wnd_root = NULL;
    cbo_interfaces = NULL;
    refXml->get_widget(GLADEROOT, wnd_root);
    refXml->get_widget("cbo_interfaces", cbo_interfaces);

    this->fill_cbointerfaces();
}

wndMain::~wndMain()
{
    if (wnd_root)
        delete wnd_root;

    // Free all vector items
    std::vector<NetworkInterface*>::iterator iter;
    for (iter = network_interfaces.begin();
            iter != network_interfaces.end(); iter++)
    {
        delete *iter;
    }
    network_interfaces.clear();
}

void wndMain::fill_cbointerfaces()
{
    network_interfaces = NetworkInterface::get_all_network_interfaces();
    std::vector<NetworkInterface*>::iterator iter;

    Glib::RefPtr<Gtk::ListStore> cbomodel =
            Gtk::ListStore::create(m_columns);
    cbo_interfaces->set_model(cbomodel);

    for (iter = network_interfaces.begin();
            iter != network_interfaces.end(); iter++)
    {
        Gtk::TreeModel::Row row = *(cbomodel->append());
        row[m_columns.m_col_name] = (**iter).get_name();
    }

    cbo_interfaces->pack_start(m_columns.m_col_name);
}

Gtk::ComboBox* wndMain::get_cbointerfaces()
{
    return this->cbo_interfaces;
}

Gtk::Window* wndMain::get_root()
{
    return this->wnd_root;
}

