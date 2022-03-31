
//
// Copyright (c) .NET Foundation and Contributors
// See LICENSE file in the project root for full license information.
//

#include <nanoHAL.h>

#if defined(AZURE_RTOS_NETXDUO)
#include <nx_api.h>
#include <nxd_bsd.h>
#endif

#include <network_options.h>
#include <nf_wireless.h>

// extern "C" struct netif *nf_getNetif();
//
// Works with the Target_NetworkConfig to map the Network_Interface_XXXXX calls to the correct driver

bool Network_Interface_Bind(int index)
{
    (void)index;

    return true;
}

int Network_Interface_Open(int index)
{
    HAL_Configuration_NetworkInterface networkConfiguration;

    // load network interface configuration from storage
    if (!ConfigurationManager_GetConfigurationBlock(
            (void *)&networkConfiguration,
            DeviceConfigurationOption_Network,
            index))
    {
        // failed to load configuration
        // FIXME output error?
        return SOCK_SOCKET_ERROR;
    }
    _ASSERTE(networkConfiguration.StartupAddressMode > 0);

    switch (networkConfiguration.InterfaceType)
    {

#if (TARGET_HAS_WIFI_SUPPORT == 1)
        // Wi-Fi (STA)
        case NetworkInterfaceType_Wireless80211:
            return NF_Wireless_Open(&networkConfiguration);
#endif

        // // Wi-Fi (Soft AP)
        // case NetworkInterfaceType_WirelessAP:
        //     return NF_WirelessAP_Open(&networkConfiguration);

#if (TARGET_HAS_ETHERNET_SUPPORT == 1)
        // Ethernet
        case NetworkInterfaceType_Ethernet:
            return NF_ESP32_Ethernet_Open(&networkConfiguration);
#endif
        default:
            break;
    }

    return SOCK_SOCKET_ERROR;
}

bool Network_Interface_Close(int index)
{
    HAL_Configuration_NetworkInterface networkConfiguration;

    // load network interface configuration from storage
    if (!ConfigurationManager_GetConfigurationBlock(
            (void *)&networkConfiguration,
            DeviceConfigurationOption_Network,
            index))
    {
        // failed to load configuration
        // FIXME output error?
        return SOCK_SOCKET_ERROR;
    }

    switch (networkConfiguration.InterfaceType)
    {

#if (TARGET_HAS_WIFI_SUPPORT == 1)
        // Wireless
        case NetworkInterfaceType_Wireless80211:
            return NF_Wireless_Close();

        // // Soft AP
        // case NetworkInterfaceType_WirelessAP:
        //     return NF_ESP32_WirelessAP_Close();
#endif

#if (TARGET_HAS_ETHERNET_SUPPORT == 1)
        // Ethernet
        case NetworkInterfaceType_Ethernet:
            return NF_ESP32_Ethernet_Close();
#endif

        default:
            break;
    }

    return false;
}

// bool Network_Interface_Start_Scan(int index)
// {
//     HAL_Configuration_NetworkInterface networkConfiguration;

//     // load network interface configuration from storage
//     if (!ConfigurationManager_GetConfigurationBlock(
//             (void *)&networkConfiguration,
//             DeviceConfigurationOption_Network,
//             index))
//     {
//         // failed to load configuration
//         // FIXME output error?
//         return SOCK_SOCKET_ERROR;
//     }

//     // can only do this is this is STA
//     if (networkConfiguration.InterfaceType == NetworkInterfaceType_Wireless80211)
//     {
//         return (NF_ESP32_Wireless_Scan() == 0);
//     }

//     return false;
// }

int Network_Interface_Start_Connect(int index, const char *ssid, const char *passphase, int options)
{
    (void)index;
    (void)ssid;
    (void)passphase;
    (void)options;

return SOCK_SOCKET_ERROR;
}


int Network_Interface_Connect_Result(int index)
{
    (void)index;


return SOCK_SOCKET_ERROR;
}

int Network_Interface_Disconnect(int index){
    (void)index;


return SOCK_SOCKET_ERROR;
}