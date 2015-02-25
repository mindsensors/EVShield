
// EVs_DISTNx.h
//
// This is a class for reading from DIST-Nx, made by Mindsensors.
// See http://www.mindsensors.com/index.php?module=pagemaster&PAGE_user_op=view_page&PAGE_id=73
// See http://www.mindsensors.com/index.php?module=pagemaster&PAGE_user_op=view_page&PAGE_id=72
// See http://www.mindsensors.com/index.php?module=pagemaster&PAGE_user_op=view_page&PAGE_id=69

// Initial version: 2010-06-10 by Andrew Sylvester
// Modified for EVShield: 2015-2-16 by Michael Giles
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


#ifndef EVs_DISTNx_H
#define EVs_DISTNx_H

#define DISTNx_Command      0x41
#define DISTNx_Distance    0x42
#define DISTNx_Voltage    0x44
#define DISTNx_SensorType  0x50

#include "EVShieldI2C.h"

/**
  @brief This class interfaces with DIST-Nx attached to EVShield 
	*/
class EVs_DISTNx : public EVShieldI2C
{
public:
	/** device constructor for DISTNx; custom i2c address is an optional parameter */
  EVs_DISTNx(uint8_t i2c_address = 0x02);

	/** issue a byte command to the command register of the device */
  uint8_t    issueCommand(char command);
	
	/** power on the device module */
  bool    energize();
	
	/** power off the device module */
  bool    deEnergize();
	
	/** get the distance of from the DISTNx in millimeters */
  int      getDist();
	
	/** get the output voltage of the sensor */
  int      getVolt();
	
	/** get the Sharp IR module type */
  short    getType();

};

#endif
