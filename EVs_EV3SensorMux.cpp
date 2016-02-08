//EVs_EV3SensorMux.cpp
//
// This is a class controlling the EV3SensorAdapter, made by Mindsensors.

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
 * History
 * ------------------------------------------------
 * Author        Date      Comments
 * Deepak        11/21/13  Initial Authoring.
 * Benjamin J.   12/15/15  modified for EVShield.
 */


#include	"EVs_EV3SensorMux.h"

EVs_EV3SensorMux::EVs_EV3SensorMux(uint8_t i2c_address)
 : EVShieldI2C(i2c_address)
{

}

uint8_t	EVs_EV3SensorMux::issueCommand(char command)
{
	return	writeByte(ESA_Command, (uint8_t) command);
}

byte	EVs_EV3SensorMux::getMode( )
{
    byte buf[17];
    readRegisters(0x52, 2, buf);
    return (buf[0]);
}

uint8_t	EVs_EV3SensorMux::setMode(char newMode)
{
	return writeByte(0x52, (uint8_t) newMode);
}

int	EVs_EV3SensorMux::readValue()
{
    byte buf[17];
    readRegisters(0x54, 2, buf);
    return (buf[0] + (buf[1]*0x100));
}

