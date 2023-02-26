#ifndef _WEBGUISERVER
#define _WEBGUISERVER
#include <ETH.h>
#include <WebServer.h>
#include "./classes/config.h"

#include <Arduino.h>
#include <ETH.h>

/*///////////////////////////////////////////////
/////////////////////////////////////////////////
CONFIGURATION NEEDED BY LAN8720 CHIP
DO NOT EDIT!
/////////////////////////////////////////////////
///////////////////////////////////////////////*/

#define ETH_CLOCK_IN_PIN 0
#define ETH_MDIO_PIN 18
#define ETH_TXD0_PIN 19
#define ETH_TXEN_PIN 21
#define ETH_TXD1_PIN 22
#define ETH_MDC_PIN 23
#define ETH_RXD0_PIN 25
#define ETH_RXD1_PIN 26
#define ETH_MODE2_PIN 27
// Nelle versioni precedenti il power pin è 12
#define ETH_POWER_PIN 17
#define ETH_ADDR 1
#define ETH_TYPE ETH_PHY_LAN8720
#define ETH_CLK_MODE ETH_CLOCK_GPIO0_IN
/////////////////////////////////////////////////

class WebGuiServer
{
private:
    Config *cnf = 0;

public:
    WebGuiServer()
    {
        initServer();
    }

    void initServer()
    {
        cnf = new Config();
        _configData cnfData = cnf->getConfig();

        // Select the IP address according to your local network
        IPAddress myIP(cnfData.ip_address[0], cnfData.ip_address[1], cnfData.ip_address[2], cnfData.ip_address[3]);
        IPAddress mySN(cnfData.netmask[0], cnfData.netmask[1], cnfData.netmask[2], cnfData.netmask[3]);
        IPAddress myGW(cnfData.gateway[0], cnfData.gateway[1], cnfData.gateway[2], cnfData.gateway[3]);
        IPAddress myDNS(cnfData.dns[0], cnfData.dns[1], cnfData.dns[2], cnfData.dns[3]);

        ETH.begin(ETH_ADDR, ETH_POWER_PIN, ETH_MDC_PIN, ETH_MDIO_PIN, ETH_TYPE, ETH_CLK_MODE);
        ETH.setHostname("powerstation.wfn.ovh");
        ETH.config(myIP, myGW, mySN, myDNS);
    }
};

#endif