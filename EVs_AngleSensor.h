
// EVs_AngleSensor.h
//
// This is a class for reading from AngelSensor, made by Mindsensors.
// See http://www.mindsensors.com/index.php?module=pagemaster&PAGE_user_op=view_page&PAGE_id=173

// Initial version: 2012-09-17 by Deepak Patil
// Modified for EVShield: 2015-02-16 Michael Giles

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


#ifndef EVs_ANGLE_SENSOR_H
#define EVs_ANGLE_SENSOR_H

#define AS_Command      0x41

#define ANGLE    0x42
#define RAW_READING    0x46

#include "EVShieldI2C.h"

	/**
 	 @brief This class 
 	 interfaces with sensor attached to EVShield 
	*/
class EVs_AngleSensor : public EVShieldI2C
{
public:
	/** Constructor for the class; may supply an optional custom i2c address 	*/
  EVs_AngleSensor(uint8_t i2c_address = 0x30);

	/** Write a command byte at the command register of the device */  
  uint8_t    issueCommand(char command);
	
	/** Get the angle position  
	 *  @return angle value*/
	long      getAngle();
  
	/** Get the raw reading from the device (twice the angle value) 
	 *  @return raw reading*/
	long      getRawReading();

	/** Reset the angle value to zero.
	 */
	void	  reset();
  
};

#endif
