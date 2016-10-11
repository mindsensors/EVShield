
/************************************************************************/
/* 
  Copyright (c) 2013 by mindsensors.com                                
Email: info (<at>) mindsensors (<dot>) com                          

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

#include <Wire.h>
#include <EVShield.h>
#include <EVs_EV3SensorMux.h>


EVShield    evshield;
EVs_EV3SensorMux esa1(0xA0);//setting esa to channel 1 on SensorMux
EVs_EV3SensorMux esa2(0xA2);//setting esa to channel 2 on SensorMux
EVs_EV3SensorMux esa3(0xA4);//setting esa to channel 3 on SensorMux

int inByte = 0;

void setup()
{
    char            str[80];

    Serial.begin(115200);       // start serial for output
    delay(500);                // wait, allowing time to
    // activate the serial monitor

    //
    // EVShield supports multiple transports
    // Initialize the transport for i2c devices.
    //
    evshield.init(SH_HardwareI2C);

    //
    // Wait until user presses GO button to continue the program
    //
    while (!evshield.getButtonState(BTN_GO)) {
        if (millis() % 1000 < 3) {
            Serial.println("Press GO button to continue");
        }
    }
    
    esa1.init( &evshield, SH_BAS1 ); // initializes sensor to correct port on EVshield
    esa2.init( &evshield, SH_BAS1 );
    esa3.init( &evshield, SH_BAS1 );
    
    esa1.setMode(0); //sets the initial mode for each sensor
    esa2.setMode(1);
    esa3.setMode(0);

}

void loop()
{
    char str[256];
    int  valueultra;
    int  valuegyro;
    int  valuelight;
    

    boolean left_btn = evshield.getButtonState(BTN_LEFT); //Press the left button on EVShield to change light sensor mode to 1
    if ( left_btn == true ) {
        Serial.println ( "changing mode to 1" );
        esa3.setMode(1);
    }

    boolean right_btn = evshield.getButtonState(BTN_RIGHT);//Press the right button on EVShield to change light sensor mode to 2
    if ( right_btn == true ) {
        Serial.println ( "changing mode to 2" );
        esa3.setMode(2);
    }


    valueultra = esa1.readValue();  //reads the sensor value from channel 1 and prints the data
    sprintf (str, "Ultrasonic: %d", valueultra);
    Serial.println ( str );


    valuegyro = esa2.readValue(); //reads the sensor value from channel 2 and prints the data
    sprintf (str, "gyro: %d", valuegyro);
    Serial.println ( str );
    

    valuelight = esa3.readValue(); //reads the sensor value from channel 3 and prints the data
    sprintf (str, "light: %d", valuelight);
    Serial.println ( str );

    Serial.println("");

    delay(300);

}

