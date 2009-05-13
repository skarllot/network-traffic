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

#ifndef _WIN_NETWORKINTERFACE_H
#define	_WIN_NETWORKINTERFACE_H

#include "networkinterface.h"

#include <map>
#include "windowsdef.h"
#include <iphlpapi.h>

#if (WINVER >= 0x0600)
#include "mingw32-extension/iphlpapi2.h"
#endif

class win_NetworkInterface : NetworkInterface
{
public:
    virtual ~win_NetworkInterface();

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
    virtual uint64_t get_bytes_received();

    /** Gets the bytes sent by this interface.
     */
    virtual uint64_t get_bytes_sent();

    /** Gets the system name of this network interface.
     */
    virtual Glib::ustring get_internal_name();

    /** Gets the name of this network interface.
     */
    virtual Glib::ustring get_name();

    /** Gets the Media Access Control address of this network interface.
     */
    virtual Glib::ustring get_physical_address();

private:
    win_NetworkInterface(const IP_ADAPTER_ADDRESSES* ifinfo,
            IP_ADAPTER_ADDRESSES* maininfo);

    static MIB_IFROW* get_if_detail(DWORD ifindex);
    #if (WINVER >= 0x0600)
    static MIB_IF_ROW2* get_if_detail2(DWORD ifindex);
    #endif
    static IP_ADAPTER_ADDRESSES* get_ifs_info();
    void alloc_maininfo();
    void free_maininfo();

    IP_ADAPTER_ADDRESSES ifinfo;
    IP_ADAPTER_ADDRESSES* maininfo;

    static std::map<IP_ADAPTER_ADDRESSES*, int> ifs_references;
};

#endif	/* _WIN_NETWORKINTERFACE_H */
