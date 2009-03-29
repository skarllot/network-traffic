/* 
 * File:   networkinfo.cpp
 * Author: fabricio
 * 
 * Created on March 26, 2009, 16:34
 */

#include "networkinfo.h"
#include <iostream>

#if WINNT
#ifndef WINVER
#define WINVER 0x0502   // Windows Server 2003 with SP1, Windows XP with SP2
// See http://msdn.microsoft.com/en-us/library/aa383745(VS.85).aspx
#endif /* WINVER */

#include <windows.h>
#include <iphlpapi.h>
#include <string>

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))
#endif

NetworkInfo::NetworkInfo()
{
    std::cout << "Constructor" << std::endl;
    this->load_interfaces_info();
}

NetworkInfo::NetworkInfo(const NetworkInfo& orig)
{
}

NetworkInfo::~NetworkInfo()
{
}

int NetworkInfo::get_interface_count()
{
    return 0;
}

void NetworkInfo::load_interfaces_info()
{
#if WINNT
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

        Interface _if;
        _if.index = (int)pIfRow->dwIndex;
        _if.name = std::wstring(pIfRow->wszName);
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

        this->interfaces.push_back(_if);
    }

    std::cout << "Test index: " << this->interfaces.at(0).index << std::endl;
    std::wcout << "Test name: " << this->interfaces.at(0).name << std::endl;
    std::cout << "Test index: " << this->interfaces.at(1).index << std::endl;
    std::wcout << "Test name: " << this->interfaces.at(1).name << std::endl;
    FREE(pAddresses);
#endif
}
