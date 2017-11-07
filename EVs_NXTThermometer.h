
// EVs_NXTThermometer.h
//
// This is a class for reading from NXTThermometer, made by Mindsensors.
// http://www.mindsensors.com/products/170-NXT-temperature-sensor-for-ev3-or-nxt

// Initial version: 2010-06-10 by Andrew Sylvester
// Modified for EVShield: 2015-2-16 by Michael Giles
// Updated  for NXTthermemometer 2017-10-17 by Nitin
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


#ifndef EVs_NXTThermometer_H
#define EVs_NXTThermometer_H

#define NXTThermometer_Command      0x41
#define NXTThermometer_Ambient_Temperature_C    0x42
#define NXTThermometer_Target_Temperature_C    0x44
#define NXTThermometer_Ambient_Temperature_F    0x46
#define NXTThermometer_Target_Temperature_F    0x48


#include "EVShieldI2C.h"

/**
  @brief This class interfaces with NXTThermometer attached to EVShield 
	*/
class EVs_NXTThermometer : public EVShieldI2C
{
public:
	/** device constructor for NXTThermometer; custom i2c address is an optional parameter */
  EVs_NXTThermometer(uint8_t i2c_address = 0x98);

	/** issue a byte command to the command register of the device */
  void    setMode(void);
	
		
	/** get the Ambient Temperature  from the NXTThermometer in Celsius*/
  float      getTemperature();
  
	
	

};

#endif
