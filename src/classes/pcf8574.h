#ifndef _PCF8574
#define _PCF8574
// Including I2C libraries
#include <Wire.h>

class Pcf8574
{
private:
    int i2c_address = 0;

public:
    Pcf8574(int i2c_address)
    {
        this->i2c_address = i2c_address;
        Wire.begin(i2c_address);
    }

    int write(int channel, char buf[], int len_buf)
    {
        int n_bytes_written = 0;
        Wire.begin();
        Wire.beginTransmission(this->i2c_address);
        for (int i = 0; i < len_buf; i++)
        {
            int n = Wire.write(buf[i]);
            n_bytes_written += n;
        }
        Wire.endTransmission();
        return n_bytes_written;
    }

    int read(char *bufRead)
    {
        int nReceivedBytes = 0;
        nReceivedBytes = Wire.requestFrom(i2c_address, nReceivedBytes, 1);
        memset(bufRead, 0, nReceivedBytes);
        for (int i = 0; i < nReceivedBytes; i++)
            bufRead[i] = Wire.read();

        return nReceivedBytes;
    }
};

#endif