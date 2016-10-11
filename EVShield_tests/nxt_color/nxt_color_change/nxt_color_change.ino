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
#include <EVs_NXTColor.h>


// setup for this example:
// attach NXT Color Sensor to Port BAS1
// Open the Serial terminal to view.

//
//  Declare shield variable for this program
//
EVShield          evshield(0x34,0x36);

//
//  Declare our sensor for use in this program
//
EVs_NXTColor c1;

void
setup()
{
    char            str[50];

    Serial.begin(115200);       // start serial for output

    Serial.println ("Starting NXT Color Sensor Color Change Test program");

    //
    // initialize the shield i2c interface.
    //
    evshield.init( SH_HardwareI2C );

    //
    //  initialize the sensor, and tell where it is connected.
    //
    c1.init( &evshield, SH_BAS1);
    c1.setType(SH_Type_COLORNONE);


    Serial.println("setup done");
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
    int val;
    char str[50];


    //
    // Turn lamp red
    //
    c1.setType(SH_Type_COLORRED);
    Serial.println("Red");
    delay(1000);

    //
    // Turn lamp Green
    //
    c1.setType(SH_Type_COLORGREEN);
    Serial.println("Green");
    delay(1000);

    //
    // Turn lamp blue
    //
    c1.setType(SH_Type_COLORBLUE);
    Serial.println("Blue");
    delay(1000);

    //
    // Turn lamp white
    //
    c1.setType(SH_Type_COLORFULL);
    Serial.println("White");
    delay(1000);

    //
    // Turn lamp off
    //
    c1.setType(SH_Type_COLORNONE);
    Serial.println("Off");
    delay(1000);
}

