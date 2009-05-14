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

#include "win_networkinterface.hpp"

#include <iomanip>
#include <glib.h> // To g_utf16_to_utf8(...) function
#include "i18n.hpp"

#ifdef GLIBMM_HAVE_WIDE_STREAM
#define IFMAC_DEFAULTFORMAT std::hex, std::setfill(L'0'), std::setw(2), \
        std::uppercase
#else
#define IFMAC_DEFAULTFORMAT std::hex, std::setfill('0'), std::setw(2), \
        std::uppercase
#endif

std::map<IP_ADAPTER_ADDRESSES*, int> win_NetworkInterface::ifs_references;

win_NetworkInterface::win_NetworkInterface(const IP_ADAPTER_ADDRESSES* ifinfo,
        IP_ADAPTER_ADDRESSES* maininfo)
{
    this->ifinfo = *ifinfo;
    this->maininfo = maininfo; // store the pointer that should be freed
    this->alloc_maininfo();
}

win_NetworkInterface::~win_NetworkInterface()
{
    this->free_maininfo();
}

void win_NetworkInterface::alloc_maininfo()
{
    std::map<IP_ADAPTER_ADDRESSES*, int>::iterator iter;
    iter = ifs_references.find(this->maininfo);
    if (iter == ifs_references.end())
        ifs_references[this->maininfo] = 1; // first reference
    else
        iter->second++; // increases for new reference
}

void win_NetworkInterface::free_maininfo()
{
    std::map<IP_ADAPTER_ADDRESSES*, int>::iterator iter;
    iter = ifs_references.find(maininfo);
    iter->second--; // decreases reference count

    if (iter->second == 0) // last reference
    {
        ifs_references.erase(iter);
        FREE(maininfo);
    }
}

std::vector<NetworkInterface*> win_NetworkInterface::
get_all_network_interfaces()
{
    std::vector<NetworkInterface*> ifs;

    IP_ADAPTER_ADDRESSES* ifsinfo = get_ifs_info();

    // Iterates over linked list to add each item
    IP_ADAPTER_ADDRESSES* curIfsinfo = ifsinfo;
    while (curIfsinfo)
    {
        win_NetworkInterface* currIf =
                new win_NetworkInterface(curIfsinfo, ifsinfo);
        ifs.push_back(currIf);
        curIfsinfo = curIfsinfo->Next;
    }

    return ifs;
}

uint64_t win_NetworkInterface::get_bytes_received()
{
    uint64_t inOctets;

    // FIXME: throw error if interface status changes.
    #if (WINVER >= 0x0600)
    MIB_IF_ROW2* ifrow2 = get_if_detail2(this->ifinfo.IfIndex);
    inOctets = ifrow2->InOctets;
    FREE(ifrow2);
    #else
    MIB_IFROW* ifrow = get_if_detail(this->ifinfo.IfIndex);
    inOctets = ifrow->dwInOctets;
    FREE(ifrow);
    #endif

    return inOctets;
}

uint64_t win_NetworkInterface::get_bytes_sent()
{
    uint64_t outOctets;

    // FIXME: throw error if interface status changes.
    #if (WINVER >= 0x0600)
    MIB_IF_ROW2* ifrow2 = get_if_detail2(this->ifinfo.IfIndex);
    outOctets = ifrow2->OutOctets;
    FREE(ifrow2);
    #else
    MIB_IFROW* ifrow = get_if_detail(this->ifinfo.IfIndex);
    outOctets = ifrow->dwOutOctets;
    FREE(ifrow);
    #endif

    return outOctets;
}

MIB_IFROW* win_NetworkInterface::get_if_detail(DWORD ifindex)
{
    MIB_IFROW* ifrow = NULL;
    ifrow = (MIB_IFROW*)MALLOC(sizeof(MIB_IFROW));
    memset(ifrow, 0, sizeof(MIB_IFROW));

    ifrow->dwIndex = ifindex;
    DWORD retval = GetIfEntry(ifrow);
    if (retval != NO_ERROR)
    {
        throw COMPOSE(_("GetIfEntry failed for index %1 with error: %2"),
                ifindex, retval);
    }

    return ifrow;
}

#if (WINVER >= 0x0600)
MIB_IF_ROW2* win_NetworkInterface::get_if_detail2(ULONG ifindex)
{
    MIB_IF_ROW2* ifrow2 = NULL;
    ifrow2 = (MIB_IF_ROW2*)MALLOC(sizeof(MIB_IF_ROW2));
    memset(ifrow2, 0, sizeof(MIB_IF_ROW2));

    ifrow2->InterfaceIndex = ifindex;
    DWORD retval = GetIfEntry2(ifrow2);
    if (retval != NO_ERROR)
    {
        throw COMPOSE(_("GetIfEntry2 failed for index %1 with error: %2"),
                ifindex, retval);
    }

    return ifrow2;
}
#endif

IP_ADAPTER_ADDRESSES* win_NetworkInterface::get_ifs_info()
{
    DWORD dwRetVal = 0;

    ULONG flags = GAA_FLAG_INCLUDE_PREFIX;
    ULONG family = AF_INET; // Only IPv4
    LPVOID lpMsgBuf = NULL;
    IP_ADAPTER_ADDRESSES* pAddresses = NULL;
    ULONG outBufLen = sizeof (IP_ADAPTER_ADDRESSES);

    pAddresses = (IP_ADAPTER_ADDRESSES*) MALLOC(outBufLen);
    if (pAddresses == NULL)
        throw _("Memory allocation failed for IP_ADAPTER_ADDRESSES struct");

    dwRetVal = GetAdaptersAddresses(family, flags, lpMsgBuf,
            pAddresses, &outBufLen);

    // If size of pAddresses is insuficient, gets needed size returned in
    // outBufLen
    if (dwRetVal == ERROR_BUFFER_OVERFLOW)
    {
        FREE(pAddresses);
        pAddresses = (IP_ADAPTER_ADDRESSES*) MALLOC(outBufLen);

        if (pAddresses == NULL)
            throw _("Memory allocation failed for IP_ADAPTER_ADDRESSES struct");

        // Tries again with correct size
        dwRetVal = GetAdaptersAddresses(family, flags, lpMsgBuf,
                pAddresses, &outBufLen);
    }

    if (dwRetVal != NO_ERROR)
        throw _("GetAdapterAddresses failed");

    return pAddresses;
}

int win_NetworkInterface::get_interface_count()
{
    IP_ADAPTER_ADDRESSES* ifsinfo = get_ifs_info();

    // Interates over linked list to count
    int count = 0;
    IP_ADAPTER_ADDRESSES* curIfsinfo = ifsinfo;
    while (curIfsinfo)
    {
        count++;
        curIfsinfo = curIfsinfo->Next;
    }

    FREE(ifsinfo);
    return count;
}

Glib::ustring win_NetworkInterface::get_internal_name()
{
    Glib::ustring iname(this->ifinfo.AdapterName);
    return iname;
}

Glib::ustring win_NetworkInterface::get_name()
{
    gchar* pt_name = g_utf16_to_utf8(
            (gunichar2*) this->ifinfo.FriendlyName, -1, NULL, NULL, NULL);
    Glib::ustring name(pt_name);
    g_free(pt_name);
    return name;
}

Glib::ustring win_NetworkInterface::get_physical_address()
{
    if (this->ifinfo.PhysicalAddressLength != 6)
        return "";

    Glib::ustring paddr(COMPOSE("%1:%2:%3:%4:%5:%6",
            FORMAT(IFMAC_DEFAULTFORMAT, (int) ifinfo.PhysicalAddress[0]),
            FORMAT(IFMAC_DEFAULTFORMAT, (int) ifinfo.PhysicalAddress[1]),
            FORMAT(IFMAC_DEFAULTFORMAT, (int) ifinfo.PhysicalAddress[2]),
            FORMAT(IFMAC_DEFAULTFORMAT, (int) ifinfo.PhysicalAddress[3]),
            FORMAT(IFMAC_DEFAULTFORMAT, (int) ifinfo.PhysicalAddress[4]),
            FORMAT(IFMAC_DEFAULTFORMAT, (int) ifinfo.PhysicalAddress[5])));
    return paddr;
}

/*
 * MIB_IFROW.bDescr get interface description as:
 * - Atheros L2 Fast Ethernet 10/100Base-T Controller
 * - Software Loopback Interface 1
 */
