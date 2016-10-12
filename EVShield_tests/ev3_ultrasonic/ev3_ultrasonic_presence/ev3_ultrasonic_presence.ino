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
#include <EVs_EV3Ultrasonic.h>

// setup for this example:
// attach EV3 Ultrasonic Sensor to Port BAS1
// Open the Serial terminal to view results.

EVShield     evshield(0x34,0x36); //  Create shield object
EVs_EV3Ultrasonic myUS; //  Create our sensor for use in this program

void setup()
{

    Serial.begin(115200);       // start serial for output
    //
    // initialize the shield i2c interface.
    //
    evshield.init( SH_HardwareI2C );

    Serial.println ("--------------------------------------");
    Serial.println ("Starting EV3 Ultrasonic Sensor Presence Test program");
    Serial.println ("--------------------------------------");

    //
    //  initialize the sensor, and tell where it is connected.
    //
    myUS.init( &evshield, SH_BAS1 );
    myUS.setMode(MODE_Sonar_Presence);

    Serial.println("setup done");
    Serial.println("turn another ultrasonic device on and off");
    Serial.println ("Press GO button to continue");
    evshield.waitForButtonPress(BTN_GO);

}

void
loop()
{
    //
    // declare variable(s)
    //    
    int detect;

    //
    // get the reading(s) from sensor
    //
    detect = myUS.detect();

    //
    // print the sensor value(s)
    //
    Serial.print("Device found? "); Serial.println(detect);


    //
    // wait for some time
    //
    delay(1000);
}

