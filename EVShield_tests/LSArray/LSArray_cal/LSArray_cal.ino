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
EVs_LightSensorArray lsa (0x02);
byte test = 1;

void setup()
{
  char str[256];

  Serial.begin(115200);  // start serial for output
  delay(500); // wait, allowing time to activate the serial monitor

  //  Serial.println (__FILE__);
  //  Serial.println ("Initializing the devices ...");
  //
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
  char str[256];
  uint8_t  result;
  char str2[20];

  strcpy(aa, lsa.getFirmwareVersion() );
  sprintf (str, "Lineleader Firmware Version: %s", aa);
  Serial.println(str);

  strcpy(aa, lsa.getDeviceID() );
  sprintf (str, "Lineleader Device ID %s", aa);
  Serial.println(str);

  strcpy(aa, lsa.getVendorID() );
  sprintf (str, "Lineleader Vendor ID: %s", aa);
  Serial.println(str);
  
  while(test == 1){  
    Serial.println("Hold over White and press LEFT button to continue.");
    evshield.waitForButtonPress(BTN_LEFT);
    lsa.calibrateWhite();
    delay(100);
    Serial.println("Hold over Black and press RIGHT button to continue.");
    evshield.waitForButtonPress(BTN_RIGHT);
    lsa.calibrateBlack();
    delay(100);
    Serial.println("LightSensorArray Calibrated!");
    test = 2;
}

  Serial.println("Should see values close to 100 when on white and close 0 when on black");

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


