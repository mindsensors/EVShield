/************************************************************************/
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

************************************************************************/
/*
For beginners tutorial (and user guide) visit:
http://www.openelectrons.com/docs/viewdoc/25
*/

#include <Wire.h>
#include <EVShield.h>
#include <EVShieldAGS.h>


// setup for this example:
// attach external power to evshield.
// attach NXT Touch Sensor to Port BAS1
// Open the Serial terminal to view.

//
//  Declare shield variable for this program
//
EVShield          evshield(0x34,0x36);

void
setup()
{
    char            str[50];

    Serial.begin(115200);       // start serial for output

    //
    // initialize the shield i2c interface.
    //
    evshield.init( SH_HardwareI2C );

    Serial.println("Press Shield buttons to see results");
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
    char str[50];  

    //
    // see if go button is pressed.
    //
    if ( evshield.getButtonState(BTN_GO) == true ) {
        Serial.println("GO button pressed");
    }
    
    //
    // see if left button is pressed.
    //
    if ( evshield.getButtonState(BTN_LEFT) == true ) {
        Serial.println("LEFT button pressed");
    }
    //
    //  see if right button is pressed.
    //
    if ( evshield.getButtonState(BTN_RIGHT) == true ) {
        Serial.println("RIGHT button pressed");
    }

    //
    // wait for one second
    //
    delay(1000);
}

