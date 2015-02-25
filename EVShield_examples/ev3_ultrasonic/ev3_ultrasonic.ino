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
#include <EVs_EV3Ultrasonic.h>


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
EVs_EV3Ultrasonic us1;

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
    us1.init( &evshield, SH_BAS2 );
    //us1.setMode(MODE_Sonar_Inches);
    us1.setMode(MODE_Sonar_CM);


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

    //
    // get the reading from sensor
    //
    distance = us1.getDist();
    mode = us1.getMode();

    //
    // print the sensor staus
    //
    char *s;
    switch (mode) {
        case MODE_Sonar_Inches:
            s = "Inches";
            break;
        case MODE_Sonar_CM:
            s = "cm";
            break;
    }
    Serial.print("Distance to obstacle: "); Serial.print(distance);
    Serial.print (" (");
    Serial.print (s);
    Serial.println (")");


    //
    // wait for some time
    //
    delay(1000);
}

