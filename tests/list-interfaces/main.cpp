#include <iostream>
#include <gtkmm.h>
#include "networkinterface.hpp"

#define HEAVY_SEP "================================================================================"
#define LIGHT_SEP "--------------------------------------------------------------------------------"
#define COMPOSE Glib::ustring::compose

typedef std::vector<NetworkInterface*> NetworkInterfaceVector;
typedef NetworkInterfaceVector::iterator NetworkInterfaceIter;

int main(int argc, char** argv)
{
    NetworkInterfaceVector netIfs =
        NetworkInterface::get_all_network_interfaces();

    std::cout << HEAVY_SEP << std::endl;
    std::cout << COMPOSE("INTERFACE LIST (%1 found)", netIfs.size())
        << std::endl;
    std::cout << HEAVY_SEP << std::endl << std::endl;

    NetworkInterfaceIter iter;
    for (iter = netIfs.begin(); iter != netIfs.end(); iter++) {
        std::cout << COMPOSE("Name            : %1",
            (**iter).get_name()) << std::endl;
        std::cout << COMPOSE("Internal name   : %1",
            (**iter).get_internal_name()) << std::endl;
        std::cout << COMPOSE("Physical address: %1",
            (**iter).get_physical_address()) << std::endl;
        std::cout << COMPOSE("Bytes received  : %1",
            (**iter).get_bytes_received()) << std::endl;
        std::cout << COMPOSE("Bytes sent      : %1",
            (**iter).get_bytes_sent()) << std::endl;
        std::cout << LIGHT_SEP << std::endl << std::endl;
    }

    return 0;
}
