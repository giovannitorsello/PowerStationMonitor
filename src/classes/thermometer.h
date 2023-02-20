#ifndef _THERMOMETER
#define _THERMOMETER

#include <OneWire.h>
#include <DallasTemperature.h>

class Thermometer
{
private:
    int oneWire_channel = 0;
    int nThermometers = 0;
    float temperatures[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    DallasTemperature *p_sensors = 0;
    OneWire *p_oneWire = 0;

public:
    Thermometer(int oneWire_channel)
    {
        this->oneWire_channel = oneWire_channel;
        p_oneWire = new OneWire(oneWire_channel);
        p_sensors = new DallasTemperature(this->p_oneWire);
        p_sensors->begin();
        nThermometers = p_sensors->getDeviceCount();
    }

public:
    int getNumThermometers()
    {
        this->nThermometers = p_sensors->getDeviceCount();
        return nThermometers;
    }

    float *getTemperatures()
    {
        p_sensors->requestTemperatures();
        int nDevices = p_sensors->getDeviceCount();

        for (int i = 0; i < nDevices; i++)
            temperatures[i] = p_sensors->getTempCByIndex(i);

        return temperatures;
    }

    void getNumThermometersString(char *buf)
    {
        getNumThermometers();
        sprintf(buf, "There are %d thermometer sensors", nThermometers);
    }

    void getTemperaturesString(char *buf)
    {
        getNumThermometers();
        getTemperatures();

        char bufTemp[100];
        sprintf(bufTemp, "Batt. temperatures\n");
        strcat(buf, bufTemp);
        for (int i = 0; i < nThermometers; i++)
        {
            sprintf(bufTemp, "|%.2f", temperatures[i]);
            if (i > 0 && i % 2 == 0)
                strcat(buf, "|\n");
            strcat(buf, bufTemp);
        }
        strcat(buf, "|");
    }
};

#endif