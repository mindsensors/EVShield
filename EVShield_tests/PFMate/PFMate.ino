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
#include <PFMate.h>

// setup for this example:
// attach PFMate to Port BAS1
// Open the Serial terminal to view.

//
// declare the EVShield(s) attached to your Arduino.
//
EVShield    evshield (0x34 ,0x36);

//
// declare the i2c devices used on EVShield(s).
//

PFMate pfmate (0x48);

void setup()
{
  char str[256];
/**  Start serial for output
 */
  Serial.begin(115200);  // 
/**  Wait, allowing time to activate the serial monitor
 */ 
  delay(500); // wait, allowing time to activate the serial monitor


/**  Initialize the Hardware I2C protocol for EVShield.
 */
  evshield.init( SH_HardwareI2C );

/**  Initialize the i2c sensors.
 */
  pfmate.init( &evshield, SH_BAS1 );

/**  Wait until user presses GO button to continue the program
 */
  Serial.println ("Press GO button to continue");
  evshield.waitForButtonPress(BTN_GO);

}

#define DELAY_T 0

void loop()
{
  char aa[80];        
  char str[256];          //sets length of character string
  uint8_t  result;
  char str2[20];          //sets length of character string 2
  char str3[20];          //sets length of character string 3 
  
/**  Displays Firmeware Version of sensor
*/
  strcpy(aa, pfmate.getFirmwareVersion() );
  sprintf (str, "pfmate: getFirmwareVersion: %s", aa);
  Serial.println(str);
/**  Displays Device ID of sensor
 */
  strcpy(aa, pfmate.getDeviceID() );
  sprintf (str, "pfmate: DeviceID: %s", aa);
  Serial.println(str);
/**  Gets and displays Vendor ID of sensor
 */
  strcpy(aa, pfmate.getVendorID() );
  sprintf (str, "pfmate: VendorID: %s", aa);
  Serial.println(str);
/**  Run motors at full speed
*/
  pfmate.controlMotor(PF_Channel_1, PF_Control_Both, PF_Operation_Forward, PF_Speed_Full);
  delay(2000);
/**  Stop motors 
*/
  pfmate.controlMotor(PF_Channel_1, PF_Control_Both, PF_Operation_Brake, PF_Speed_Full);
  delay(2000);
  
  Serial.println( "-------------" );
  delay (1500);
}


