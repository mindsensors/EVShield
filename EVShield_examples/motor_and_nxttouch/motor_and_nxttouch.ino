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
#include <EVs_NXTTouch.h>


// setup for this example:
// attach external power to EVShield.
// attach a touch sensor to BBS1
// attach motors to motor ports (any number of motors is fine).
// Open the Serial terminal to view.

//
// declare the EVShield(s) attached to your Arduino.
//
EVShield    evshield(0x34,0x36);

//
// declare the i2c devices used on EVShield(s).
//

//
// declare analog devices attached to evshields.
//
EVs_NXTTouch    touch1;

void setup()
{
  char str[256];

  Serial.begin(115200);  // start serial for output
  delay(500); // wait, allowing time to activate the serial monitor

  Serial.println ("Initializing the devices ...");
  //
  // EVShield provides multiple protocols
  // Initialize the protocol for EVShield
  // It is best to use Hardware I2C (unless you want to use Ultrasonic).
  //
  //evshield.init( SH_SoftwareI2C );
  evshield.init(); // the default is SH_HardwareI2C

  //
  // Wait until user presses GO button to continue the program
  //
  while (!evshield.getButtonState(BTN_GO)) {
    if (millis() % 1000 < 3) {
      Serial.println("Press GO button to continue");
    }
  }

  //
  // Initialize the i2c sensors.
  //

  // initialize the analog sensors.
  touch1.init( &evshield, SH_BBS1 );

  //
  // reset motors.
  //
  evshield.bank_a.motorReset();
  evshield.bank_b.motorReset();

}


void loop()
{
  char aa[80];
  int a;
  char str[256];
  bool touch_status;
  bool last_status;

  while (true) {  

    //
    //  run the motor if touch sensor is pressed.
    //


    a = touch1.readRaw();
  

    touch_status = touch1.isPressed();
		sprintf (str, "touch1: is pressed : %s", touch_status?"true":"false");
		Serial.println(str);
		//if ( 1 ) {
    if ( touch_status != last_status ) {
      if ( touch_status ) {
        Serial.println( "run unlimited" );
        evshield.bank_b.motorRunUnlimited(SH_Motor_1, SH_Direction_Forward, 50);
        evshield.bank_b.motorRunUnlimited(SH_Motor_2, SH_Direction_Forward, 50);
        evshield.bank_a.motorRunUnlimited(SH_Motor_1, SH_Direction_Forward, 50);
        evshield.bank_a.motorRunUnlimited(SH_Motor_2, SH_Direction_Forward, 50);
      } else {
        Serial.println( "stop (float)");
        evshield.bank_b.motorStop(SH_Motor_1, SH_Next_Action_Float);
        evshield.bank_b.motorStop(SH_Motor_2, SH_Next_Action_Float);
        evshield.bank_a.motorStop(SH_Motor_1, SH_Next_Action_Float);
        evshield.bank_a.motorStop(SH_Motor_2, SH_Next_Action_Float);
      }
		  last_status = touch_status;
    }

    delay (500);
  }
}
