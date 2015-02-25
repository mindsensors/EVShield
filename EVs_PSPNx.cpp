
// EVs_PSPNx.cpp
//
// This is a class for reading from PSP-Nx, made by Mindsensors.
// See http://www.mindsensors.com/index.php?module=pagemaster&PAGE_user_op=view_page&PAGE_id=61

// Initial version: 2010-06-15 by Andrew Sylvester
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


#include "EVs_PSPNx.h"


EVs_PSPNx::EVs_PSPNx(uint8_t i2c_address)
 : EVShieldI2C(i2c_address)
{
}

uint8_t EVs_PSPNx::issueCommand(char command)
{
  return writeByte(PSPNx_Command, (uint8_t)command);
}

bool EVs_PSPNx::energize()
{
  return issueCommand('R');
}

bool EVs_PSPNx::deEnergize()
{
  return issueCommand('S');
}

bool EVs_PSPNx::setDigitalMode()
{
  return issueCommand('A');
}

bool EVs_PSPNx::setAnalogMode()
{
  return issueCommand('s');
}

int8_t EVs_PSPNx::getXLJoy()
{
  int16_t a;
  int8_t b;
  a = readByte(PSPNx_XLeftJoystick);
  b = (((a - 128)*25) >> 5) & 0xFF;
  return b;
}
int8_t EVs_PSPNx::getYLJoy()
{
  int16_t a;
  int8_t b;
  a= readByte(PSPNx_YLeftJoystick);
  b = (((a - 128)*25) >> 5) & 0xFF;
  return b;
}
int8_t EVs_PSPNx::getXRJoy()
{
  int16_t a;
  int8_t b;
  a = readByte(PSPNx_XRightJoystick);
  b = (((a - 128)*25) >> 5) & 0xFF;
  return b;
}
int8_t EVs_PSPNx::getYRJoy()
{
  int16_t a;
  int8_t b;
  a = readByte(PSPNx_YRightJoystick);
  b = (((a - 128)*25) >> 5) & 0xFF;
  return b;
}

void EVs_PSPNx::getButtons(int8_t *buttons1, int8_t *buttons2)
{
  int8_t buf1, buf2;
  buf1 = readByte(PSPNx_ButtonSet1);
  buf2 = readByte(PSPNx_ButtonSet2);
  for (int i = 0; i < 8; i++) {
    buttons1[i]   =  buf1 >> i & 0x01;
    buttons2[i]   =  buf2 >> i & 0x01;
  }
}
