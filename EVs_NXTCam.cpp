
// EVs_NXTCam.cpp
//
// This is a class for controlling the NXT Cam, made by Mindsensors.
// See http://www.mindsensors.com/index.php?module=pagemaster&PAGE_user_op=view_page&PAGE_id=78 .

// Initial version: 2010-06-18 by Andrew Sylvester
// Modified for EVShield: 2015-02-24 by Michael Giles
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


#include "EVs_NXTCam.h"


EVs_NXTCam::EVs_NXTCam(uint8_t i2c_address)
: EVShieldI2C(i2c_address)
{
}

uint8_t EVs_NXTCam::issueCommand(char command)
{
  return writeByte(Cam_Command, (uint8_t)command);
}

bool EVs_NXTCam::sortSize()
{
  return issueCommand('A');
}

bool EVs_NXTCam::selectObjectMode()
{
  return issueCommand('B');
}

bool EVs_NXTCam::writeImageRegisters()
{
  return issueCommand('C');
}

bool EVs_NXTCam::disableTracking()
{
  return issueCommand('D');
}

bool EVs_NXTCam::enableTracking()
{
  return issueCommand('E');
}

bool EVs_NXTCam::getColorMap()
{
  return issueCommand('G');
}

bool EVs_NXTCam::illuminationOn()
{
  return issueCommand('I');
}

bool EVs_NXTCam::readImageRegisters()
{
  return issueCommand('H');
}

bool EVs_NXTCam::selectLineMode()
{
  return issueCommand('L');
}

bool EVs_NXTCam::pingCam()
{
  return issueCommand('P');
}

bool EVs_NXTCam::resetCam()
{
  return issueCommand('R');
}

bool EVs_NXTCam::sendColorMap()
{
  return issueCommand('S');
}

bool EVs_NXTCam::illuminationOff()
{
  return issueCommand('T');
}

bool EVs_NXTCam::sortColor()
{
  return issueCommand('U');
}

bool EVs_NXTCam::camFirmware()
{
  return issueCommand('V');
}

bool EVs_NXTCam::sortNone()
{
  return issueCommand('X');
}  

int EVs_NXTCam::getNumberObjects()
{
  return readByte(Cam_Number_Objects);
}

void EVs_NXTCam::getBlobs(int *nblobs, uint8_t *color, uint8_t *left, uint8_t *top, uint8_t *right, uint8_t *bottom)
{
    *nblobs = readByte(Cam_Number_Objects);
  for (int i = 0; i < *nblobs; i++) {
    uint8_t* buf ;
    buf = (uint8_t *) readString (Start_Reg +(i*5), 5);
    color[i]  = buf[0] & 0x00FF;
    left[i]   = buf[1] & 0x00FF;
    top[i]    = buf[2] & 0x00FF;
    right[i]  = buf[3] & 0x00FF;
    bottom[i] = buf[4] & 0x00FF;
  }
}
