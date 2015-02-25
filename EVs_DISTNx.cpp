
// EVs_DISTNx.cpp
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


#include "EVs_DISTNx.h"


EVs_DISTNx::EVs_DISTNx(uint8_t i2c_address)
: EVShieldI2C(i2c_address)
{
}
uint8_t EVs_DISTNx::issueCommand(char command)
{
	return writeByte(DISTNx_Command, (uint8_t)command);
}

bool EVs_DISTNx::energize()
{
	return issueCommand('E');
}

bool EVs_DISTNx::deEnergize()
{
	return issueCommand('D');
}

int EVs_DISTNx::getDist()
{
	return readInteger(DISTNx_Distance);
}

int EVs_DISTNx::getVolt()
{
	return readInteger(DISTNx_Voltage);
}

short EVs_DISTNx::getType()
{
	return readByte(DISTNx_SensorType);
}
