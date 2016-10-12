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
NXT Color Sensor works best with LEGO colors at close distance.

For beginners tutorial (and user guide) visit:
http://www.openelectrons.com/docs/viewdoc/25
*/

#include <Wire.h>
#include <EVShield.h>
#include <EVs_NXTColor.h>


// setup for this example:
// attach external power to evshield.
// attach NXT Color Sensor to Port BBS2
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

    Serial.println ("Starting NXTColor Sensor Color Change");

    //
    // initialize the shield i2c interface.
    //
    evshield.init( SH_HardwareI2C );

    //
    // red on bank a and
    // blue on bank b
    //
    evshield.bank_a.ledSetRGB(255,255,255);
    evshield.bank_b.ledSetRGB(255,255,255);
    
    while (!evshield.getButtonState(BTN_GO)) {
        if (millis() % 1000 < 3) {
            Serial.println("Press GO button to continue");
        }
    }
    //
    //  initialize the sensor, and tell where it is connected.
    //
    c1.init( &evshield, SH_BBS2);
    c1.setType(SH_Type_COLORFULL);
    
    Serial.println("Bank A motors >>");
    sprintf(str, "Run Slow");
    Serial.println(str);
    str[0] = '\0';
    evshield.bank_a.motorRunUnlimited(SH_Motor_Both, 
                     SH_Direction_Reverse, 
                     1);  

}

void
loop()
{
    int val;
    char str[50];


    //
    // read the value from color sensor
    //
    val = c1.readColor();

    //
    // print the value on serial terminal
    //
    Serial.print("color sensor value: "); Serial.println(val);
    switch(val){
      case 2:
        evshield.ledSetRGB(0,0,255);
        break;
      case 4:
        evshield.ledSetRGB(255,255,0);
        break;
      case 5:
        evshield.ledSetRGB(255,0,0);
        break;
      default:
        evshield.ledSetRGB(255,255,255);
        break;
    }
    //
    // wait for 25 milliseconds
    //
    delay(25);
}

