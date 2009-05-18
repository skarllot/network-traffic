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

#include <libglademm.h>
#include "functions.hpp"

#define GLADEFILE "ui.glade"
#define GLADEROOT "wndMain"

wndMain::wndMain()
{
    Glib::RefPtr<Gnome::Glade::Xml> refXml;
    try
    {
        refXml = Gnome::Glade::Xml::create(NETWORK_LOGGER_GLADEDIR GLADEFILE,
                GLADEROOT);
    }
    catch (Gnome::Glade::XmlError& error)
    {
        try
        {
            refXml = Gnome::Glade::Xml::create("src/" GLADEFILE, GLADEROOT);
        }
        catch (Gnome::Glade::XmlError& error2)
        {
            show_error(error.what(), true);
        }
    }
    window = NULL;
    refXml->get_widget(GLADEROOT, window);
}

wndMain::~wndMain()
{
}

Gtk::Window* wndMain::get_root()
{
    return this->window;
}

