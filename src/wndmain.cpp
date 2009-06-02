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
#include "i18n.hpp"

#define GLADEFILE "ui.glade"
#define GLADEROOT "wndMain"
#define REFRESH_MS 500

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

    // wndmain
    wnd_root = NULL;
    refXml->get_widget(GLADEROOT, wnd_root);

    // cbo_interfaces
    cbo_interfaces = NULL;
    refXml->get_widget("cbo_interfaces", cbo_interfaces);
    SingleTextModel mcolumn;
    Glib::RefPtr<Gtk::ListStore> cbomodel = Gtk::ListStore::create(mcolumn);
    cbo_interfaces->set_model(cbomodel);
    cbo_interfaces->pack_start(mcolumn.m_col_name);
    cbo_interfaces->signal_changed().connect(sigc::mem_fun(*this,
            &wndMain::refresh_all_information));
    cbo_interfaces->set_has_tooltip(true);
    cbo_interfaces->signal_query_tooltip().connect(sigc::mem_fun(*this,
            &wndMain::on_cbointerfaces_query_tooltip));

    // lbl_bytes_received
    lbl_bytes_received = NULL;
    refXml->get_widget("lbl_bytes_received", lbl_bytes_received);

    // lbl_bytes_sent
    lbl_bytes_sent = NULL;
    refXml->get_widget("lbl_bytes_sent", lbl_bytes_sent);


    this->fill_cbointerfaces();
    if (network_interfaces.size() > 0)
        cbo_interfaces->set_active(0);
    Glib::signal_timeout().connect(sigc::mem_fun(*this,
            &wndMain::timed_refresh), REFRESH_MS, Glib::PRIORITY_LOW);
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

    SingleTextModel mcolumn;
    Glib::RefPtr<Gtk::ListStore> cbomodel =
            Glib::RefPtr<Gtk::ListStore>::cast_dynamic(
            cbo_interfaces->get_model());

    for (iter = network_interfaces.begin();
            iter != network_interfaces.end(); iter++)
    {
        Gtk::TreeModel::Row row = *(cbomodel->append());
        row[mcolumn.m_col_name] = (**iter).get_name();
    }
}

Gtk::ComboBox* wndMain::get_cbointerfaces()
{
    return this->cbo_interfaces;
}

Gtk::Window* wndMain::get_root()
{
    return this->wnd_root;
}

bool wndMain::on_cbointerfaces_query_tooltip(int x, int y,
        bool keyboard_tooltip, const Glib::RefPtr<Gtk::Tooltip>& tooltip)
{
    int index = cbo_interfaces->get_active_row_number();

    tooltip->set_markup(COMPOSE("<b>Internal name:</b> %1\n"
            "<b>Physical address:</b> %2",
            network_interfaces[index]->get_internal_name(),
            network_interfaces[index]->get_physical_address()));
    return true;
}

void wndMain::refresh_all_information()
{
    int index = cbo_interfaces->get_active_row_number();

    lbl_bytes_received->set_text(COMPOSE("%1 B",
            network_interfaces[index]->get_bytes_received()));
    lbl_bytes_sent->set_text(COMPOSE("%1 B",
            network_interfaces[index]->get_bytes_sent()));
}

bool wndMain::timed_refresh()
{
    refresh_all_information();
    return true;
}

