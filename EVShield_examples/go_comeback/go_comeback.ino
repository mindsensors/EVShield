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

// setup for this example:
// attach external power to EVShield.
// attach 2 motors to motor ports on Bank A 
// Open the Serial terminal to view.

EVShield          evshield(0x34,0x36);

void
setup()
{
    Serial.begin(115200);       // start serial for output
    delay(2000);                // wait two seconds, allowing time to
                                // activate the serial monitor

    long            rotations = 6;  // Define variable rotations and set
                                    // equal to 90
    char            str[40];

    evshield.init( SH_HardwareI2C );

    //
    // Wait until user presses GO button to continue the program
    //
    while (!evshield.getButtonState(BTN_GO)) {
        if (millis() % 1000 < 3) {
            Serial.println("Press GO button to continue");
        }
    }

    //
    // reset motors.
    //
    evshield.bank_a.motorReset();
    evshield.bank_b.motorReset();


    // Drive motor 1 forward and backward for a specific number of
    // rotations
    sprintf(str, "Turn around");
    Serial.println(str);
    str[0] = '\0';
    evshield.bank_a.motorRunRotations(SH_Motor_1, 
                     SH_Direction_Reverse, 
                     SH_Speed_Medium,
                     2, 
                     SH_Completion_Wait_For,
                     SH_Next_Action_BrakeHold);
    
    delay(1000);
    Serial.println("Bank A motors >>");
    sprintf(str, "Run away", rotations);
    Serial.println(str);
    str[0] = '\0';
    evshield.bank_a.motorRunRotations(SH_Motor_Both, 
                     SH_Direction_Reverse, 
                     SH_Speed_Medium,
                     rotations, 
                     SH_Completion_Wait_For,
                     SH_Next_Action_BrakeHold);
    delay(1000);
    sprintf(str, "Turn around");
    Serial.println(str);
    str[0] = '\0';
    evshield.bank_a.motorRunRotations(SH_Motor_1, 
                     SH_Direction_Reverse, 
                     SH_Speed_Medium,
                     2, 
                     SH_Completion_Wait_For,
                     SH_Next_Action_BrakeHold);

    // Drive motor 2 forward and backward for a specific number of
    // rotations
    delay(1000);
    sprintf(str, "Come Back", rotations);
    Serial.println(str);
    str[0] = '\0';
    evshield.bank_a.motorRunRotations(SH_Motor_Both, 
                     SH_Direction_Reverse, 
                     SH_Speed_Medium,
                     rotations, 
                     SH_Completion_Wait_For,
                     SH_Next_Action_BrakeHold);
    delay(1000);
    
    //
    // we're done with the motors, reset them so they don't continue 
    // trying to hold their position (SH_Next_Action_BrakeHold)
    //
    evshield.bank_a.motorReset();
    evshield.bank_b.motorReset();
}

void
loop()                          // After the setup the LED blinks to show
                                // the program is complete
{
		evshield.ledSetRGB(255,0,0);     // light on the EVShield LED
    delay(1000);                // wait 
		evshield.ledSetRGB(0,0,0);     // turn off the EVShield LED.
    delay(1000);                // wait
}
