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
#include <EVs_NXTTouch.h>


// setup for this example:
// attach external power to evshield.
// attach NXT Touch Sensor to Port BAS1
// Open the Serial terminal to view.

//
//  Declare shield variable for this program
//
EVShield          evshield(0x34,0x36);

//
//  Declare our sensor for use in this program
//
EVs_NXTTouch touch1;

void
setup()
{
    char            str[50];

    Serial.begin(115200);       // start serial for output

    Serial.println ("Starting NXT Touch Sensor Test program");

    //
    // initialize the shield i2c interface.
    //
    evshield.init( SH_HardwareI2C );

    //
    // red on bank a and
    // blue on bank b
    //
    evshield.bank_a.ledSetRGB(5,0,0);
    evshield.bank_b.ledSetRGB(0,0,5);

    //
    //  initialize the touch sensor, and tell where it is connected.
    //
    touch1.init( &evshield, SH_BAS1);


    Serial.println("setup done");
    Serial.println("Press Touch Sensor to see results");

}

void
loop()
{
    bool bTouchVal;
    char str[50];


    //
    // see if the sensor is pressed.
    //
    bTouchVal = touch1.isPressed();

    //
    // print the sensor staus
    //
    sprintf (str, "TouchSensor Status: %s", bTouchVal?"Pressed":"not-pressed");
    Serial.println(str);
    if ( bTouchVal ) {
        //
        // power on the leds in Red color
        //
        evshield.ledSetRGB(10,0,0);
    } else {
        //
        // turn off the leds
        //
        evshield.ledSetRGB(0,0,0);
    }
    //
    // wait for one second
    //
    delay(1000);
}

