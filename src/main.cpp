/* 
 * File:   main.cpp
 * Author: fabricio
 *
 * Created on 25 de Março de 2009, 08:41
 */

#include "config.h"

#include <stdlib.h>
#include <iostream>
#include <string>
#if WINNT
#ifndef WINVER
#define WINVER 0x0502   // Windows Server 2003 with SP1, Windows XP with SP2
// See http://msdn.microsoft.com/en-us/library/aa383745(VS.85).aspx
#endif /* WINVER */

#include <windows.h>
#include <iphlpapi.h>

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))
#endif

/*
 * 
 */
int main(int argc, char** argv)
{
#if WINNT
    // Verify Windows version
    // http://msdn.microsoft.com/en-gb/library/ms724833(VS.85).aspx
    OSVERSIONINFOEX os_version;
    ZeroMemory(&os_version, sizeof (OSVERSIONINFOEX));
    os_version.dwOSVersionInfoSize = sizeof (OSVERSIONINFOEX);
    GetVersionEx((OSVERSIONINFO*) & os_version);

    if (os_version.dwMajorVersion < 5 ||
            (os_version.dwMajorVersion == 5 && os_version.dwMinorVersion < 1) ||
            (os_version.dwMajorVersion == 5 && os_version.dwMinorVersion == 1 &&
            os_version.wServicePackMajor < 2) ||
            (os_version.dwMajorVersion = 5 && os_version.dwMinorVersion == 2 &&
            os_version.wServicePackMajor < 1))
    {
        std::cout << "Windows version not supported, requires at least Windows XP with SP2"
                << std::endl;
        return (EXIT_FAILURE);
    }
    // ----------------------

    DWORD dwSize = 0;
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
    }

    FREE(pAddresses);

    // ---

    MIB_IFTABLE* pIfTable;
    MIB_IFROW* pIfRow;

    pIfTable = (MIB_IFTABLE*) MALLOC(sizeof (MIB_IFTABLE));
    if (pIfTable == NULL)
        throw "Error allocating memory needed to call GetIfTable";

    dwSize = sizeof (MIB_IFTABLE);
    if (GetIfTable(pIfTable, &dwSize, FALSE) == ERROR_INSUFFICIENT_BUFFER)
    {
        FREE(pIfTable);
        pIfTable = (MIB_IFTABLE*) MALLOC(dwSize);

        if (pIfTable == NULL)
            throw "Error allocating memory";
    }

    dwRetVal = GetIfTable(pIfTable, &dwSize, FALSE);
    if (dwRetVal != NO_ERROR)
        throw "GetIfTable failed with error: " + dwRetVal;

    if (pIfTable->dwNumEntries == 0)
    {
        FREE(pIfTable);
        std::cout << "No interfaces found." << std::endl;
        return (EXIT_FAILURE);
    }

    std::cout << "Num entries: " << pIfTable->dwNumEntries << std::endl;

    pIfRow = (MIB_IFROW*) MALLOC(sizeof (MIB_IFROW));
    if (pIfRow == NULL)
    {
        FREE(pIfTable);
        throw "Error allocating memory";
    }

    for (int i = 0; i < (int) pIfTable->dwNumEntries; i++)
    {
        pIfRow->dwIndex = pIfTable->table[i].dwIndex;

        dwRetVal = GetIfEntry(pIfRow);
        if (dwRetVal != NO_ERROR)
        {
            FREE(pIfTable);
            FREE(pIfRow);
            throw "GetIfEntry failed for index %index with error: %num";
        }

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
    }

    FREE(pIfRow);
    FREE(pIfTable);
#endif

    return (EXIT_SUCCESS);
}

