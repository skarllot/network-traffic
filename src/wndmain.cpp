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
#if (defined(WIN32) || defined(WINNT))
#include "windowsdef.h"
#endif
#include <vector>
#include "functions.hpp"
#include "networkinterface.hpp"

#define GLADEFILE "ui.glade"
#define GLADEROOT "wndMain"

wndMain::wndMain()
{
    try
    {
#ifndef TEST
        refXml = Gnome::Glade::Xml::create(
                NETWORK_LOGGER_GLADEDIR "/" GLADEFILE, GLADEROOT);
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
}

void wndMain::fill_cbointerfaces()
{
    std::vector<NetworkInterface*> netifs =
            NetworkInterface::get_all_network_interfaces();
    std::vector<NetworkInterface*>::iterator iter;

    Glib::RefPtr<Gtk::ListStore> cbomodel =
            Gtk::ListStore::create(m_columns);
    cbo_interfaces->set_model(cbomodel);

    for (iter = netifs.begin(); iter != netifs.end(); iter++)
    {
        Gtk::TreeModel::Row row = *(cbomodel->append());
        row[m_columns.m_col_name] = (**iter).get_name();
    }
    
    cbo_interfaces->pack_start(m_columns.m_col_name);

    // Free all vector items
    for (iter = netifs.begin(); iter != netifs.end(); iter++)
        delete *iter;
    netifs.clear();
}

Gtk::ComboBox* wndMain::get_cbointerfaces()
{
    return this->cbo_interfaces;
}

Gtk::Window* wndMain::get_root()
{
    return this->wnd_root;
}

