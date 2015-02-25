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

    Serial.begin(115200);       // start serial for output

    Serial.println ("Starting EV3 Touch Sensor Test program");

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
    touch1.init( &evshield, SH_BAS2);


    Serial.println("setup done");
    Serial.println("Press Touch Sensor to see results");

}

int bumpCount, oldBumpCount;
void
loop()
{
    char str[80];


    //
    // wait for some time
    //
    Serial.println("Sleeping for 5 seconds... (in the meantime, press touch sensor couple of times)");
    delay(5000);
    bumpCount = touch1.getBumpCount();
    sprintf(str, "BumpCount: old: %d, new: %d", oldBumpCount, bumpCount);
    Serial.println(str);
    oldBumpCount = bumpCount;
}

