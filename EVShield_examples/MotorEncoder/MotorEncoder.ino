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
http://www.mindsensors.com/pdfs/EVShield-Library-Tutorial.pdf
*/

#include <Wire.h>
#include <EVShield.h>

// setup for this example:
// attach EV3 motor to Bank A M1 port.
// Open the Serial terminal to view.

EVShield          evshield(0x34,0x36);
char str[200];

void
setup()
{
    Serial.begin(115200);       // start serial for output
    delay(2000);                // wait two seconds, allowing time to
                                // activate the serial monitor

    long            rotations = 2;  // Define variable rotations and set
                                    // equal to 90
    char            str[40];

    evshield.init( SH_HardwareI2C );

    //
    // Wait until user presses GO button to continue the program
    //
    Serial.println ("Turn the motor shaft to see changing encoder values.");
    Serial.println ("Press Left Arrow button to reset motor encoder.");
    Serial.println ("---------------------------");
    Serial.println ("Press GO button to continue");
    Serial.println ("---------------------------");
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


}

int32_t  new_encoder1, new_encoder2;

void
loop()
{
    new_encoder2 = evshield.bank_a.motorGetEncoderPosition(SH_Motor_2);
    new_encoder1 = evshield.bank_a.motorGetEncoderPosition(SH_Motor_1);
    sprintf (str, "encoder values: 1) %ld, 2) %ld", new_encoder1, new_encoder2);
    Serial.println (str);
    if ( evshield.getButtonState(BTN_LEFT) == true ) {
        Serial.println ("resetting encoders..");
        evshield.bank_a.motorResetEncoder(SH_Motor_1);
        evshield.bank_a.motorResetEncoder(SH_Motor_2);
    }

    delay(1000);
}

