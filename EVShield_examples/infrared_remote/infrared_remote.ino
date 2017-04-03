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
#include <EVShieldAGS.h>
#include <EVs_EV3Infrared.h>


// setup for this example:
// attach external power to evshield.
// attach EV3 Infrared Sensor to Port BBS2
// Open the Serial terminal to view.

//
//  Declare shield variable for this program
//
EVShield          evshield(0x34,0x36);

//
//  Declare our sensor for use in this program
//
EVs_EV3Infrared infra01;

void
setup()
{
    char            str[50];

    Serial.begin(115200);       // start serial for output

    Serial.println ("-------------------------------------------");
    Serial.println ("Starting EV3 Infrared Sensor Remote Control");
    Serial.println ("-------------------------------------------");

    //
    // initialize the shield i2c interface.
    //
    evshield.init( SH_HardwareI2C );

    //
    // red on bank a and
    // blue on bank b
    //
    evshield.bank_a.ledSetRGB(5,0,0);
    evshield.bank_b.ledSetRGB(0,0,5);

    //
    //  initialize the sensor, and tell where it is connected.
    //
    infra01.init( &evshield, SH_BBS2 );
    //infra01.setMode(MODE_Infrared_Proximity);
    //infra01.setMode(MODE_Infrared_Beacon);
    infra01.setMode(MODE_Infrared_Remote);
    
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
}



void
loop()
{
    uint8_t mode;
    uint8_t button;
    char str[50];
    int i;

    infra01.readAndPrint(0x81+infra01.m_offset, 10);
    //
    // get reading from the sensor and print
    //
    button = infra01.readChannelButton(1);
    Serial.print("Button Value: "); Serial.print(button);
    Serial.println ("");
    
    switch (button){
      case 1:
        // Drive motor 1 forward 
        sprintf(str, "Motor 1 Forward");
        Serial.println(str);
        str[0] = '\0';
        evshield.bank_a.motorRunUnlimited(SH_Motor_1, SH_Direction_Forward, SH_Speed_Medium);
        break;    
      case 2:
        // Drive motor 1 backward 
        sprintf(str, "Motor 1 Reverse");
        Serial.println(str);
        str[0] = '\0';
        evshield.bank_a.motorRunUnlimited(SH_Motor_1, SH_Direction_Reverse, SH_Speed_Medium);
        break;   
      case 3:
        // Drive motor 2 forward
        sprintf(str, "Motor 2 Forward");
        Serial.println(str);
        str[0] = '\0';
        evshield.bank_a.motorRunUnlimited(SH_Motor_2, SH_Direction_Forward, SH_Speed_Medium);
        break;    
      case 4:
        // Drive motor 2 backward
        sprintf(str, "Motor 2 Reverse");
        Serial.println(str);
        str[0] = '\0';
        evshield.bank_a.motorRunUnlimited(SH_Motor_2, SH_Direction_Reverse, SH_Speed_Medium);
        break;
      case 5:
        // Drive both motors forward 
        sprintf(str, "Both Motors Forward");
        Serial.println(str);
        str[0] = '\0';
        evshield.bank_a.motorRunUnlimited(SH_Motor_Both, SH_Direction_Forward, SH_Speed_Medium);
        break; 
     case 6:
        // Drive motor 1 forward motor 2 backward
        sprintf(str, "Motor 1 Forward, Motor 2 Reverse");
        Serial.println(str);
        str[0] = '\0';
        evshield.bank_a.motorRunUnlimited(SH_Motor_1, SH_Direction_Forward, SH_Speed_Medium); 
        evshield.bank_a.motorRunUnlimited(SH_Motor_2, SH_Direction_Reverse, SH_Speed_Medium);
        break;
      case 7:
        // Drive motor 1 backward motor 2 forward
        sprintf(str, "Motor 1 Reverse, Motor 2 Forward");
        Serial.println(str);
        str[0] = '\0';
        evshield.bank_a.motorRunUnlimited(SH_Motor_2, SH_Direction_Forward, SH_Speed_Medium);   
        evshield.bank_a.motorRunUnlimited(SH_Motor_1, SH_Direction_Reverse, SH_Speed_Medium);
        break;
      case 8:
        // Drive both motors backward 
        sprintf(str, "Both Motors Reverse");
        Serial.println(str);
        str[0] = '\0';
        evshield.bank_a.motorRunUnlimited(SH_Motor_Both, SH_Direction_Reverse, SH_Speed_Medium);
        break;
      default:
        // Stop both motors
        sprintf(str, "Stop Both Motors");
        Serial.println(str);
        str[0] = '\0';
        evshield.bank_a.motorStop(SH_Motor_Both, SH_Next_Action_BrakeHold);
        break;
    }
    //
    // wait for some time
    //
    //delay(500);
    
    // if the GO button is pressed, end the program
    if (evshield.getButtonState(BTN_GO)) {
        // reset the motors so the don't keep trying to run
        evshield.bank_a.motorReset();
        evshield.bank_b.motorReset();
        // indefinitely do nothing, until the reset button is pressed (on the Arduino) 
        while (1) ;
    }
}
