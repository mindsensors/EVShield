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
#include <EVs_NXTMMX.h>

// setup for this example:
// attach NXTMMX to Port BAS1
// attach NXTMMX to M1
// attach Power to NXTMMX
// Open the Serial terminal to view.

//
// declare the EVShield(s) attached to your Arduino.
//
EVShield    evshield(0x34,0x36);
  byte forward = 1;
  byte reverse = 0;
  byte brake = 1;
  byte float1 = 0;
//
// declare the i2c devices used on EVShield(s).
//

EVs_NXTMMX  mmx  (0x06);

void setup()
{
  char str[256];

/**  Start serial for output
 */
  Serial.begin(115200);  // 

/**  Wait, allowing time to activate the serial monitor
 */ 
  delay(500); // wait, allowing time to activate the serial monitor

/**  Initialize the protocol for EVShield with Hardware I2C
 */
  evshield.init( SH_HardwareI2C );

/**  Initialize the i2c sensor(s).
 */
  mmx.init( &evshield, SH_BAS1 );
  mmx.stop(3, brake);			//Stop both motors

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
  byte motor1 = 1;
  byte motor2 = 2;
  byte motorboth = 3;
  byte speed = 100;
  byte direction = forward;
  long enc1;
  long enc2;
  int volt;
  
/**  Displays Firmware Version of sensor
*/
  strcpy(aa, mmx.getFirmwareVersion() );
  sprintf (str, "FirmwarVersion: %s", aa);
  Serial.println(str);
/**  Displays Device ID of sensor
 */
  strcpy(aa, mmx.getDeviceID() );
  sprintf (str, "Device ID: %s", aa); //Encoder value of motor 1
  Serial.println(str);
/**  Gets and displays Vendor ID of sensor
 */
  strcpy(aa, mmx.getVendorID() );
  sprintf (str, "VendorID: %s", aa);
  Serial.println(str);
/**  Displays Battery Voltage 
 */
  volt = mmx.getBatteryVoltage();
  sprintf (str, "Battery Voltage:   %d", volt);
  Serial.println(str);
/**  Displays Encoder value of motor 1
 */  
  enc1 = mmx.getEncoderPosition(motor1);
  sprintf (str, "Encoder 1:   %d",  enc1);
  Serial.println(str);
/**  Displays  Encoder value of motor 2
 */    
  enc2 = mmx.getEncoderPosition(motor2);
  sprintf (str, "Encoder 2:  %d",  enc2);
  Serial.println(str);

  mmx.runUnlimited(motor1, direction, speed);	//Run specified motor(s)
  delay(5000);					//Wait for some time.
  mmx.stop(motor1, brake);			//Stop the specified motor(s)
  
  Serial.println( "-------------" );
  delay (1500);
}


