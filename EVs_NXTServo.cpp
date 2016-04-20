
// EVs_NXTServo.cpp
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


#include "EVs_NXTServo.h"



EVs_NXTServo::EVs_NXTServo(uint8_t i2c_address)
: EVShieldI2C(i2c_address)
{
}

uint8_t EVs_NXTServo::getBatteryVoltage()
{
	return readByte(Servo_Voltage);
}

uint8_t EVs_NXTServo::issueCommand(char command)
{
	return writeByte(Servo_Command, (uint8_t)command);
}

bool EVs_NXTServo::storeInitial(uint8_t number)
{
	issueCommand('I');
	return issueCommand(number);
}
bool EVs_NXTServo::reset()
{
	return issueCommand('S');
}
bool EVs_NXTServo::haltMacro()
{
	return issueCommand('H');
}

bool EVs_NXTServo::resumeMacro()
{
	return issueCommand('R');
}

bool EVs_NXTServo::gotoEEPROM(uint8_t position)
{
	issueCommand('G');
	issueCommand(position);
}

bool EVs_NXTServo::editMacro()
{
	issueCommand('E');
	return issueCommand('m');
}

bool EVs_NXTServo::pauseMacro()
{
	return issueCommand('P');
}
bool EVs_NXTServo::setSpeed(uint8_t number, uint8_t speed)
{
	return writeByte((uint8_t) number, (uint8_t)speed);
}

bool EVs_NXTServo::setPosition(uint8_t number, uint8_t position)
{
	return writeByte((uint8_t) number, (uint8_t) position);
}

void EVs_NXTServo::runServo(uint8_t number,			    // Servo_1, 2, 3, ..., 8
						uint8_t position,			// [500,2500] Servo_Default
						uint8_t speed)		     	// [0, inf] or Speed_Full
{
	if (number == Servo_1) 
	{
	setPosition(Servo_Position_1, position);
	setSpeed(Servo_Speed_1, speed);
	}
	else if (number == Servo_2) 
	{
	setPosition(Servo_Position_2, position);
	setSpeed(Servo_Speed_2, speed);
	}
	else if (number == Servo_3) 
	{
	setPosition(Servo_Position_3, position);
	setSpeed(Servo_Speed_3, speed);
	}
	else if (number == Servo_4) 
	{
	setPosition(Servo_Position_4, position);
	setSpeed(Servo_Speed_4, speed);
	}
	else if (number == Servo_5) 
	{
	setPosition(Servo_Position_5, position);
	setSpeed(Servo_Speed_5, speed);
	}
	else if (number == Servo_6) 
	{
	setPosition(Servo_Position_6, position);
	setSpeed(Servo_Speed_6, speed);
	}
	else if (number == Servo_7) 
	{
	setPosition(Servo_Position_7, position);
	setSpeed(Servo_Speed_7, speed);
	}
	else if (number == Servo_8) 
	{
	setPosition(Servo_Position_8, position);
	setSpeed(Servo_Speed_8, speed);
	}
}
