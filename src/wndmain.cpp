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
#include "utils/windowsdef.h"
#endif
#include <string>
#include "utils/functions.hpp"
#include "utils/i18n.hpp"
#include "shareddef.h"
#include "program-info.h"

#define GLADEFILE "ui.glade"
#define GLADEROOT "wndMain"
#define REFRESH_MS 500

wndMain::wndMain()
{
    try
    {
        Glib::ustring file_path = build_filename(glade_dir, GLADEFILE);
        refXml = Gnome::Glade::Xml::create(file_path, GLADEROOT);
    }
    catch (Gnome::Glade::XmlError& error)
    {
        show_error(error.what(), true);
    }

    // wndmain
    wnd_root = NULL;
    refXml->get_widget(GLADEROOT, wnd_root);
    wnd_root->set_title(_(PROGRAM_NAME));
    wnd_root->set_default_icon_name(PROGRAM_ICON_NAME);

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

    // mnu_quit
    mnu_quit = NULL;
    refXml->get_widget("mnu_quit", mnu_quit);
    mnu_quit->signal_activate().connect(sigc::mem_fun(*this,
            &wndMain::on_mnuquit_activate));

    // mnu_about
    mnu_about = NULL;
    refXml->get_widget("mnu_about", mnu_about);
    mnu_about->signal_activate().connect(sigc::mem_fun(*this,
            &wndMain::on_mnuabout_activate));

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
    if (index == -1)
        return false;

    tooltip->set_markup(COMPOSE(_("<b>Internal name:</b> %1\n"
            "<b>Physical address:</b> %2"),
            network_interfaces[index]->get_internal_name(),
            network_interfaces[index]->get_physical_address()));
    return true;
}

void wndMain::on_link_clicked(Gtk::Widget& widget, const Glib::ustring& link)
{
    gtk_show_uri(NULL, link.c_str(), GDK_CURRENT_TIME, NULL);
}

void wndMain::on_mnuabout_activate()
{
    Gtk::AboutDialog *wndabout = NULL;
    wndabout = new Gtk::AboutDialog;

    wndabout->set_artists(PROGRAM_ARTISTS);
    wndabout->set_authors(PROGRAM_AUTHORS);
    wndabout->set_comments(_(PROGRAM_COMMENTS));
    wndabout->set_copyright(PROGRAM_COPYRIGHT);
    wndabout->set_documenters(PROGRAM_DOCUMENTERS);
    wndabout->set_license(_(PROGRAM_LICENSE));
    wndabout->set_logo_icon_name(PROGRAM_ICON_NAME);
    wndabout->set_name(_(PROGRAM_NAME));
    wndabout->set_translator_credits(_(PROGRAM_TRANSLATORS));
    wndabout->set_version(VERSION);
    wndabout->set_website(PROGRAM_WEBSITE);
    wndabout->set_website_label(_(PROGRAM_WEBSITE_LABEL));

    wndabout->set_url_hook(sigc::mem_fun(*this, &wndMain::on_link_clicked));
    wndabout->run();

    delete wndabout;
}

void wndMain::on_mnuquit_activate()
{
    wnd_root->hide();
}

void wndMain::refresh_all_information()
{
    int index = cbo_interfaces->get_active_row_number();
    if (index == -1)
        return;

    lbl_bytes_received->set_text(
            format_bytes(network_interfaces[index]->get_bytes_received()));
    lbl_bytes_sent->set_text(
            format_bytes(network_interfaces[index]->get_bytes_sent()));
}

bool wndMain::timed_refresh()
{
    refresh_all_information();
    return true;
}

