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
*/
/*
For beginners tutorial (and user guide) visit:
http://www.openelectrons.com/docs/viewdoc/25
*/

#include <Wire.h>
#include <EVShield.h>
#include <EVs_PiLight.h>

// setup for this example:
// attach PiLight to I2C Pins
// Open the Serial terminal to view.

//
// declare the EVShield(s) attached to your Arduino.
//
EVShield    evshield;

//
// declare the i2c devices used on EVShield(s).
//

EVs_PiLight  pilyt  (0x30);

void setup()
{
  char str[256];
/**  Start serial for output
 */
  Serial.begin(115200);  // 
/**  Wait, allowing time to activate the serial monitor
 */ 
  delay(500); // wait, allowing time to activate the serial monitor

/**  Initialize the protocol for EVShield
     It is best to use Hardware I2C (unless you want to use Ultrasonic).
 */
  evshield.init( SH_HardwareI2C );

/**  Initialize the i2c sensors.
 */
  pilyt.init( &evshield, SH_BAS1 );

/**  Set timeout to save power
*/
  pilyt.setTimeout1(7);

/**  Wait until user presses GO button to continue the program
 */
  while (!evshield.getButtonState(BTN_GO)) {
    if (millis() % 1000 < 3) {
      Serial.println("Press GO button to continue");
    }
  }

}

#define DELAY_T 0

void loop()
{
  char aa[80];        
  char str[256];          //sets length of character string
  color mycolor;            //declares color variable
/**  Displays Firmeware Version of sensor
*/
  strcpy(aa, pilyt.getFirmwareVersion() );
  sprintf (str, "pilight: getFirmwareVersion: %s", aa);
  Serial.println(str);
/**  Displays Device ID of sensor
 */
  strcpy(aa, pilyt.getDeviceID() );
  sprintf (str, "pilight: DeviceID: %s", aa);
  Serial.println(str);
/**  Gets and displays Vendor ID of sensor
 */
  strcpy(aa, pilyt.getVendorID() );
  sprintf (str, "pilight: VendorID: %s", aa);
  Serial.println(str);
  delay(1000);
/**  Sets and Displays the color values
 */
  pilyt.createPiLight(25,0,0);          //red
  pilyt.readPiLight(mycolor);
  sprintf (str, "pilight: color      r:%d | g:%d | b:%d", mycolor.r, mycolor.g, mycolor.b);
  Serial.println(str); 
  delay(1000);
    
  pilyt.createPiLight(0,25,0);          //green
  pilyt.readPiLight(mycolor);
  sprintf (str, "pilight: color      r:%d | g:%d | b:%d", mycolor.r, mycolor.g, mycolor.b);
  Serial.println(str);
  delay(1000);  
 
  pilyt.createPiLight(0,0,25);          //blue
  pilyt.readPiLight(mycolor);
  sprintf (str, "pilight: color      r:%d | g:%d | b:%d", mycolor.r, mycolor.g, mycolor.b);
  Serial.println(str);
  Serial.println( "-------------" );
  delay(1000);   

}


