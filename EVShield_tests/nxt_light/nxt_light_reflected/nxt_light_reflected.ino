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
 * For beginners tutorial (and user guide) visit:
 * http://www.openelectrons.com/docs/viewdoc/25
 */

#include <Wire.h>
#include <EVShield.h>
#include <EVShieldAGS.h>
#include <EVs_NXTLight.h>

// setup for this example:
// attach NXT Light Sensor to Port BAS1
// Open the Serial terminal to view results.

EVShield     evshield(0x34,0x36); //  Create shield object
EVs_NXTLight myLight; //  Create our sensor for use in this program

void setup()
{

    Serial.begin(115200);       // start serial for output
    //
    // initialize the shield i2c interface.
    //
    evshield.init( SH_HardwareI2C );

    Serial.println ("--------------------------------------");
    Serial.println ("Starting NXT Light Sensor Reflected Light Test program");
    Serial.println ("--------------------------------------");

    //
    //  initialize the sensor, and tell where it is connected.
    //
    myLight.init( &evshield, SH_BAS1 );
    myLight.setReflected();

    Serial.println("setup done");
    Serial.println("shine or block light going into color sensor to see change in value");
    Serial.println ("Press GO button to continue");
    evshield.waitForButtonPress(BTN_GO);

}

void
loop()
{
    //
    // declare variable(s)
    //    
    int light;

    //
    // get the reading(s) from sensor
    //
    light = myLight.readRaw();

    //
    // print the sensor value(s)
    //
    Serial.print("Reflected Light: "); Serial.println(light);


    //
    // wait for some time
    //
    delay(1000);
}

