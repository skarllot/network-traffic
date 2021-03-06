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

#ifdef __linux__

#include "linux_networkinterface.hpp"

#include <fstream>
#include <stdlib.h>
#include <vector>
#include <sys/types.h>
#include <dirent.h>

// sysfs paths
#define SYSFS_NET_CLASS "/sys/class/net"
#define SYSFS_IFADDRESS SYSFS_NET_CLASS "/%1/address"
#define SYSFS_IFRX      SYSFS_NET_CLASS "/%1/statistics/rx_bytes"
#define SYSFS_IFTX      SYSFS_NET_CLASS "/%1/statistics/tx_bytes"


linux_NetworkInterface::linux_NetworkInterface(const char* ifname)
{
    this->ifname = ifname;
}

linux_NetworkInterface::~linux_NetworkInterface()
{
}

std::vector<NetworkInterface*> linux_NetworkInterface::
get_all_network_interfaces()
{
    std::vector<NetworkInterface*> if_list;
    DIR* dirp;

    if (dirp = opendir(SYSFS_NET_CLASS))
    {
        struct dirent* entry;
        
        readdir(dirp); // skip .
        readdir(dirp); // skip ..
        while (entry = readdir(dirp))
        {
            linux_NetworkInterface* if_item =
                    new linux_NetworkInterface(entry->d_name);
            if_list.push_back(if_item);
        }
        closedir(dirp);
    }

    return if_list;
}

uint64_t linux_NetworkInterface::get_bytes_received() const
{
    std::string rbytes = this->read_sysfs(SYSFS_IFRX);
    return strtoull(rbytes.c_str(), NULL, 0);
}

uint64_t linux_NetworkInterface::get_bytes_sent() const
{
    std::string tbytes = this->read_sysfs(SYSFS_IFTX);
    return strtoull(tbytes.c_str(), NULL, 0);
}

int linux_NetworkInterface::get_interface_count()
{
    DIR* dirp;
    int count = 0;

    if (dirp = opendir(SYSFS_NET_CLASS))
    {
        struct dirent* entry;

        readdir(dirp); // skip .
        readdir(dirp); // skip ..
        while (entry = readdir(dirp))
            count++;
        closedir(dirp);
    }

    return count;
}

Glib::ustring linux_NetworkInterface::get_internal_name() const
{
    Glib::ustring name(this->ifname);
    return name;
}

Glib::ustring linux_NetworkInterface::get_name() const
{
    return this->get_internal_name();
}

NetworkInterface* linux_NetworkInterface::
get_network_interface(Glib::ustring ifname)
{
    NetworkInterface* ret = NULL;
    
    if (is_valid(ifname))
        ret = new linux_NetworkInterface(ifname.c_str());

    return ret;
}

Glib::ustring linux_NetworkInterface::get_physical_address() const
{
    std::string paddr = this->read_sysfs(SYSFS_IFADDRESS);
    return paddr;
}

bool linux_NetworkInterface::is_valid() const
{
    return is_valid(this->ifname);
}

bool linux_NetworkInterface::is_valid(std::string ifname)
{
    DIR* dirp;
    std::string ifpath = SYSFS_NET_CLASS "/";
    ifpath += ifname;
    
    bool ret = opendir(ifpath.c_str()) != NULL;
    closedir(dirp);
    return ret;
}

std::string linux_NetworkInterface::read_sysfs(std::string path) const
{
    std::string filename = Glib::ustring::compose(path, this->ifname);

    std::ifstream fs(filename.c_str());
    std::string strvalue;
    std::getline(fs, strvalue);
    fs.close();

    return strvalue;
}

#endif
