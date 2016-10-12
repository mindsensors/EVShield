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

/* To see this program working, 
 *   Connect a Touch sensor to BAS1
 *   Connect a Light sensor to BAS2
 *   Download this program on your Arduino.
 *   Start the Serial Monitor in Arduino-IDE
 *   Set baud rate to 115200 for your serial connection
 *   Follow instructions in serial window.
 */
 
#include <Wire.h>
#include <EVShield.h>
#include <EVs_NXTTouch.h>
#include <EVs_NXTLight.h>

//
// declare the EVShield(s) attached to your Arduino.
//
EVShield    evshield;

//
// declare analog devices attached to EVShield.
//
EVs_NXTTouch    touch1;
EVs_NXTLight    light1;

void setup()
{
  Serial.begin(115200);       // start serial for output
  delay(500);                // wait, allowing time to
                             // activate the serial monitor
  Serial.println ("Initializing the devices ...");
  //
  // Initialize the protocol 
  // It is best to use Hardware I2C
  //
  evshield.init( SH_HardwareI2C );

  //
  // Wait until user presses GO button to continue the program
  //
  while (!evshield.getButtonState(BTN_GO)) {
    if (millis() % 1000 < 3) {
      Serial.println("Press GO button to continue");
    }
  }

  //
  // initialize the analog sensors.
  // NXT light sensor is not supported on BAS1.
  // connect a NXT light sensor to BAS2,
  // connect a touch sensor to BAS1
  //
  touch1.init( &evshield, SH_BAS1 );
  light1.init( &evshield, SH_BAS2 );
}

bool lastTouch, touchPressed;
void loop()
{
  char            str[256];
  int lightReading;

  Serial.println("------------------------------------");

  touchPressed = touch1.isPressed();
  sprintf (str, "touch1: is pressed : %s", touchPressed?"true":"false");
  Serial.println(str);

  if ( touchPressed != lastTouch ) {
    if ( touchPressed == true ) {
      Serial.println( "Changing light sensor to reflected light mode" );
      light1.setReflected();
    } else {
      Serial.println( "Changing light sensor to ambient light mode" );
      light1.setAmbient();
    }
    lastTouch = touchPressed;
  }
  lightReading = light1.readRaw();
  sprintf (str, "Light sensor Reading: %d", lightReading);
  Serial.println (str);

  delay (1000);
}
