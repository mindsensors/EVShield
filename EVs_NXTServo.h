
// EVs_NXTServo.h
//
// This is a class for controlling the NXT Servo Controller, made by Mindsensors.
// See http://www.mindsensors.com/index.php?module=pagemaster&PAGE_user_op=view_page&PAGE_id=93 .

// Initial version: 2010-06-17 by Andrew Sylvester.
// Modified for EVShield: 2015-02-16 by Michael Giles
// Large parts of the code is ported from the NXC library for the device,
// written by Deepak Patil.

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

#ifndef EVs_NXTServo_H
#define EVs_NXTServo_H

#define Servo_Command        0x41
#define Servo_Voltage        0x41

#define Servo_1            1
#define Servo_2            2
#define Servo_3            3
#define Servo_4            4
#define Servo_5            5  
#define Servo_6            6  
#define Servo_7            7
#define Servo_8            8

#define Servo_Position_Default    1500
#define Servo_Speed_Full      0

#define Servo_Position_1      0x5A      
#define Servo_Position_2      0x5B  
#define Servo_Position_3      0x5C  
#define Servo_Position_4      0x5D  
#define Servo_Position_5      0x5E  
#define Servo_Position_6      0x5F  
#define Servo_Position_7      0x60  
#define Servo_Position_8      0x61

#define Servo_Speed_1        0x52      
#define Servo_Speed_2        0x53  
#define Servo_Speed_3        0x54  
#define Servo_Speed_4        0x55  
#define Servo_Speed_5        0x56  
#define Servo_Speed_6        0x57  
#define Servo_Speed_7        0x58  
#define Servo_Speed_8        0x59

#include "EVShieldI2C.h"

/**
  @brief This class interfaces with NXTServo attached to EVShield 
	*/
class EVs_NXTServo : public EVShieldI2C
{
public:
	/** class constructor for the NXTServo with optional custom i2c address parameter */
  EVs_NXTServo(uint8_t i2c_address = 0xb0);
  
	/** issue a character command byte to the command register of the NXTServo */
  uint8_t issueCommand(char command);
	
	/** get the battery voltage supplied to the NXTServo */
  uint8_t getBatteryVoltage();
	
	/** store current settings of the given servo to initial default setting and remember when powered on */
  bool storeInitial(uint8_t number);
	
	/** reset all servos to default */
  bool reset();
	
	/** stop the onboard macro on the NXTServo */
  bool haltMacro();
	
	/** resume the onboard macro on the NXTServo */
  bool resumeMacro();
	
	/** Go to given EEPROM position (This command re-initializes the macro environment) */
  bool gotoEEPROM(uint8_t position);
	
	/** edit the onboard macro */
  bool editMacro();
	
	/** temporarily pause the running macro */
  bool pauseMacro();
	
	/** set the speed of a specified servo */
  bool setSpeed(uint8_t number, uint8_t speed);
	
	/** set the position of a specified servo */
  bool setPosition(uint8_t number, uint8_t position);
	
	/** run the specified to the specified position at the specified speed */
  void runServo(uint8_t number, uint8_t position, uint8_t speed);

};

#endif
