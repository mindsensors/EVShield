
// EVs_NXTThermometer.cpp
//
// This is a class for reading from DIST-Nx, made by Mindsensors.
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


#include "EVs_NXTThermometer.h"


EVs_NXTThermometer::EVs_NXTThermometer(uint8_t i2c_address)
: EVShieldI2C(i2c_address)
{
}
void EVs_NXTThermometer::setMode(void)
{
	writeByte(0x01, 0x60);
}

float EVs_NXTThermometer::getTemperature()
{
    int temp = readInteger(0x00);
    
    byte b1 = temp&0xff;
    byte b2 =  0xff&(temp>>8);
    temp =  (b1<<4)|(b2>>4);
	return 0.0625*(float)temp;
}




