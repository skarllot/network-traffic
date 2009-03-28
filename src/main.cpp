/* 
 * File:   main.cpp
 * Author: fabricio
 *
 * Created on 25 de Março de 2009, 08:41
 */

#include "../config.h"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "networkinfo.h"

#if WINNT
#ifndef WINVER
#define WINVER 0x0502   // Windows Server 2003 with SP1, Windows XP with SP2
// See http://msdn.microsoft.com/en-us/library/aa383745(VS.85).aspx
#endif /* WINVER */

#include <windows.h>
#include <iphlpapi.h>

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))
#else
#include <sys/socket.h>
#include <netdb.h>
#include <dirent.h>
#include <ifaddrs.h>
#include <fstream>
//#include <arpa/inet.h>
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

    NetworkInfo netinfo;
    return (EXIT_SUCCESS);

    // WILL DEPRECATE

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
#else
    DIR* dirp;
    struct dirent* entry;

    if (dirp = opendir("/sys/class/net"))
    {
        readdir(dirp); // .
        readdir(dirp); // ..
        while (entry = readdir(dirp))
            std::cout << entry->d_name << std::endl;
        closedir(dirp);
    }

    std::cout << "----------" << std::endl;

    struct ifaddrs* ifs;
    getifaddrs(&ifs);

    struct ifaddrs* curIfs;
    curIfs = ifs;
    while (curIfs)
    {
        std::cout << "Name: " << curIfs->ifa_name << std::endl;
        if (curIfs->ifa_addr)
        {
            char name[NI_MAXHOST];
            getnameinfo(curIfs->ifa_addr, sizeof (sockaddr_storage), name, sizeof (name),
                    NULL, 0, NI_NUMERICHOST);
            std::string strname(name);
            std::cout << "Gen addr: " << strname << " -> " << strname.length() << std::endl;

            // ---

            std::string filename("/sys/class/net/");
            filename.append(curIfs->ifa_name).append("/statistics/rx_bytes");
            std::ifstream fs(filename.c_str());
            std::string rbytes;

            getline(fs, rbytes);
            fs.close();
            std::cout << "R. bytes: " << rbytes << std::endl;

            // ---

            std::string filename2("/sys/class/net/");
            filename2.append(curIfs->ifa_name).append("/statistics/tx_bytes");
            std::ifstream fs2(filename2.c_str());
            std::string tbytes;

            getline(fs2, tbytes);
            fs2.close();
            std::cout << "T. bytes: " << tbytes << std::endl;
        }
        std::cout << "------------------------------------------------------" <<
                std::endl;
        
        curIfs = curIfs->ifa_next;
    }

    freeifaddrs(ifs);
#endif

    return (EXIT_SUCCESS);
}

