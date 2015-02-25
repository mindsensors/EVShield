
// EVs_LineLeader.cpp
//
// This is a class for reading from LineLeader Sensor made by Openelectrons.com.
// See http://www.mindsensors.com/index.php?module=pagemaster&PAGE_user_op=view_page&PAGE_id=111

// Initial version: 2010-06-15 by Andrew Sylvester
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


#include "EVs_LineLeader.h"


EVs_LineLeader::EVs_LineLeader(uint8_t i2c_address)
: EVShieldI2C(i2c_address)
{
}

uint8_t EVs_LineLeader::issueCommand(char command)
{
	return writeByte(LineLeader_Command, (uint8_t)command);
}

bool EVs_LineLeader::calibrateWhite()
{
	return issueCommand('W');
}

bool EVs_LineLeader::calibrateBlack()
{
	return issueCommand('B');
}

bool EVs_LineLeader::sleep()
{
	return issueCommand('D');
}

bool EVs_LineLeader::wakeUp()
{
	return issueCommand('P');
}

bool EVs_LineLeader::invertLineColorToWhite()
{
	return issueCommand('I');
}

bool EVs_LineLeader::resetColorInversion()
{
	return issueCommand('R');
}

bool EVs_LineLeader::takeSnapshot()
{
	return issueCommand('S');
}

bool EVs_LineLeader::configureUS()
{
	return issueCommand('A');
}

bool EVs_LineLeader::configureEurope()
{
	return issueCommand('E');
}

bool EVs_LineLeader::configureUniversal()
{
	return issueCommand('U');
}

uint8_t EVs_LineLeader::getSetPoint()
{
	return readByte(LineLeader_SetPoint);
}

bool EVs_LineLeader::setSetPoint(uint8_t spoint)
{
	return writeByte(LineLeader_SetPoint, (uint8_t)spoint);
}

uint8_t EVs_LineLeader::getKp(uint8_t kp)
{
	return readByte(LineLeader_Kp);
}

bool EVs_LineLeader::setKp(uint8_t kp)
{
	return writeByte(LineLeader_Kp, (uint8_t)kp);
}

uint8_t EVs_LineLeader::getKi(uint8_t ki)
{
	return readByte(LineLeader_Ki);
}

bool EVs_LineLeader::setKi(uint8_t ki)
{
	return writeByte(LineLeader_Ki, (uint8_t)ki);
}

uint8_t EVs_LineLeader::getKd(uint8_t kd)
{
	return readByte(LineLeader_Kd);
}

bool EVs_LineLeader::setKd(uint8_t kd)
{
	return writeByte(LineLeader_Kd, (uint8_t)kd);
}

uint8_t EVs_LineLeader::getKpFactor(uint8_t kpfact)
{
	return readByte(LineLeader_Kp);
}

bool EVs_LineLeader::setKpFactor(uint8_t kpfact)
{
	return writeByte(LineLeader_Kp_Factor, (uint8_t)kpfact);
}

uint8_t EVs_LineLeader::getKiFactor(uint8_t kifact)
{
	return readByte(LineLeader_Ki);
}

bool EVs_LineLeader::setKiFactor(uint8_t kifact)
{
	return writeByte(LineLeader_Ki_Factor, (uint8_t)kifact);
}

uint8_t EVs_LineLeader::getKdFactor(uint8_t kdfact)
{
	return readByte(LineLeader_Kd);
}

bool EVs_LineLeader::setKdFactor(uint8_t kdfact)
{
	return writeByte(LineLeader_Kd_Factor, (uint8_t)kdfact);
}

int EVs_LineLeader::getSteering()
{
	return readByte(LineLeader_Steering);
}

unsigned char EVs_LineLeader::getAverage()
{
	return readByte(LineLeader_Average);
}

unsigned char EVs_LineLeader::getResult()
{
	return readByte(LineLeader_Result);
}

uint8_t* EVs_LineLeader::getRawCalibrated()
{
	return (uint8_t *) readString (LineLeader_Raw_Calibrated, 8);
}

uint8_t* EVs_LineLeader::getRawUncalibrated()
{
	return (uint8_t *) readString (LineLeader_Raw_Uncalibrated, 16);
}

uint8_t* EVs_LineLeader::getWhiteLimit()
{
	return (uint8_t *)readString (LineLeader_White_Limit, 8);
}

uint8_t* EVs_LineLeader::getBlackLimit()
{
	return (uint8_t *)readString (LineLeader_Black_Limit, 8);
}

uint8_t* EVs_LineLeader::getWhiteCalibration()
{
	return (uint8_t *)readString (LineLeader_White_Calibration, 8);
}

uint8_t* EVs_LineLeader::getBlackCalibration()
{
	return (uint8_t *)readString (LineLeader_Black_Calibration, 8);
}
