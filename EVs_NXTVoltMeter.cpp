//EVs_NXTVoltMeter.cpp
//
// This is a class controlling the NXTVoltMeter, made by Mindsensors.
// See http://www.mindsensors.com/index.php?module=pagemaster&PAGE_user_op=view_page&PAGE_id=162

// Initial version: 2013-01-24 by Michael Giles
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

#include	"EVs_NXTVoltMeter.h"

EVs_VoltMeter::EVs_VoltMeter(uint8_t i2c_address)
 : EVShieldI2C(i2c_address)
{
	
}

uint8_t	EVs_VoltMeter::issueCommand(char command)
{
	return	writeByte(VM_Command, (uint8_t) command);
}

int	EVs_VoltMeter::getAVoltage()
{
	return	readInteger(ABSOLUTE_V); 
}

int	EVs_VoltMeter::getRVoltage()
{
	return	readInteger(RELATIVE_V);
}

int	EVs_VoltMeter::getReference()
{
	return	readInteger(REFERENCE_V);
}

int	EVs_VoltMeter::setReferenceV()
{
	return	issueCommand('d');
}

