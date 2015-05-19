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
//#include <EVShieldAGS.h>
#include <EVs_EV3Touch.h>


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
EVs_EV3Touch touch1;

void
setup()
{
    char            str[50];
    long timeBefore, timeAfter;

    Serial.begin(115200);       // start serial for output

    Serial.println ("--------------------------------------");
    Serial.println ("Starting EV3 Touch Sensor Light Switch program");
    Serial.println ("--------------------------------------");

    //
    // initialize the shield i2c interface.
    //
    timeBefore = millis();
    evshield.init( SH_HardwareI2C );
    timeAfter = millis();
    sprintf (str, "after evshield.init(): %ld, %ld", timeAfter - timeBefore, timeAfter);
    Serial.println(str);

    //
    // red on bank a and
    // blue on bank b
    //
    Serial.println("before led on");
    timeBefore = millis();
    evshield.bank_a.ledSetRGB(5,0,0);
    evshield.bank_b.ledSetRGB(0,0,5);
    timeAfter = millis();
    sprintf(str, "after led on, %ld, %ld", timeAfter - timeBefore, timeAfter);
    Serial.println( str );

    //
    //  initialize the sensor, and tell where it is connected.
    //
    Serial.println("before touch1.init");
    timeBefore = millis();
    touch1.init( &evshield, SH_BAS1);
    timeAfter = millis();
    sprintf(str, "after touch1.init: %ld, %ld", timeAfter - timeBefore, timeAfter);
    Serial.println(str);


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
    /*
    sprintf (str, "TouchSensor Status: %s", bTouchVal?"Pressed":"not-pressed");
    Serial.println(str);
    sprintf (str, "TouchSensor Bump Count: %d", touch1.getBumpCount());
    Serial.println(str);
    Serial.println("Press LEFT button to reset bump count");
    */
    if ( bTouchVal ) {
        //
        // power on the leds in Red color
        //
        evshield.ledSetRGB(255,0,0);
    } else {
        //
        // turn off the leds
        //
        evshield.ledSetRGB(0,0,0);
    }
    if ( evshield.getButtonState(BTN_LEFT) == true ) {
        Serial.println("resetting bump count");
        touch1.resetBumpCount();
    }
    //
    // wait for one second
    //
    delay(1000);
}

