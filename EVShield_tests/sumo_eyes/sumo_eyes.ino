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
#include <EVs_SumoEyes.h>\

#define shortrange false
#define longrange true


//
// declare the EVShield(s) attached to your Arduino.
//
EVShield    evshield(0x34,0x36);

//
// declare the i2c devices used on EVShield(s).
//

//
// declare analog devices attached to evshields.
//
EVs_SumoEyes    seyes1;

int inByte = 0;

void setup()
{
  char            str[80];

  Serial.begin(115200);       // start serial for output
  delay(500);                // wait, allowing time to
                             // activate the serial monitor
  Serial.println ("Initializing the devices ...");
 
  //
  // Initialize the Hardware I2C protocol for EVShield.
  //
  evshield.init( SH_HardwareI2C );

  //
  // Initialize the i2c sensors.
  //

  // initialize the analog sensors.
  seyes1.init( &evshield, SH_BAS1 );
  
  //
  // Wait until user presses GO button to continue the program
  //
  while (!evshield.getButtonState(BTN_GO)) {
    if (millis() % 1000 < 3) {
      Serial.println("Press GO button to continue");
    }
  }
  
}

void
loop()
{
  int seyesValue;
  SE_Zone obzone;
  char str[256];
  char aa[80];
  bool touchPressed;
  bool status;
  bool zone;

      Serial.println("----------------------------------------------");
      zone = shortrange;	//set the range to short
      //zone = longrange;	//set the range to long
      if ( zone ) {
        status = seyes1.setLongRange();
        delay (500);
      } 
      else {
        status = seyes1.setShortRange();
        delay (500);
      }
      seyesValue = seyes1.readRaw();
      obzone = seyes1.detectObstacleZone();

      sprintf (str, "Sumo Eyes (Range: %s) raw value: %d, obzone: %d (%s)",
                                          zone?"Long":"Short",
                                          seyesValue, obzone,
                                          seyes1.OBZoneToString(obzone) );
      Serial.println(str);

      Serial.println("----------------------------------------------");

    delay (1500);
}

