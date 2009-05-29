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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <gtkmm.h>
#include "i18n.hpp"
#include "networkinterface.hpp"
#include "wndmain.hpp"

#if (defined(WIN32) || defined(WINNT))
#include "windowsdef.h"
#endif

int main(int argc, char** argv)
{
#if (defined(WIN32) || defined(WINNT))
    int retval = check_version();
    if (retval != NO_ERROR)
        return retval;
#endif

    // Gettext initialization
    bindtextdomain(GETTEXT_PACKAGE, NETWORK_LOGGER_LOCALEDIR);
    bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
    textdomain(GETTEXT_PACKAGE);

    Gtk::Main kit(argc, argv);
    wndMain wndmain;
    kit.run(*wndmain.get_root());
/*
    std::vector<NetworkInterface*> netifs =
            NetworkInterface::get_all_network_interfaces();

    std::vector<NetworkInterface*>::iterator iter;
    for (int i = 0; i < 6; i++)
    {
        for (iter = netifs.begin(); iter != netifs.end(); iter++)
        {
            std::cout << COMPOSE(_("Name: %1"),
                    (**iter).get_name()) << std::endl;
            std::cout << COMPOSE(_("Internal name: %1"),
                    (**iter).get_internal_name()) << std::endl;
            std::cout << COMPOSE(_("Physical address: %1"),
                    (**iter).get_physical_address()) << std::endl;
            std::cout << COMPOSE(_("Bytes in: %1"),
                    (**iter).get_bytes_received()) << std::endl;
            std::cout << COMPOSE(_("Bytes out: %1"),
                    (**iter).get_bytes_sent()) << std::endl;
            std::cout << std::endl;
        }
        std::cout << "--------------------" << std::endl;

        // Wait 1 second
        Glib::usleep(G_USEC_PER_SEC);
    }

    // Free all vector items
    for (iter = netifs.begin(); iter != netifs.end(); iter++)
        delete *iter;
    netifs.clear();
*/
    return (EXIT_SUCCESS);
}

