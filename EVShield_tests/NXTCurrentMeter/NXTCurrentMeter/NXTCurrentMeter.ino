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
#include <EVs_NXTCurrentMeter.h>

// setup for this example:
// attach NXTCurrentMeter to Port BAS1
// Open the Serial terminal to view.

//
// declare the EVShield(s) attached to your Arduino.
//
EVShield    evshield(0x34,0x36);

//
// declare the i2c devices used on EVShield(s).
//

EVs_CurrentMeter  im  (0x28);

void setup()
{
  char str[256];
/**  Start serial for output
 */
  Serial.begin(115200);  // 
/**  Wait, allowing time to activate the serial monitor
 */ 
  delay(500); // wait, allowing time to activate the serial monitor


/**  Initialize the Hardware I2C protocol for EVShield
 */
  evshield.init( SH_HardwareI2C );

/**  Initialize the i2c sensors.
 */
  im.init( &evshield, SH_BAS1 );// Modified for EVShield: 2015-2-16 by Michael Giles

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
  char str[256];         //sets length of character string
  int  acurr;            //declares "acurr" variable 
  int  rcurr;            //declares "rcurr" variable 
  int  refI;             //declares "refI" variable
  
/**  Displays Firmeware Version of sensor
*/
  strcpy(aa, im.getFirmwareVersion() );
  sprintf (str, "IMeter: getFirmwareVersion: %s", aa);
  Serial.println(str);
/**  Displays Device ID of sensor
 */
  strcpy(aa, im.getDeviceID() );
  sprintf (str, "IMeter: DeviceID: %s", aa);
  Serial.println(str);
/**  Gets and displays Vendor ID of sensor
 */
  strcpy(aa, im.getVendorID() );
  sprintf (str, "IMeter: VendorID: %s", aa);
  Serial.println(str);
/**  Displays Absolute Current value
 */
  acurr = im.getACurrent();
  sprintf (str, "IMeter: Absolute Current:   %d", acurr);
  Serial.println(str);
/**  Displays Relative Current value
 */  
  rcurr = im.getRCurrent();
  sprintf (str, "IMeter: Relative Current:   %d",  rcurr);
  Serial.println(str);
/**  Displays Reference Current value
 */    
  refI = im.getReference();
  sprintf (str, "IMeter: Reference Current:  %d",  refI);
  Serial.println(str);
  
  Serial.println( "-------------" );
  delay (1500);
}


