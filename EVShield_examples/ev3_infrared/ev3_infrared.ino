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
#include <EVs_EV3Infrared.h>


// setup for this example:
// attach external power to evshield.
// attach EV3 Ultrasonic Sensor to Port BAS2
// Open the Serial terminal to view.

//
//  Declare shield variable for this program
//
EVShield          evshield(0x34,0x36);

//
//  Declare our sensor for use in this program
//
EVs_EV3Infrared infra01;

void
setup()
{
    char            str[50];

    Serial.begin(115200);       // start serial for output

    Serial.println ("--------------------------------------");
    Serial.println ("Starting EV3 Ultrasonic Sensor Test program");
    Serial.println ("--------------------------------------");

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
    //  initialize the sensor, and tell where it is connected.
    //
    infra01.init( &evshield, SH_BAS2 );
    infra01.setMode(MODE_Infrared_Proximity);
    //infra01.setMode(MODE_Infrared_Beacon);


    Serial.println("setup done");
    Serial.println("Hold object in front of Sensor to see results");

}

char last_data[200];
char curr_data[200];
char output[500];

void
loop()
{
    uint8_t mode;
    float distance;
    char str[50];
    int i;

    infra01.readAndPrint(0x81+infra01.m_offset, 10);
    //
    // get reading from the sensor
    //
    Serial.print("proximity value: "); Serial.print(infra01.readProximity());
    Serial.println ("");

    //
    // print the sensor staus
    //


    //
    // wait for some time
    //
    delay(500);
}

