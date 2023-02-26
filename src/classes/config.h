#ifndef _CONFIG
#define _CONFIG
#include <Arduino.h>
#include "EEPROM.h"
#define EEPROM_SIZE 256

#define STATUS_RESET 0
#define STATUS_CONFIGURED 1

struct _configData
{
    char name[50];
    char ip_address[4];
    char netmask[4];
    char gateway[4];
    char dns[4];
    char server_ip[4];
    char server_url[150];
    int server_port;
    char status;
};

class Config
{

private:
    int writeConfig()
    {
        configData.status = STATUS_CONFIGURED;
        EEPROM.put(0, configData);
        EEPROM.commit();

        return 0;
    }

    int setIpv4(char *address, char data[4])
    {
        for (int i = 0; i < 4; i++)
            address[i] = data[i];

        return writeConfig();
    }

    int setString(char *field, char *data)
    {
        {
            strcpy(field, data);
            return writeConfig();
        }
    }

    int setInt(int *field, int data)
    {
        {
            *field = data;
            return writeConfig();
        }
    }

public:
    _configData configData;
    Config()
    {
        EEPROM.begin(EEPROM_SIZE);
        memset(&configData, 0, sizeof(_configData));
    }

    Config(_configData cnf)
    {
        EEPROM.begin(EEPROM_SIZE);
        setDeviceName(cnf.name);
        setIpAddress(cnf.ip_address);
        setNetmask(cnf.netmask);
        setGateway(cnf.gateway);
        setDNS(cnf.dns);
        setServerIP(cnf.server_ip);
        setServerPort(cnf.server_port);
        setServerUrl(cnf.server_url);
    }

    _configData getConfig()
    {
        EEPROM.get(0, configData);
        if (configData.status == STATUS_RESET)
        {
            Serial.println("Device seems to be in first execution.");
            setDefaultConfig();
        }

        return configData;
    }

    void printConfiguration()
    {
        char configString[512];

        sprintf(configString, "Name: %s", configData.name);
        Serial.println(configString);
        sprintf(configString, "Ip address:\t\t %d.%d.%d.%d", configData.ip_address[0], configData.ip_address[1], configData.ip_address[2], configData.ip_address[3]);
        Serial.println(configString);
        sprintf(configString, "Netmask:\t\t %d.%d.%d.%d", configData.netmask[0], configData.netmask[1], configData.netmask[2], configData.netmask[3]);
        Serial.println(configString);
        sprintf(configString, "Gateway:\t\t %d.%d.%d.%d", configData.gateway[0], configData.gateway[1], configData.gateway[2], configData.gateway[3]);
        Serial.println(configString);
        sprintf(configString, "Server DNS:\t\t %d.%d.%d.%d", configData.dns[0], configData.dns[1], configData.dns[2], configData.dns[3]);
        Serial.println(configString);
        sprintf(configString, "Server IP:\t\t %d.%d.%d.%d", configData.server_ip[0], configData.server_ip[1], configData.server_ip[2], configData.server_ip[3]);
        Serial.println(configString);
        sprintf(configString, "Server port: %d", configData.server_port);
        Serial.println(configString);
        sprintf(configString, "Server url: %s", configData.server_url);
        Serial.println(configString);
    }

    int setDefaultConfig()
    {
        char ip[4] = {192, 168, 1, 100};
        char netmask[4] = {255, 255, 255, 0};
        char gateway[4] = {192, 168, 1, 1};
        char dns[4] = {8, 8, 8, 8};
        char server[4] = {5, 53, 124, 98};

        memset(&configData, 0, sizeof(_configData));
        strcpy(configData.name, "Device PowerStation");
        setIpv4(configData.ip_address, ip);
        setIpv4(configData.netmask, netmask);
        setIpv4(configData.gateway, gateway);
        setIpv4(configData.dns, dns);
        setIpv4(configData.server_ip, server);
        configData.server_port = 3333;
        strcpy(configData.server_url, "http://powerstations.wfn.net:3333/api/powerstation");
        return 0;
    }

    int setDeviceName(char *data) { return setString(configData.name, data); }
    int setIpAddress(char *data) { return setIpv4(configData.ip_address, data); }
    int setNetmask(char *data) { return setIpv4(configData.netmask, data); }
    int setGateway(char *data) { return setIpv4(configData.gateway, data); }
    int setDNS(char *data) { return setIpv4(configData.dns, data); }
    int setServerIP(char *data) { return setIpv4(configData.server_ip, data); }
    int setServerPort(int data) { return setInt(&configData.server_port, data); }
    int setServerUrl(char *data) { return setString(configData.server_url, data); }
};

#endif