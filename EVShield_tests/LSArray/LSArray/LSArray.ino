/*
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
*/
/*
For beginners tutorial (and user guide) visit:
http://www.openelectrons.com/docs/viewdoc/25
*/

#include <Wire.h>
#include <EVShield.h>
#include <EVs_LightSensorArray.h>

// setup for this example:
// attach LightSensorArray to Port BAS1
// Open the Serial terminal to view.

//
// declare the EVShield(s) attached to your Arduino.
//
EVShield    evshield(0x34,0x36);

//
// declare the i2c devices used on EVShield(s).
//
EVs_LightSensorArray lsa (0x14);

void setup()
{
  char str[256];

  Serial.begin(115200);  // start serial for output
  delay(500); // wait, allowing time to activate the serial monitor

  // Initialize the Hardware I2C protocol for EVShield
  //
  evshield.init( SH_HardwareI2C );

  //
  // Initialize the i2c sensors.
  //
  lsa.init( &evshield, SH_BAS1 );

  //
  // Wait until user presses GO button to continue the program
  //
  while (!evshield.getButtonState(BTN_GO)) {
    if (millis() % 1000 < 3) {
      Serial.println("Press GO button to continue");
    }
  }

}

#define DELAY_T 0

void loop()
{
  char aa[80];
  char str[256];        //declare character string length           
  uint8_t *cal;         //declare "cal" pointer
  int  i;               //declare integer "i"
  
 /** Display Firmware Version */
  strcpy(aa, lsa.getFirmwareVersion() );
  sprintf (str, "LSArray: getFirmwareVersion: %s", aa);
  Serial.println(str);
/** Display Device ID */
  strcpy(aa, lsa.getDeviceID() );
  sprintf (str, "LSArray: DeviceID: %s", aa);
  Serial.println(str);
/** Display Vendor ID */
  strcpy(aa, lsa.getVendorID() );
  sprintf (str, "LSArray: VendorID: %s", aa);
  Serial.println(str);
/** Display 8 different light sensor values */  
  cal = lsa.getCalibrated();
  for (i=0; i< 8; i++)
  {    
    sprintf (str, "LSArray: sensor array: %d = %d", i, cal[i] );
    Serial.println(str);
  }

  Serial.println( "-------------" );
  delay (1500);
}



