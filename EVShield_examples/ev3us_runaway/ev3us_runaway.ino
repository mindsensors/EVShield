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
//#include <EVShieldAGS.h>
#include <EVs_EV3Ultrasonic.h>


// setup for this example:
// attach external power to evshield.
// attach EV3 Ultrasonic Sensor to Port BAS1
// Open the Serial terminal to view.

//
//  Declare shield variable for this program
//
EVShield          evshield(0x34,0x36);

//
//  Declare our sensor for use in this program
//
EVs_EV3Ultrasonic us1;

void
setup()
{
    char            str[50];

    Serial.begin(115200);       // start serial for output

    Serial.println ("-----------------------------------------------");
    Serial.println ("Starting EV3 Ultrasonic Sensor Run Away Program");
    Serial.println ("-----------------------------------------------");

    //
    // initialize the shield i2c interface.
    //
    evshield.init( SH_HardwareI2C );
    //
    // reset motors.
    //
    evshield.bank_a.motorReset();
    evshield.bank_b.motorReset();


    //
    // red on bank a and
    // blue on bank b
    //
    evshield.bank_a.ledSetRGB(5,0,0);
    evshield.bank_b.ledSetRGB(0,0,5);

    //
    //  initialize the sensor, and tell where it is connected.
    //
    
    us1.init( &evshield, SH_BAS2);
    //us1.setMode(MODE_Sonar_Inches);
    us1.setMode(MODE_Sonar_CM);
      
    while (!evshield.getButtonState(BTN_GO)) {
        if (millis() % 1000 < 3) {
            Serial.println("Press GO button to continue");
        }
    }
    
    //
    // see if the sensor is pressed.
    // Drive motor 1 forward and backward for a specific number of
    // rotations
    sprintf(str, "Turn around");
    Serial.println(str);
    str[0] = '\0';
    evshield.bank_a.motorRunRotations(SH_Motor_1, 
                     SH_Direction_Reverse, 
                     SH_Speed_Slow,
                     2, 
                     SH_Completion_Wait_For,
                     SH_Next_Action_BrakeHold);
    
    delay(1000);
    Serial.println("Bank A motors >>");
    sprintf(str, "Run away");
    Serial.println(str);
    str[0] = '\0';
    evshield.bank_a.motorRunUnlimited(SH_Motor_Both, 
                     SH_Direction_Reverse, 
                     SH_Speed_Medium);
}

void
loop()
{
    uint8_t mode;
    float distance;
    char str[50];
    int i;

    //
    // see distance from sensor.
    //
    distance = us1.getDist();
    mode = us1.getMode();
    Serial.print(distance);
   
    if ( distance < 10 ) {
        //
        // power on the leds in Red color
        //
        Serial.println("Bank A motors >>");
        sprintf(str, "Stop");
        Serial.println(str);
        str[0] = '\0';
        evshield.bank_a.motorStop(SH_Motor_Both, 
                     SH_Next_Action_BrakeHold);
        evshield.ledSetRGB(10,0,0);
        Serial.println("Bank A motors >>");
        sprintf(str, "Stop");
        Serial.println(str);
        str[0] = '\0';
        evshield.bank_a.motorStop(SH_Motor_Both, 
                     SH_Next_Action_BrakeHold);
        delay(1000);
        evshield.ledSetRGB(10,0,0);
        sprintf(str, "Turn around");
        Serial.println(str);
        str[0] = '\0';
        evshield.bank_a.motorRunRotations(SH_Motor_Both, 
                     SH_Direction_Forward, 
                     SH_Speed_Medium,
                     1, 
                     SH_Completion_Wait_For,
                     SH_Next_Action_BrakeHold);
        evshield.bank_a.motorRunRotations(SH_Motor_1, 
                     SH_Direction_Forward, 
                     SH_Speed_Medium,
                     2, 
                     SH_Completion_Wait_For,
                     SH_Next_Action_BrakeHold);
        delay(1000);
        sprintf(str, "Come Back");
        Serial.println(str);
        str[0] = '\0';
        evshield.bank_a.motorRunRotations(SH_Motor_Both, 
                     SH_Direction_Reverse, 
                     SH_Speed_Medium,
                     5, 
                     SH_Completion_Wait_For,
                     SH_Next_Action_BrakeHold);
        delay(1000);
        char test = 1;
        while (test == 1){
            evshield.ledSetRGB(255,0,0);     // light on the EVShield LED
            delay(1000);                // wait 
            evshield.ledSetRGB(0,0,0);     // turn off the EVShield LED.
            delay(1000);               // wait
            test = 1;}
  } 
  else {
        //
        // turn off the leds
        //
        evshield.ledSetRGB(0,0,0);
    }
    //
    // wait for one second
    //
    
    // if the GO button is pressed, end the program
    if (evshield.getButtonState(BTN_GO)) {
        // reset the motors so the don't keep trying to run
        evshield.bank_a.motorReset();
        evshield.bank_b.motorReset();
        // indefinitely do nothing, until the reset button is pressed (on the Arduino) 
        while (1) ;
    }
}
