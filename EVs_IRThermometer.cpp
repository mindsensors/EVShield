
// EVs_IRThermometer.cpp
//
// This is a class for reading from DIST-Nx, made by Mindsensors.
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


#include "EVs_IRThermometer.h"


EVs_IRThermometer::EVs_IRThermometer(uint8_t i2c_address)
: EVShieldI2C(i2c_address)
{
}
uint8_t EVs_IRThermometer::issueCommand(char command)
{
	return writeByte(IRThermometer_Command, (uint8_t)command);
}

float EVs_IRThermometer::getAmbientTemperatureC()
{
	return (float)readInteger(IRThermometer_Ambient_Temperature_C)/100.0;
}

float EVs_IRThermometer::getTargetTemperatureC()
{
	return (float)readInteger(IRThermometer_Target_Temperature_C)/100.0;
}

float EVs_IRThermometer::getAmbientTemperatureF()
{
	return (float)readInteger(IRThermometer_Ambient_Temperature_F)/100.0;
}

float EVs_IRThermometer::getTargetTemperatureF()
{
	return (float)readInteger(IRThermometer_Target_Temperature_F)/100.0;
}
