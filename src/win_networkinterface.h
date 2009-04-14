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

#ifdef WINNT

#ifndef _WIN_NETWORKINTERFACE_H
#define	_WIN_NETWORKINTERFACE_H

#include "networkinterface.h"
#include <iphlpapi.h>

class win_NetworkInterface : NetworkInterface
{
public:
    virtual ~win_NetworkInterface();

    static NetworkInterface* get_all_network_interfaces();
    static int get_interface_count();
    static int test_code();

private:
    win_NetworkInterface(const IP_ADAPTER_ADDRESSES ifinfo);
    win_NetworkInterface(const win_NetworkInterface& orig);
    
    static IP_ADAPTER_ADDRESSES* get_ifs_info();
    
    const IP_ADAPTER_ADDRESSES ifinfo;
};

#endif	/* _WIN_NETWORKINTERFACE_H */

#endif  /* WINNT */
