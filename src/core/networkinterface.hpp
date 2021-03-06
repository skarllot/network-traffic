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

#include <stdint.h>
#include <glibmm/ustring.h>
#include <vector>

/** Base class that provides basic information from network interfaces.
 */
class NetworkInterface
{
public:
    NetworkInterface();
    virtual ~NetworkInterface();

    /** Gets NetworkInterface instances for all network interfaces found in
     * current system.
     *
     * @return A network interfaces information vector.
     */
    static std::vector<NetworkInterface*> get_all_network_interfaces();

    /** Gets a number that represents a count of network interfaces found in
     * current system.
     *
     * @return Network interfaces count.
     */
    static int get_interface_count();

    /** Gets a NetworkInterface instance by its internal name.
     *
     * @param ifname System name for this network interface.
     */
    static NetworkInterface* get_network_interface(Glib::ustring ifname);

    /** Gets the bytes received by this network interface.
     */
    virtual uint64_t get_bytes_received() const = 0;

    /** Gets the bytes sent by this network interface.
     */
    virtual uint64_t get_bytes_sent() const = 0;

    /** Gets system name for this network interface.
     */
    virtual Glib::ustring get_internal_name() const = 0;

    /** Gets user name for this network interface.
     */
    virtual Glib::ustring get_name() const = 0;

    /** Gets the Media Access Control address from this network interface.
     */
    virtual Glib::ustring get_physical_address() const = 0;

    /** Gets true whether this network interface is valid.
     */
    virtual bool is_valid() const = 0;
};

#endif	/* _NETWORKINTERFACE_H */

