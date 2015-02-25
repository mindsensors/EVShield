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
#include <EVs_EV3Gyro.h>

// setup for this example:
// attach external power to evshield.
// attach EV3 Gyro Sensor to Port BBS1
// Open the Serial terminal to view results.

EVShield     evshield(0x34,0x36); //  Create shield object
EVs_EV3Gyro myGyro; //  Create our sensor for use in this program

void setup()
{
    char    str[50];

    Serial.begin(115200);       // start serial for output
    //
    // initialize the shield i2c interface.
    //
    evshield.init( SH_HardwareI2C );

    Serial.println ("--------------------------------------");
    Serial.println ("Starting EV3 Gyro Sensor Test program");
    Serial.println ("--------------------------------------");

    //
    // red on bank a and
    // blue on bank b
    //
    evshield.bank_a.ledSetRGB(5,0,0);
    evshield.bank_b.ledSetRGB(0,0,5);

    //
    //  initialize the sensor, and tell where it is connected.
    //
    myGyro.init( &evshield, SH_BBS1 );
    //us1.setMode(MODE_Sonar_Inches);
    //myGyro.setMode(MODE_Gyro_Rate);
    myGyro.setMode(MODE_Gyro_Angle);


    Serial.println("setup done");
    Serial.println("turn your gyro to see change in value");

}

char last_data[200];
char curr_data[200];
char output[500];

void
loop()
{
    uint8_t mode;
    int angle;
    char str[50];
    int i;

    //myGyro.readAndPrint(0x81+myGyro.m_offset, 10);
    //
    // get the reading from sensor
    //
    angle = myGyro.getAngle();

    //
    // print the sensor staus
    //
    Serial.print("angle: "); Serial.println(angle);


    //
    // wait for some time
    //
    delay(1000);
}

