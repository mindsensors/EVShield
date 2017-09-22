// AbsoluteIMU.cpp
//
// This is a class for controlling the PiLight device made by OpenElectrons.com
// See http://www.openelectrons.com/pages/19

// Initial version: 2014-03-17 by Michael Giles
// Large parts of the code is ported from the Raspberry Pi library for the device,
// written by Nitin Patil.

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

#include "EVs_PiLight.h"


EVs_PiLight::EVs_PiLight(uint8_t i2c_address)
 : EVShieldI2C(i2c_address)
{

}

void EVs_PiLight::readPiLight(color &currcolor)
{
	char *b;
	char str[200];
 	b = readString(PILIGHT_RED, 3);
    currcolor.r = readIntFromBuffer((uint8_t *)&b[0]);
    currcolor.g = readIntFromBuffer((uint8_t *)&b[1]);
    currcolor.b = readIntFromBuffer((uint8_t *)&b[2]);    
}

void EVs_PiLight::setTimeout1(uint8_t timeoutValue)
{
	uint8_t null = 0;
    writeByteToBuffer(_buffer + 0, null);
    writeByteToBuffer(_buffer + 1, null);
    writeByteToBuffer(_buffer + 2, null);
    writeByteToBuffer(_buffer + 3, timeoutValue);
    writeRegisters(PILIGHT_RED, 4, _buffer);
}

void EVs_PiLight::createPiLight(uint8_t red, uint8_t green, uint8_t blue)
{
	writeByteToBuffer(_buffer + 0, red);
    writeByteToBuffer(_buffer + 1, green);
    writeByteToBuffer(_buffer + 2, blue);
    writeRegisters(PILIGHT_RED, 3, _buffer);
}

