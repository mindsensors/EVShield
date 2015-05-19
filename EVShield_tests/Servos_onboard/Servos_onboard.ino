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
#include <Servo.h>

// setup for this example:
// attach external power to EVShield.
// attach RC servo to any servo pin (pins are near Bank B-M1)
EVShield evshield(0x34,0x36);

//Create objects for each servo pin
Servo myservo3;
Servo myservo5;
Servo myservo6;
Servo myservo9;
Servo myservo10;
Servo myservo11;

int pos = 0;

void setup()   {  
  Serial.begin(115200);

//
//Initialze EVShield with Hardware I2C protocol.
//
  evshield.init(SH_HardwareI2C);

//Attach the servo objects to Arduino pins.
  myservo3.attach(3);
  myservo5.attach(5);
  myservo6.attach(6);
  myservo9.attach(9);
  myservo10.attach(10);
  myservo11.attach(11);
  
}

void loop()                     
{
  //Move all servos to maximum position
  pos = 255;
  myservo3.write(pos);    // tell servo to go to 'pos'
  myservo5.write(pos);    // tell servo to go to 'pos'
  myservo6.write(pos);   // tell servo to go to 'pos'
  myservo9.write(pos);    // tell servo to go to 'pos'
  myservo10.write(pos);    // tell servo to go to 'pos'
  myservo11.write(pos);   // tell servo to go to 'pos'

  delay(1000);

  //Move all servos to minimum position
  pos = 0;
  myservo3.write(pos);    // tell servo to go to 'pos'
  myservo5.write(pos);    // tell servo to go to 'pos'
  myservo6.write(pos);   // tell servo to go to 'pos'
  myservo9.write(pos);    // tell servo to go to 'pos'
  myservo10.write(pos);    // tell servo to go to 'pos'
  myservo11.write(pos);   // tell servo to go to 'pos'
  
  delay(1000);

}

