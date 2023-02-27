#ifndef _SDCARD
#define _SDCARD
#include <SPI.h>
#include <SD.h>

#define SD_CS_PIN 15
#define SD_CLK_PIN 2
#define SD_MOSI_PIN 4
#define SD_MISO_PIN 16

class SdCard
{
private:
    // SPIClass *spi = 0;
    bool bSdCardPresent = false;
    int delayTime = 1000;
    int initSDCard()
    {
        pinMode(SD_CS_PIN, OUTPUT);
        SPIClass SPI2(HSPI);
        bSdCardPresent = SD.begin(SD_CS_PIN, SPI2);

        return 0;
    }

public:
    SdCard()
    {
        initSDCard();
    }

    int isCardPresent()
    {
        return bSdCardPresent;
    }
};

#endif