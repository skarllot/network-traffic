/* 
 * File:   networkinfo.h
 * Author: fabricio
 *
 * Created on 26 de Março de 2009, 16:34
 */

#ifndef _NETWORKINFO_H
#define	_NETWORKINFO_H

#include "../config.h"

#include <string>
#include <vector>

struct Interface
{
    int index;
    std::wstring name;
    long long inBytes;
    long long outBytes;
};

class NetworkInfo
{
public:
    NetworkInfo();
    NetworkInfo(const NetworkInfo& orig);
    virtual ~NetworkInfo();

    int get_interface_count();

private:
    void load_interfaces_info();

    std::vector<Interface> interfaces;
#if WINNT
    int ifIndex;
#endif
};

#endif	/* _NETWORKINFO_H */

