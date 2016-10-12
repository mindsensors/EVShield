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
// attach motor to BA M1
// Open the Serial terminal to view.
// follow instructions in serial terminal.

EVShield          evshield(0x34,0x36);

void
setup()
{
    Serial.begin(115200);       // start serial for output
    delay(2000);                // wait two seconds, allowing time to
                                // activate the serial monitor

    long            rotations = 2;  // Define variable rotations and set
                                    // equal to 90
    char            str[100];
    bool doExit = false;
    bool btnState = false;
    uint8_t regA, regB, status;
    char regAbin[20], regBbin[20], statusBin[20];

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


    // Drive motor 1 forward and backward for unlimited duration
    // rotations
    delay(1000);
    Serial.println("Press left button to stop");
    Serial.println("running Bank A motor 1 >>");
    evshield.bank_a.motorRunUnlimited(SH_Motor_1, SH_Direction_Forward, 75);

    while ( doExit == false ) {
        regA = evshield.bank_a.motorGetCommandRegA(SH_Motor_1);
        regB = evshield.bank_a.motorGetCommandRegB(SH_Motor_1);
        status = evshield.bank_a.motorGetStatusByte(SH_Motor_1);
        format_bin(regA, regAbin);
        format_bin(regB, regBbin);
        format_bin(status, statusBin);
        sprintf (str, "regA: %s, regB: %s, status: %s", regAbin, regBbin, statusBin);
        Serial.println (str);
        delay(100);
        // look if left button is pressed,
        // if yes, we should exit the program
        btnState = evshield.getButtonState(BTN_LEFT);
        if ( btnState == true ) doExit = true;
    }

    evshield.bank_a.motorStop(SH_Motor_1, SH_Next_Action_Float);
    Serial.println("Program Finished");

}

void
loop()                          // After the setup the LED blinks to show
                                // the program is complete
{
		evshield.ledSetRGB(8,0,0);     // light on the EVShield LED
    delay(1000);                // wait 
		evshield.ledSetRGB(0,0,0);     // turn off the EVShield LED.
    delay(1000);                // wait
}

