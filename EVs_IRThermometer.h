
// EVs_IRThermometer.h
//
// This is a class for reading from IRThermometer, made by Mindsensors.
// http://www.mindsensors.com/products/170-ir-temperature-sensor-for-ev3-or-nxt

// Initial version: 2010-06-10 by Andrew Sylvester
// Modified for EVShield: 2015-2-16 by Michael Giles
// Updated  for IRthermemometer 2017-10-17 by Nitin
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


#ifndef EVs_IRThermometer_H
#define EVs_IRThermometer_H

#define IRThermometer_Command      0x41
#define IRThermometer_Ambient_Temperature_C    0x42
#define IRThermometer_Target_Temperature_C    0x44
#define IRThermometer_Ambient_Temperature_F    0x46
#define IRThermometer_Target_Temperature_F    0x48


#include "EVShieldI2C.h"

/**
  @brief This class interfaces with IRThermometer attached to EVShield 
	*/
class EVs_IRThermometer : public EVShieldI2C
{
public:
	/** device constructor for IRThermometer; custom i2c address is an optional parameter */
  EVs_IRThermometer(uint8_t i2c_address = 0x2A);

	/** issue a byte command to the command register of the device */
  uint8_t    issueCommand(char command);
	
		
	/** get the Ambient Temperature  from the IRThermometer in Celsius*/
  float      getAmbientTemperatureC();
	
	/** get the Target Temperature  from the IRThermometer in Celsius*/
  float      getTargetTemperatureC();
	
	/** get the Ambient Temperature  from the IRThermometer in Fahrenheit*/
  float      getAmbientTemperatureF();
	
	/** get the Target Temperature  from the IRThermometer in Fahrenheit*/
  float      getTargetTemperatureF();

};

#endif
