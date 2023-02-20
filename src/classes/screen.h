#ifndef _SCREEN
#define _SCREEN
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class Screen
{
private:
    int i2c_address = 0;
    int width = 0;
    int height = 0;
    int reset_pin = 0;
    TwoWire *pWire;
    Adafruit_SSD1306 *display = 0;

public:
    Screen(int i2c_address, int width, int height, int reset_pin, TwoWire *pWire)
    {
        this->i2c_address = i2c_address;
        this->width = width;
        this->height = height;
        this->reset_pin = reset_pin;
        this->pWire = pWire;

        Serial.println("Configuring screen...");
        pWire->beginTransmission(this->i2c_address);
        display = new Adafruit_SSD1306(width, height, pWire, reset_pin);
        pWire->endTransmission();

        // initialize the OLED object
        if (!display->begin(SSD1306_SWITCHCAPVCC, this->i2c_address))
            Serial.println(F("SSD1306 allocation failed"));

        Serial.println("Screen configuration done");
    }

    int write(char *buf)
    {

        display->clearDisplay();
        display->setTextSize(1);
        display->setTextColor(WHITE);
        display->setCursor(0, 0);
        display->println(buf);
        display->display();

        return 1;
    }
};

#endif