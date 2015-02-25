// EVs_AbsoluteIMU.cpp
//
// This is a class for controlling the AbsoluteIMU Sensor made by Mindsensors.
// Seehttp://www.mindsensors.com/index.php?module=pagemaster&PAGE_user_op=view_page&PAGE_id=169

// Initial version: 2013-01-22 by Michael Giles
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

#include "EVs_AbsoluteIMU.h"


EVs_AbsoluteIMU::EVs_AbsoluteIMU(uint8_t i2c_address)
 : EVShieldI2C(i2c_address)
{

}

uint8_t	EVs_AbsoluteIMU::issueCommand(char command)
{
	return	writeByte(IMU_Command, (uint8_t) command);
}

void EVs_AbsoluteIMU::readGyro(gyro &currgyro)
{
	char *b;
	char str[200];
 	b = readString(0x53, 6);
	currgyro.gx = readIntFromBuffer((uint8_t *)&b[0]);
	currgyro.gy = readIntFromBuffer((uint8_t *)&b[2]);
	currgyro.gz = readIntFromBuffer((uint8_t *)&b[4]);
	currgyro.error = getErrorCode();
}

void EVs_AbsoluteIMU::readCompass(cmps &currcmps)
{
	char str[200];
 	currcmps.heading = readInteger(0x4b);
	currcmps.error = getErrorCode();
}

void EVs_AbsoluteIMU::readAccelerometer(accl &currAccl)
{
	char *b;
	char str[200];
 	currAccl.tx = readByte(0x42);
	currAccl.ty = readByte(0x43);
	currAccl.tz = readByte(0x44);
	b = readString(0x45, 6);
	currAccl.ax = readIntFromBuffer((uint8_t *)&b[0]);
	currAccl.ay = readIntFromBuffer((uint8_t *)&b[2]);
	currAccl.az = readIntFromBuffer((uint8_t *)&b[4]);
	currAccl.error = getErrorCode();
}
void EVs_AbsoluteIMU::readMagneticField(magnetic_field &currmagnetic_field)
{
	char *b;
	char str[200];
 	b = readString(0x4d, 6);
	currmagnetic_field.mx = readIntFromBuffer((uint8_t *)&b[0]);
	currmagnetic_field.my = readIntFromBuffer((uint8_t *)&b[2]);
	currmagnetic_field.mz = readIntFromBuffer((uint8_t *)&b[4]);
	currmagnetic_field.error = getErrorCode();
}
bool EVs_AbsoluteIMU::beginCompassCalibration()
{
	return issueCommand('C');
}
bool EVs_AbsoluteIMU::endCompassCalibration()
{
	return issueCommand('c');
}

