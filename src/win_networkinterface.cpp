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

#include <glibmm/i18n.h>
#include "win_networkinterface.h"
#include "networkinterface.h"

// Test
#include <iostream>

#include <windows.h>
#include <iphlpapi.h>

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))

IP_ADAPTER_ADDRESSES* win_NetworkInterface::ifinfocache = NULL;

win_NetworkInterface::win_NetworkInterface(const IP_ADAPTER_ADDRESSES ifinfo)
{
}

win_NetworkInterface::win_NetworkInterface(const win_NetworkInterface& orig)
{
}

win_NetworkInterface::~win_NetworkInterface()
{
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

NetworkInterface* win_NetworkInterface::get_all_network_interfaces()
{
    IP_ADAPTER_ADDRESSES* ifsinfo = get_ifs_info();
    FREE(ifsinfo);
    return 0;
}

int win_NetworkInterface::get_interface_count()
{
    IP_ADAPTER_ADDRESSES* ifsinfo = get_ifs_info();

    int count = 0;
    while (ifsinfo)
    {
        count++;
        ifsinfo = ifsinfo->Next;
    }

    FREE(ifsinfo);
    return count;
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

#endif
