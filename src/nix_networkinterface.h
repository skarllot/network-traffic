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

#include "networkinterface.h"
#include <ifaddrs.h>
#include <map>

class nix_NetworkInterface : NetworkInterface
{
public:
    virtual ~nix_NetworkInterface();

    /** Gets an array or NetworkInterface for all computer network interfaces.
     *
     * @return A vector of NetworkInterface.
     */
    static std::vector<NetworkInterface*> get_all_network_interfaces();
    static int test_code();

    /** Gets the bytes received by this interface.
     */
    virtual uint64_t get_bytes_received();

    /** Gets the bytes sent by this interface.
     */
    virtual uint64_t get_bytes_sent();

    /** Gets the name of this network interface.
     */
    virtual Glib::ustring get_name();
    
private:
    nix_NetworkInterface(const ifaddrs* ifinfo, ifaddrs* maininfo);
    nix_NetworkInterface(const nix_NetworkInterface& orig);

    void add_info(const ifaddrs* ifinfo);

    std::vector<ifaddrs> ifinfo;
    ifaddrs* maininfo;
    
    static std::map<ifaddrs*, int> ifs_references;
};

#endif	/* _NIX_NETWORKINTERFACE_H */
