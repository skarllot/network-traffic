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

#include "nix_networkinterface.h"

#include <stdlib.h>
#include <string.h>
#include <vector>

// Test
#include <iostream>
#include <sys/socket.h>
#include <netdb.h>
#include <dirent.h>
#include <fstream>
//#include <arpa/inet.h>

#define NET_STATISTICS_PATH "/sys/class/net/"
#define NET_STATISTICS_RX_SUFFIX "/statistics/rx_bytes"
#define NET_STATISTICS_TX_SUFFIX "/statistics/tx_bytes"

std::map<ifaddrs*, int> nix_NetworkInterface::ifs_references;

nix_NetworkInterface::nix_NetworkInterface(const ifaddrs* ifinfo,
        ifaddrs* maininfo)
{
    this->ifinfo.push_back(*ifinfo);
    this->maininfo = maininfo; // store the pointer that should be freed

    std::map<ifaddrs*, int>::iterator iter;
    iter = ifs_references.find(maininfo);
    if (iter == ifs_references.end())
        ifs_references[maininfo] = 1; // first reference
    else
        iter->second++; // increases for new reference
}

nix_NetworkInterface::~nix_NetworkInterface()
{
    std::map<ifaddrs*, int>::iterator iter;
    iter = ifs_references.find(maininfo);
    iter->second--; // decreases reference count

    if (iter->second == 0) // last reference
    {
        ifs_references.erase(iter);
        freeifaddrs(maininfo);
    }
}

/** Add info for same interface but different protocol (e.g. IPv6)
 */
void nix_NetworkInterface::add_info(const ifaddrs* ifinfo)
{
    this->ifinfo.push_back(*ifinfo);
}

std::vector<NetworkInterface*> nix_NetworkInterface::get_all_network_interfaces()
{
    std::vector<NetworkInterface*> ifs;
    std::map<std::string, nix_NetworkInterface*> ifsmap;
    std::map<std::string, nix_NetworkInterface*>::iterator it_ifsmap;

    ifaddrs* ifsinfo = NULL;
    getifaddrs(&ifsinfo);

    // Iterates over linked list to add each item
    ifaddrs* curIfsinfo = ifsinfo;
    while (curIfsinfo)
    {
        it_ifsmap = ifsmap.find(curIfsinfo->ifa_name);
        nix_NetworkInterface* currnetif;

        if (it_ifsmap == ifsmap.end()) // If this interface is not added
        {
            currnetif = new nix_NetworkInterface(curIfsinfo, ifsinfo);
            ifs.push_back(currnetif);
            ifsmap[curIfsinfo->ifa_name] = currnetif;
        }
        else // If this interface is already added
        {
            currnetif = it_ifsmap->second;
            currnetif->add_info(curIfsinfo);
        }

        curIfsinfo = curIfsinfo->ifa_next;
    }

    // Will be free on destructor.
    //freeifaddrs(ifsinfo);
    return ifs;
}

uint64_t nix_NetworkInterface::get_bytes_received()
{
    // Reads from pseudo file
    std::string filename(NET_STATISTICS_PATH);
    filename += this->ifinfo[0].ifa_name;
    filename += NET_STATISTICS_RX_SUFFIX;

    std::ifstream fs(filename.c_str());
    std::string rbytes;
    getline(fs, rbytes);
    fs.close();

    return strtoull(rbytes.c_str(), NULL, 0);
}

uint64_t nix_NetworkInterface::get_bytes_sent()
{
    // Reads from pseudo file
    std::string filename(NET_STATISTICS_PATH);
    filename += this->ifinfo[0].ifa_name;
    filename += NET_STATISTICS_TX_SUFFIX;

    std::ifstream fs(filename.c_str());
    std::string tbytes;
    getline(fs, tbytes);
    fs.close();

    return strtoull(tbytes.c_str(), NULL, 0);
}

Glib::ustring nix_NetworkInterface::get_name()
{
    Glib::ustring name(this->ifinfo[0].ifa_name);
    return name;
}

int nix_NetworkInterface::test_code()
{
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
            memset(name, 0, NI_MAXHOST);
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
}
