#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// I2C pin definition
#define I2C_SDA 32
#define I2C_SCL 33

// oneWire channel protocol pin
#define ONE_WIRE_BUS 14

// Screen definition
#define SCREEN_ADDRESS 0x3C // Screen i2C Address
#define SCREEN_WIDTH 128    // OLED display width, in pixels
#define SCREEN_HEIGHT 32    // OLED display height, in pixels
#define OLED_RESET -1       // Reset pin

#include "./classes/screen.h"
#include "./classes/thermometer.h"

#define LED 2

Screen *sc = 0;
Thermometer *th = 0;

void setup()
{

  Serial.begin(9600);
  Wire.begin(I2C_SDA, I2C_SCL); // Start i2C
  sc = new Screen(SCREEN_ADDRESS, SCREEN_WIDTH, SCREEN_HEIGHT, OLED_RESET, &Wire);
  th = new Thermometer(ONE_WIRE_BUS);

  Serial.println("PowerStationMonitor is starting...");
  sc->write((char *)"PowerStationMonitor is starting...");
  delay(2000);
  Serial.println("Configuring I2C bus SDA->32 SDL->33  ...");
  sc->write((char *)"Configuring I2C bus SDA->32 SDL->33  ...");
  delay(2000);
  Serial.println("I2C bus configuration done.");
  sc->write((char *)"I2C bus configuration done.");
  delay(2000);
  sc->write((char *)"Power Station Monitor 1.0");

  //  Set pin mode
  pinMode(LED, OUTPUT);
}

void loop()
{
  delay(100);
  digitalWrite(LED, HIGH);
  delay(100);
  digitalWrite(LED, LOW);

  char bufMessage[512];
  memset(bufMessage, 0, 512);
  th->getTemperaturesString(bufMessage);
  Serial.println(bufMessage);
  sc->write((char *)bufMessage);
  delay(100);
}

void searchi2CDevices()
{
  byte error, address;
  int nDevices;
  Serial.println("Scanning...");
  nDevices = 0;
  for (address = 1; address < 127; address++)
  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address < 16)
      {
        Serial.print("0");
      }
      Serial.println(address, HEX);
      nDevices++;
    }
    else if (error == 4)
    {
      Serial.print("Unknow error at address 0x");
      if (address < 16)
      {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
  {
    Serial.println("No I2C devices found\n");
  }
  else
  {
    Serial.println("done\n");
  }
}