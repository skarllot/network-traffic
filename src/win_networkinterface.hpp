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

#include "networkinterface.hpp"

#include <map>
#include "windowsdef.h"
#include <iphlpapi.h>

#if (WINVER >= 0x0600)
#include "mingw32-extension/iphlpapi2.h"
#endif

/** Class that provides basic network interface information for Windows systems.
 */
class win_NetworkInterface : NetworkInterface
{
public:
    virtual ~win_NetworkInterface();

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
    win_NetworkInterface(const IP_ADAPTER_ADDRESSES* ifinfo,
            IP_ADAPTER_ADDRESSES* maininfo);

    /** Gets more information from desired network interface.
     *
     * @param ifindex System index for network interface.
     */
    static MIB_IFROW* get_if_detail(DWORD ifindex);
    #if (WINVER >= 0x0600)
    /** Gets more information from desired network interface (Windows Vista or
     * greater).
     *
     * @param ifindex System index for network interface.
     */
    static MIB_IF_ROW2* get_if_detail2(DWORD ifindex);
    #endif
    /** Get network interface information for all network interfaces.
     *
     * @return Network interfaces information in a linked list.
     */
    static IP_ADAPTER_ADDRESSES* get_ifs_info();
    /** Increases reference counting for current maininfo.
     */
    void alloc_maininfo();
    /** Decreases reference counting for current maininfo.
     */
    void free_maininfo();

    /// Current native network interface information.
    IP_ADAPTER_ADDRESSES ifinfo;
    /// Current native top network interface information from linked list.
    IP_ADAPTER_ADDRESSES* maininfo;

    /// Store network interface information reference counting for all
    /// win_networkinterface instances.
    static std::map<IP_ADAPTER_ADDRESSES*, int> ifs_references;
};

#endif	/* _WIN_NETWORKINTERFACE_H */
