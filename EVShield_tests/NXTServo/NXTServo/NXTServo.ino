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
#include <EVs_NXTServo.h>

// setup for this example:
// attach NXTServo to Port BAS1
// Open the Serial terminal to view.

//
// declare the EVShield(s) attached to your Arduino.
//
EVShield    evshield(0x34,0x36);

//
// declare the i2c devices used on EVShield(s).
//

EVs_NXTServo  nservo  (0xB0);

void setup()
{
  char str[256];
/**  Start serial for output
 */
  Serial.begin(115200);
/**  Wait until the serial connection is established
 */ 
  while (!Serial) ;


/**  Initialize the protocol for EVShield with Hardware I2C
 */
  evshield.init( SH_HardwareI2C );

/**  Initialize the i2c sensor(s).
 */
  nservo.init( &evshield, SH_BAS1 );

/**  Reset all servos to default position and speed;
*/
  nservo.reset();

/**  Wait until user presses GO button to continue the program
 */
  Serial.println ("Press GO button to continue");
  evshield.waitForButtonPress(BTN_GO);


}

#define DELAY_T 0

void loop()
{
  char aa[80];        
  char str[256];         //sets length of character string
 
  
/**  Displays Firmware Version of sensor
*/
  strcpy(aa, nservo.getFirmwareVersion() );
  sprintf (str, "Firmware Version: %s", aa);
  Serial.println(str);
/**  Displays Device ID of sensor
 */
  strcpy(aa, nservo.getDeviceID() );
  sprintf (str, "Device ID: %s", aa);
  Serial.println(str);
/**  Gets and displays Vendor ID of sensor
 */
  strcpy(aa, nservo.getVendorID() );
  sprintf (str, "VendorID: %s", aa);
  Serial.println(str);

/**  Run servo 1 to maximum position with maximum speed
*/
  nservo.runServo(1, 250, 100);
  delay(1000);
/**  Run servo 1 to minimum position with maximum speed
*/
  nservo.runServo(1, 50, 100);
  delay(1000);

  
  Serial.println( "-------------" );
  delay (1500);
}


