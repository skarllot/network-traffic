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

#ifndef _NETWORKINTERFACE_H
#define	_NETWORKINTERFACE_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <glibmm/ustring.h>
#include <vector>

/** Base class that provides basic network interface information.
 */
class NetworkInterface
{
public:
    NetworkInterface();
    NetworkInterface(const NetworkInterface& orig);
    virtual ~NetworkInterface();

    /** Gets an array or NetworkInterface for all computer network interfaces.
     *
     * @return A vector of NetworkInterface.
     */
    static std::vector<NetworkInterface*> get_all_network_interfaces();

    /** Gets a number that represents a count of computer network interfaces.
     */
    static int get_interface_count();

    /** Gets the bytes received by this interface.
     */
    virtual uint64_t get_bytes_received() = 0;

    /** Gets the bytes sent by this interface.
     */
    virtual uint64_t get_bytes_sent() = 0;

    /** Gets the name of this network interface.
     */
    virtual Glib::ustring get_name() = 0;

protected:
    // Fields:
    Glib::ustring name;
    uint64_t in_bytes;
    uint64_t out_bytes;
};

#endif	/* _NETWORKINTERFACE_H */

