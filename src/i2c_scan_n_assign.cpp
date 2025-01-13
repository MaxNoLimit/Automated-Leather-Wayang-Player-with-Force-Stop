#include "i2c_scan_n_assign.hpp"
#include "mainheader.hpp"

/*
Function untuk scanning address dari I2C yang terhubung dengan Arduino Mega 2560 dan akan me-return address yang ditemukan
*/
int I2C_Scanner::scan_n_assign()
{
    int lcd_2040_address;
    Wire.begin();
    byte error, address;
    int nDevices;

    Serial.println(F("Scanning..."));

    nDevices = 0;
    for (address = 1; address < 127; address++)
    {
        // The i2c_scanner uses the return value of
        // the Write.endTransmisstion to see if
        // a device did acknowledge to the address.
        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        if (error == 0)
        {
            Serial.print(F("I2C device found at address 0x"));
            if (address < 16)
                Serial.print(F("0"));
            Serial.print(address, HEX);
            Serial.println(F("  !"));

            // nDevices++; only one address so after found, break
            lcd_2040_address = address;
            break;
        }
        else if (error == 4)
        {
            Serial.print(F("Unknown error at address 0x"));
            if (address < 16)
                Serial.print(F("0"));
            Serial.println(address, HEX);
        }
    }
    if (nDevices == 0)
        Serial.println(F("No I2C devices found\n"));
    else
        Serial.println(F("done\n"));
        
    return lcd_2040_address;
}