#ifndef _IPHLPAPI2_H
#define	_IPHLPAPI2_H

#include <iphlpapi.h>

#ifdef __cplusplus
extern "C" {
#endif
#define IF_MAX_STRING_SIZE 256
#define IF_MAX_PHYS_ADDRESS_LENGTH 32

#define IF_TYPE_OTHER 1
#define IF_TYPE_ETHERNET_CSMACD 6
#define IF_TYPE_ISO88025_TOKENRING 9
#define IF_TYPE_PPP 23
#define IF_TYPE_SOFTWARE_LOOPBACK 24
#define IF_TYPE_ATM 37
#define IF_TYPE_IEEE80211 71
#define IF_TYPE_TUNNEL 131
#define IF_TYPE_IEEE1394 144

typedef ULONG IFTYPE;
typedef ULONG NET_IFINDEX, *PNET_IFINDEX;
typedef GUID NET_IF_NETWORK_GUID, *PNET_IF_NETWORK_GUID;
typedef enum {
    NET_IF_ACCESS_LOOPBACK = 1,
    NET_IF_ACCESS_BROADCAST = 2,
    NET_IF_ACCESS_POINT_TO_POINT = 3,
    NET_IF_ACCESS_POINT_TO_MULTI_POINT = 4,
    NET_IF_ACCESS_MAXIMUM = 5
} NET_IF_ACCESS_TYPE, *PNET_IF_ACCESS_TYPE;
typedef enum {
    NET_IF_ADMIN_STATUS_UP = 1,
    NET_IF_ADMIN_STATUS_DOWN = 2,
    NET_IF_ADMIN_STATUS_TESTING = 3
} NET_IF_ADMIN_STATUS, *PNET_IF_ADMIN_STATUS;
typedef enum {
   NET_IF_CONNECTION_DEDICATED = 1,
   NET_IF_CONNECTION_PASSIVE = 2,
   NET_IF_CONNECTION_DEMAND = 3,
   NET_IF_CONNECTION_MAXIMUM = 4
} NET_IF_CONNECTION_TYPE, *PNET_IF_CONNECTION_TYPE;
typedef enum {
    NET_IF_DIRECTION_SENDRECEIVE = 0,
    NET_IF_DIRECTION_SENDONLY = 1,
    NET_IF_DIRECTION_RECEIVEONLY = 2,
    NET_IF_DIRECTION_MAXIMUM = 3
} NET_IF_DIRECTION_TYPE, *PNET_IF_DIRECTION_TYPE;
typedef enum {
    MediaConnectStateUnknown = 0,
    MediaConnectStateConnected = 1,
    MediaConnectStateDisconnected = 2
} NET_IF_MEDIA_CONNECT_STATE, *PNET_IF_MEDIA_CONNECT_STATE;
typedef enum {
    NdisMedium802_3 = 0,
    NdisMedium802_5 = 1,
    NdisMediumFddi = 2,
    NdisMediumWan = 3,
    NdisMediumLocalTalk = 4,
    NdisMediumDix = 5,
    NdisMediumArcnetRaw = 6,
    NdisMediumArcnet878_2 = 7,
    NdisMediumAtm = 8,
    NdisMediumWirelessWan = 9,
    NdisMediumIrda = 10,
    NdisMediumBpc = 11,
    NdisMediumCoWan = 12,
    NdisMedium1394 = 13,
    NdisMediumInfiniBand = 14,
    NdisMediumTunnel = 15,
    NdisMediumNative802_11 = 16,
    NdisMediumLoopback = 17
} NDIS_MEDIUM, *PNDIS_MEDIUM;
typedef enum {
    NdisPhysicalMediumUnspecified = 0,
    NdisPhysicalMediumWirelessLan = 1,
    NdisPhysicalMediumCableModem = 2,
    NdisPhysicalMediumPhoneLine = 3,
    NdisPhysicalMediumPowerLine = 4,
    NdisPhysicalMediumDSL = 5,
    NdisPhysicalMediumFibreChannel = 6,
    NdisPhysicalMedium1394 = 7,
    NdisPhysicalMediumWirelessWan = 8,
    NdisPhysicalMediumNative802_11 = 9,
    NdisPhysicalMediumBluetooth = 10,
    NdisPhysicalMediumInfiniband = 11,
    NdisPhysicalMediumWiMax = 12,
    NdisPhysicalMediumUWB = 13,
    NdisPhysicalMedium802_3 = 14,
    NdisPhysicalMedium802_5 = 15,
    NdisPhysicalMediumIrda = 16,
    NdisPhysicalMediumWiredWAN = 17,
    NdisPhysicalMediumWiredCoWan = 18,
    NdisPhysicalMediumOther = 19
} NDIS_PHYSICAL_MEDIUM, *PNDIS_PHYSICAL_MEDIUM;
typedef enum {
    TUNNEL_TYPE_NONE = 0,
    TUNNEL_TYPE_OTHER = 1,
    TUNNEL_TYPE_DIRECT = 2,
    TUNNEL_TYPE_6TO4 = 11,
    TUNNEL_TYPE_ISATAP = 13,
    TUNNEL_TYPE_TEREDO = 14,
} TUNNEL_TYPE, *PTUNNEL_TYPE;
typedef union {
    ULONG64 Value;
    struct {
        ULONG64 Reserved:24;
        ULONG64 NetLuidIndex:24;
        ULONG64 IfType:16;
    } Info;
} NET_LUID, *PNET_LUID;
typedef struct {
    NET_LUID InterfaceLuid;
    NET_IFINDEX InterfaceIndex;
    GUID InterfaceGuid;
    WCHAR Alias[IF_MAX_STRING_SIZE + 1];
    WCHAR Description[IF_MAX_STRING_SIZE + 1];
    ULONG PhysicalAddressLength;
    UCHAR PhysicalAddress[IF_MAX_PHYS_ADDRESS_LENGTH];
    UCHAR PermanentPhysicalAddress[IF_MAX_PHYS_ADDRESS_LENGTH];
    ULONG Mtu;
    IFTYPE Type;
    TUNNEL_TYPE TunnelType;
    NDIS_MEDIUM MediaType;
    NDIS_PHYSICAL_MEDIUM PhysicalMediumType;
    NET_IF_ACCESS_TYPE AccessType;
    NET_IF_DIRECTION_TYPE DirectionType;
    struct {
        BOOLEAN HardwareInterface : 1;
        BOOLEAN FilterInterface : 1;
        BOOLEAN ConnectorPresent : 1;
        BOOLEAN NotAuthenticated : 1;
        BOOLEAN NotMediaConnected : 1;
        BOOLEAN Paused : 1;
        BOOLEAN LowPower : 1;
        BOOLEAN EndPointInterface : 1;
    } InterfaceAndOperStatusFlags;
    IF_OPER_STATUS OperStatus;
    NET_IF_ADMIN_STATUS AdminStatus;
    NET_IF_MEDIA_CONNECT_STATE MediaConnectState;
    NET_IF_NETWORK_GUID NetworkGuid;
    NET_IF_CONNECTION_TYPE ConnectionType;
    ULONG64 TransmitLinkSpeed;
    ULONG64 ReceiveLinkSpeed;
    ULONG64 InOctets;
    ULONG64 InUcastPkts;
    ULONG64 InNUcastPkts;
    ULONG64 InDiscards;
    ULONG64 InErrors;
    ULONG64 InUnknownProtos;
    ULONG64 InUcastOctets;
    ULONG64 InMulticastOctets;
    ULONG64 InBroadcastOctets;
    ULONG64 OutOctets;
    ULONG64 OutUcastPkts;
    ULONG64 OutNUcastPkts;
    ULONG64 OutDiscards;
    ULONG64 OutErrors;
    ULONG64 OutUcastOctets;
    ULONG64 OutMulticastOctets;
    ULONG64 OutBroadcastOctets;
    ULONG64 OutQLen;
} MIB_IF_ROW2, *PMIB_IF_ROW2;

#if (_WIN32_WINNT >= 0x0600)
DWORD WINAPI GetIfEntry2(PMIB_IF_ROW2);
#endif

#ifdef __cplusplus
}
#endif
#endif	/* _IPHLPAPI2_H */

