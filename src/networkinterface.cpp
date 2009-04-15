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

#include <iostream>
#include "networkinterface.h"
#ifndef WINNT
#include "nix_networkinterface.h"
#else
#include "win_networkinterface.h"
#endif

NetworkInterface::NetworkInterface()
{
}

NetworkInterface::NetworkInterface(const NetworkInterface& orig)
{
}

NetworkInterface::~NetworkInterface()
{
}

NetworkInterface* NetworkInterface::get_all_network_interfaces()
{
#ifndef WINNT
    return nix_NetworkInterface::get_all_network_interfaces();
#else
    return win_NetworkInterface::get_all_network_interfaces();
#endif
}

int NetworkInterface::get_interface_count()
{
#ifndef WINNT
    return 0;
#else
    return win_NetworkInterface::get_interface_count();
#endif
}
