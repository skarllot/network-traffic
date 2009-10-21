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

#include "linux_networkinterface.hpp"

#include <fstream>
#include <stdlib.h>
#include <vector>

/* Test
#include <iostream>
#include <sys/socket.h>
#include <netdb.h>
#include <dirent.h>
//#include <arpa/inet.h> */

// sysfs paths
#define SYSFS_NET_CLASS "/sys/class/net"
#define SYSFS_IFADDRESS SYSFS_NET_CLASS "/%1/address"
#define SYSFS_IFRX SYSFS_NET_CLASS "/%1/statistics/rx_bytes"
#define SYSFS_IFTX SYSFS_NET_CLASS "/%1/statistics/tx_bytes"


std::map<ifaddrs*, int> linux_NetworkInterface::ifs_references;

linux_NetworkInterface::linux_NetworkInterface(const ifaddrs* ifinfo,
        ifaddrs* firstinfo)
{
    this->ifinfo.push_back(*ifinfo);
    this->firstinfo = firstinfo; // pointer that must be freed

    std::map<ifaddrs*, int>::iterator iter;
    iter = ifs_references.find(firstinfo);
    if (iter == ifs_references.end())
        ifs_references[firstinfo] = 1; // first reference
    else
        iter->second++; // increases reference counting
}

linux_NetworkInterface::~linux_NetworkInterface()
{
    std::map<ifaddrs*, int>::iterator iter;
    iter = ifs_references.find(firstinfo);
    iter->second--; // decreases reference count

    if (iter->second == 0) // last reference
    {
        ifs_references.erase(iter);
        freeifaddrs(firstinfo);
    }
}

void linux_NetworkInterface::add_info(const ifaddrs* ifinfo)
{
    this->ifinfo.push_back(*ifinfo);
}

std::vector<NetworkInterface*> linux_NetworkInterface::get_all_network_interfaces()
{
    std::vector<NetworkInterface*> ifs;
    std::map<std::string, linux_NetworkInterface*> ifsmap;
    std::map<std::string, linux_NetworkInterface*>::iterator it_ifsmap;

    ifaddrs* ifsinfo = NULL;
    getifaddrs(&ifsinfo);

    // Iterates over linked list to add each item
    ifaddrs* curIfsinfo = ifsinfo;
    while (curIfsinfo)
    {
        it_ifsmap = ifsmap.find(curIfsinfo->ifa_name);
        linux_NetworkInterface* currnetif;

        if (it_ifsmap == ifsmap.end()) // If this interface is not added
        {
            currnetif = new linux_NetworkInterface(curIfsinfo, ifsinfo);
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

uint64_t linux_NetworkInterface::get_bytes_received()
{
    // TODO: test if_data struct at <net/if.h>
    std::string rbytes = this->read_sysfs(SYSFS_IFRX);
    return strtoull(rbytes.c_str(), NULL, 0);
}

uint64_t linux_NetworkInterface::get_bytes_sent()
{
    std::string tbytes = this->read_sysfs(SYSFS_IFTX);
    return strtoull(tbytes.c_str(), NULL, 0);
}

int linux_NetworkInterface::get_interface_count()
{
    ifaddrs* ifsinfo = NULL;
    getifaddrs(&ifsinfo);

    // Interates over linked list to count
    int count = 0;
    ifaddrs* curIfsinfo = ifsinfo;
    while (curIfsinfo)
    {
        count++;
        curIfsinfo = curIfsinfo->ifa_next;
    }

    freeifaddrs(ifsinfo);
    return count;
}

Glib::ustring linux_NetworkInterface::get_internal_name()
{
    return this->get_name();
}

Glib::ustring linux_NetworkInterface::get_name()
{
    Glib::ustring name(this->ifinfo[0].ifa_name);
    return name;
}

Glib::ustring linux_NetworkInterface::get_physical_address()
{
    std::string paddr = this->read_sysfs(SYSFS_IFADDRESS);
    return paddr;
}

std::string linux_NetworkInterface::read_sysfs(std::string path)
{
    std::string filename = Glib::ustring::compose(path,
            this->ifinfo[0].ifa_name);

    std::ifstream fs(filename.c_str());
    std::string strvalue;
    std::getline(fs, strvalue);
    fs.close();

    return strvalue;
}

/*
 *
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
 */
