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

#include "win_networkinterface.h"

#include <memory>
#include <glib.h>   // To g_utf16_to_utf8(...) function
#include "i18n.h"

// Test
#include <iostream>

win_NetworkInterface::win_NetworkInterface(const IP_ADAPTER_ADDRESSES* ifinfo)
{
    this->ifinfo = *ifinfo;
}

win_NetworkInterface::win_NetworkInterface(const win_NetworkInterface& orig)
{
    this->ifinfo = orig.ifinfo;
}

win_NetworkInterface::~win_NetworkInterface()
{
}

std::vector<NetworkInterface*> win_NetworkInterface::get_all_network_interfaces()
{
    std::vector<NetworkInterface*> ifs;

    IP_ADAPTER_ADDRESSES* ifsinfo = get_ifs_info();

    IP_ADAPTER_ADDRESSES* curIfsinfo = ifsinfo;
    while (curIfsinfo)
    {
        win_NetworkInterface* currIf = new win_NetworkInterface(curIfsinfo);
        ifs.push_back(currIf);
        curIfsinfo = curIfsinfo->Next;
    }

    // FIXME: remaining references will point to garbage
    FREE(ifsinfo);
    return ifs;
}

uint64_t win_NetworkInterface::get_bytes_received()
{
    MIB_IFROW ifrow = get_if_detail(this->ifinfo.IfIndex);
    return ifrow.dwInOctets;
}

uint64_t win_NetworkInterface::get_bytes_sent()
{
    MIB_IFROW ifrow = get_if_detail(this->ifinfo.IfIndex);
    return ifrow.dwOutOctets;
}

MIB_IFROW win_NetworkInterface::get_if_detail(DWORD ifindex)
{
    MIB_IFROW ifrow;
    ifrow.dwIndex = ifindex;
    DWORD retval = GetIfEntry(&ifrow);
    if (retval != NO_ERROR)
    {
        throw compose(_("GetIfEntry failed for index %1 with error: %2"),
                ifindex, retval);
    }

    return ifrow;
}

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

    // Gets needed size to alloc pAddresses, writes size to outBufLen.
    if (GetAdaptersAddresses(family, flags, lpMsgBuf, pAddresses,
            &outBufLen) == ERROR_BUFFER_OVERFLOW)
    {
        FREE(pAddresses);
        pAddresses = (IP_ADAPTER_ADDRESSES*) MALLOC(outBufLen);

        if (pAddresses == NULL)
            throw _("Memory allocation failed for IP_ADAPTER_ADDRESSES struct");
    }

    dwRetVal = GetAdaptersAddresses(family, flags, lpMsgBuf,
            pAddresses, &outBufLen);
    if (dwRetVal != NO_ERROR)
        throw _("GetAdapterAddresses failed");

    return pAddresses;
}

int win_NetworkInterface::get_interface_count()
{
    IP_ADAPTER_ADDRESSES* ifsinfo = get_ifs_info();

    // interates over linked list to count.
    int count = 0;
    while (ifsinfo)
    {
        count++;
        ifsinfo = ifsinfo->Next;
    }

    FREE(ifsinfo);
    return count;
}

Glib::ustring win_NetworkInterface::get_name()
{
    gchar* pt_name = g_utf16_to_utf8(
            (gunichar2*) this->ifinfo.FriendlyName, -1, NULL, NULL, NULL);
    Glib::ustring name(pt_name);
    g_free(pt_name);
    return name;
}

int win_NetworkInterface::test_code()
{
    DWORD dwRetVal = 0;

    ULONG flags = GAA_FLAG_INCLUDE_PREFIX;
    ULONG family = AF_INET;
    LPVOID lpMsgBuf = NULL;
    PIP_ADAPTER_ADDRESSES pAddresses = NULL;
    ULONG outBufLen = sizeof (IP_ADAPTER_ADDRESSES);

    pAddresses = (IP_ADAPTER_ADDRESSES*) MALLOC(outBufLen);
    if (pAddresses == NULL)
        throw "Memory allocation failed for IP_ADAPTER_ADDRESSES struct";

    // Gets needed size to alloc pAddresses, writes size to outBufLen.
    if (GetAdaptersAddresses(family, flags, lpMsgBuf, pAddresses,
            &outBufLen) == ERROR_BUFFER_OVERFLOW)
    {
        FREE(pAddresses);
        pAddresses = (IP_ADAPTER_ADDRESSES*) MALLOC(outBufLen);

        if (pAddresses == NULL)
            throw "Memory allocation failed for IP_ADAPTER_ADDRESSES struct";
    }

    dwRetVal = GetAdaptersAddresses(family, flags, lpMsgBuf,
            pAddresses, &outBufLen);
    if (dwRetVal != NO_ERROR)
        throw "GetAdapterAddresses failed";

    PIP_ADAPTER_ADDRESSES pCurAddresses = pAddresses;
    while (pCurAddresses)
    {
        MIB_IFROW* pIfRow = (MIB_IFROW*) MALLOC(sizeof (MIB_IFROW));
        if (pIfRow == NULL)
        {
            FREE(pAddresses);
            throw "Error allocating memory";
        }
        pIfRow->dwIndex = pCurAddresses->IfIndex;

        dwRetVal = GetIfEntry(pIfRow);
        if (dwRetVal != NO_ERROR)
        {
            FREE(pAddresses);
            FREE(pIfRow);
            throw "GetIfEntry failed for index %index with error: %num";
        }

        std::cout << "IfIndex: " << pCurAddresses->IfIndex << std::endl;
        std::wcout << "FriendlyName: " << pCurAddresses->FriendlyName << std::endl;

        std::cout << "Index: " << pIfRow->dwIndex << std::endl;
        std::cout << "Interface name: ";
        if (pIfRow->wszName != NULL)
            std::wcout << pIfRow->wszName;
        std::cout << std::endl;
        std::cout << "Description: " << pIfRow->bDescr << std::endl;
        std::cout << "Bytes in: " << pIfRow->dwInOctets << std::endl;
        std::cout << "Bytes out: " << pIfRow->dwOutOctets << std::endl;

        std::cout << std::endl <<
                "============================================================================" <<
                std::endl;

        pCurAddresses = pCurAddresses->Next;
        FREE(pIfRow);
    }

    FREE(pAddresses);
}
