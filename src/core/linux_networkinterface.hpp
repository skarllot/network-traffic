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

#ifndef _NIX_NETWORKINTERFACE_H
#define	_NIX_NETWORKINTERFACE_H

#include "networkinterface.hpp"
#include <ifaddrs.h>
#include <map>
#include <string.h>

/** Class that provides basic network interface information for *nix systems.
 */
class linux_NetworkInterface : NetworkInterface
{
public:
    virtual ~linux_NetworkInterface();

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

    /** Gets the bytes received by this network interface.
     */
    virtual uint64_t get_bytes_received();

    /** Gets the bytes sent by this network interface.
     */
    virtual uint64_t get_bytes_sent();

    /** Gets system name for this network interface.
     */
    virtual Glib::ustring get_internal_name();

    /** Gets user name for this network interface.
     */
    virtual Glib::ustring get_name();

    /** Gets the Media Access Control address from this network interface.
     */
    virtual Glib::ustring get_physical_address();
    
private:
    /** Constructs new instance based on parameters.
     * 
     * @param ifinfo Network interface native information.
     * @param firstinfo Network interface got by linked list.
     */
    linux_NetworkInterface(const ifaddrs* ifinfo, ifaddrs* firstinfo);

    /** Add info for same interface but different protocol (e.g. IPv6)
     *
     * @param ifinfo Network interface native information.
     */
    void add_info(const ifaddrs* ifinfo);
    /** Reads sysfs network information file.
     *
     * @param path The file where information is read from.
     */
    std::string read_sysfs(std::string path);

    /// Current native network interface information list.
    std::vector<ifaddrs> ifinfo;
    /// Current native top network interface information from linked list.
    ifaddrs* firstinfo;

    /// Store network interface information reference counting for all
    /// nix_networkinterface instances.
    static std::map<ifaddrs*, int> ifs_references;
};

#endif	/* _NIX_NETWORKINTERFACE_H */
