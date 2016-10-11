/************************************************************************/
/*                                                                 
  Copyright (c) 2015 by mindsensors.com                                
  Email: info (<at>) mindsensors (<dot>) com                          
                                                                    
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

************************************************************************/
/*
For beginners tutorial (and user guide) visit:
http://www.openelectrons.com/docs/viewdoc/25
*/

#include <Wire.h>
#include <EVShield.h>


EVShield    evshield;

int inByte = 0;

void setup()
{
  char            str[80];

  Serial.begin(115200);       // start serial for output
  delay(500);                // wait, allowing time to
                             // activate the serial monitor

  //
  // EVShield supports multiple transports
  // Initialize the transport for i2c devices.
  //
  evshield.init(SH_HardwareI2C);

  //
  // Wait until user presses GO button to continue the program
  //
  while (!evshield.getButtonState(BTN_GO)) {
    if (millis() % 1000 < 3) {
      Serial.println("Press GO button to continue");
    }
  }

}

static int counter;
void
loop()
{
    int ba_v1, ba_v2, bb_v1, bb_v2, bb_us;
    char            str[256];
    int accl_x;
    bool touchPressed;
    bool status;

    while (true) {

        if (Serial.available() > 0) {
            //
            // get user input from serial window
            //
            inByte = Serial.read();
            sprintf (str, "input: %c", inByte); 
            Serial.println(str);

            switch (inByte) {
                case '1':
                    // turn on RED LED
                    evshield.ledSetRGB(8, 0, 0);
                    break;
                case '2':
                    // turn on Green LED
                    evshield.ledSetRGB(0, 8, 0);
                    break;
                case '3':
                    // turn on blue LED
                    evshield.ledSetRGB(0, 0, 8);
                    break;

                default:
                    sprintf (str, "this key not implemented");
                    Serial.println(str);
                    break;
            }
        } else {
            counter ++;
            sprintf (str,"counter: %d", counter);
            Serial.println(str);

            strcpy (str, "BA ... ");
            strcat (str, "F/w Version: ");
            strcat (str, evshield.bank_a.getFirmwareVersion());
            strcat (str, ", Vendor ID: ");
            strcat (str, evshield.bank_a.getVendorID());
            strcat (str, ", Device ID: ");
            strcat (str, evshield.bank_a.getDeviceID());
            strcat (str, ", Feature Set: ");
            strcat (str, evshield.bank_a.getFeatureSet());
            Serial.println(str);

            delay (100);
            strcpy (str, "BB ... ");
            strcat (str, "F/w Version: ");
            strcat (str, evshield.bank_b.getFirmwareVersion());
            strcat (str, ", Vendor ID: ");
            strcat (str, evshield.bank_b.getVendorID());
            strcat (str, ", Device ID: ");
            strcat (str, evshield.bank_b.getDeviceID());
            strcat (str, ", Feature Set: ");
            strcat (str, evshield.bank_b.getFeatureSet());
            Serial.println(str);

            int voltage;
            voltage = evshield.bank_a.evshieldGetBatteryVoltage();
            Serial.print ("Voltage (milli-volts): ");
            Serial.println ( voltage );

        }
        delay (1000);
    }
}
