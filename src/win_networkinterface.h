/* 
 * File:   win_networkinterface.h
 * Author: fabricio
 *
 * Created on 29 de Março de 2009, 18:42
 */

#ifdef WINNT

#ifndef _WIN_NETWORKINTERFACE_H
#define	_WIN_NETWORKINTERFACE_H

#include "networkinterface.h"


class win_NetworkInterface
{
public:
    win_NetworkInterface();
    win_NetworkInterface(const win_NetworkInterface& orig);
    virtual ~win_NetworkInterface();

    static NetworkInterface* get_all_network_interfaces();
    static int test_code();
private:

};

#endif	/* _WIN_NETWORKINTERFACE_H */

#endif
