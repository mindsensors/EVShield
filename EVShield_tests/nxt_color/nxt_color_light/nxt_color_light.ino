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
// attach external power to evshield.
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

    Serial.println ("Starting NXT Color Sensor Test program");

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
    c1.init( &evshield, SH_BAS1);
    c1.setType(SH_Type_COLORNONE);	//Color none returns ambient light values


    Serial.println("setup done");
    Serial.println("hold a colored object in front of the color sensor");

}

void
loop()
{
    int val;
    char str[50];


    //
    // read the value from color sensor
    //
    val = c1.readValue();

    //
    // print the value on serial terminal
    //
    Serial.print("color sensor light value: "); Serial.println(val);
    
    //
    // wait for one second
    //
    delay(1000);
}

