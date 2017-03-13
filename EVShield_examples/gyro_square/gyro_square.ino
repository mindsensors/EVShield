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
#include <EVs_EV3Gyro.h>


// setup for this example:
// attach external power to evshield.
// attach EV3 Gyro Sensor to Port BBS2
// Open the Serial terminal to view.

//
//  Declare shield variable for this program
//
EVShield          evshield(0x34,0x36);

//
//  Declare our sensor for use in this program
//
EVs_EV3Gyro gyro1;

void
setup()
{
    char            str[50];

    Serial.begin(115200);       // start serial for output

    Serial.println ("------------------------");
    Serial.println ("Starting EV3 Gyro Square");
    Serial.println ("------------------------");

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
    gyro1.init( &evshield, SH_BBS2 );
    gyro1.setMode(MODE_Gyro_Angle);

    //
    // reset motors.
    //
    evshield.bank_a.motorReset();
    evshield.bank_b.motorReset();
    
    gyro1.setRef();
    
    //
    // Wait until user presses GO button to continue the program
    //
    while (!evshield.getButtonState(BTN_GO)) {
        if (millis() % 1000 < 3) {
            Serial.println("Press GO button to continue");
        }
    }
    
    sprintf(str, "Move Forward");
    Serial.println(str);
    str[0] = '\0';
    evshield.bank_a.motorRunRotations(SH_Motor_Both, 
                     SH_Direction_Reverse, 
                     SH_Speed_Medium,
                     1, 
                     SH_Completion_Wait_For,
                     SH_Next_Action_BrakeHold);
}

void
loop()
{
    uint8_t mode;
    int angle;
    char str[50];
    int i;
   
    gyro1.readAndPrint(0x81+gyro1.m_offset, 10);
    //
    // get the reading from sensor
    //
    angle = gyro1.getRefAngle();
    Serial.print("angle: "); Serial.println(angle);
    
    if (angle < 90){
      sprintf(str, "Turn Right Angle");
      Serial.println(str);
      str[0] = '\0';
      evshield.bank_a.motorRunUnlimited(SH_Motor_2, SH_Direction_Reverse, 1);
    }
    else{
      sprintf(str, "Stop");
        Serial.println(str);
        str[0] = '\0';
        evshield.bank_a.motorStop(SH_Motor_Both,SH_Next_Action_BrakeHold);
        Serial.println("Resetting Angle");
        gyro1.setRef();
        angle = gyro1.getRefAngle();
        Serial.print("angle: "); Serial.println(angle);
        
        sprintf(str, "Move Forward");
        Serial.println(str);
        str[0] = '\0';
        evshield.bank_a.motorRunRotations(SH_Motor_Both, 
                     SH_Direction_Reverse, 
                     SH_Speed_Medium,
                     1, 
                     SH_Completion_Wait_For,
                     SH_Next_Action_BrakeHold);
    }
    
    //
    // wait for some time
    //
    delay(100);
    
    // if the GO button is pressed, end the program
    if (evshield.getButtonState(BTN_GO)) {
        // reset the motors so the don't keep trying to move
        evshield.bank_a.motorReset();
        evshield.bank_b.motorReset();
        // indefinitely do nothing, until the reset button is pressed (on the Arduino) 
        while (1) ;
    }
}
