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
#include <EVs_NumericPad.h>

// setup for this example:
// attach external power to EVShield.
// attach NumericPad to Port BAS1
// Open the Serial terminal to view.

//
// declare the EVShield(s) attached to your Arduino.
//
EVShield    evshield(0x34,0x36);

//
// declare the i2c devices used on EVShield(s).
//

EVs_NumericPad  np  (0xB4);

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
/**  Wait until user presses GO button to continue the program
 */
  Serial.println ("Press GO button to continue");
  evshield.waitForButtonPress(BTN_GO);
/**  Initialize the i2c sensors.
 */
  np.init( &evshield, SH_BAS1 );// Modified for EVShield: 2015-2-16 by Michael Giles
  np.InitializeKeyPad();
}

#define DELAY_T 0

void loop()
{
  char aa[80];        
  char str[256];         //sets length of character string 
  int  keys;            //declares "keys" variable 
  

/**  Displays Key(s)  pressed
 */  
  keys = np.GetKeysPressed();
  sprintf (str, "Keys Pressed:   %d",  keys);
  Serial.println(str);
  
  Serial.println( "-------------" );
  delay (1500);
}

' '
