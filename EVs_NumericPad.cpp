// EVs_NumericPad.cpp
//
// This is a class for reading from NumericPad, made by Mindsensors.
// See http://www.mindsensors.com/index.php?module=pagemaster&PAGE_user_op=view_page&PAGE_id=138

// Initial version: 2011-07-19 by Michael Giles 
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


#include "EVs_NumericPad.h"
/*
byte Group1[] = {0x5C, 0x0B, 0x20};
byte Group2[] = {0x2B, 1, 1, 0, 0, 1, 1, 0xFF, 2};
byte Group3[] = {0x41, 15, 10, 15, 10, 15, 10, 15, 10, 15, 10, 15, 10, 15, 10, 15};
byte Group4[] = {0x50, 10, 15, 10, 15, 10, 15, 10, 15, 10, 15, 10};
byte Group5[] = {0x7D, 156, 101, 140, 0x0C};
*/
byte Group1[] = {0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0xFF, 0x02};
byte Group2[] = {0x0F, 0x0A, 0x0F, 0x0A, 0x0F, 0x0A, 0x0F, 0x0A, 0x0F};
byte Group3[] = {0x0A, 0x0F, 0x0A, 0x0F, 0x0A, 0x0F, 0x0A, 0x0F};
byte Group4[] = {0x0A, 0x0F, 0x0A, 0x0F, 0x0A, 0x0F, 0x0A, 0x0F};
byte Group5[] = {0x0b, 0x20, 0x0C};
byte Group6[] = {0x9C, 0x65, 0x8C};
byte waitPeriod = 1;
byte Group7[] = {0x0B};

char keyMap[] = { '4', '1', '7', '*', '5', '2', '8', '0', '3', '6', '9', '#' };

uint8_t KEY_STATUS_REG = 0x00;

EVs_NumericPad::EVs_NumericPad(uint8_t i2c_address)
: EVShieldI2C(i2c_address)
{
}

void EVs_NumericPad::InitializeKeypad() 
{
// the following sequence of bytes initialize the sensor's
// configuration for performance.

// This function must be called at the beginning of every power cycle
// (call it at the beginning of your program, after you initialize the port).

// Do not change the values below 
// Or the order in which these values are written.
  writeRegisters(0x41, 9, Group2);
  writeRegisters(0x4A, 8, Group3);
  writeRegisters(0x52, 8, Group4);
  writeRegisters(0x5C, 3, Group5);
  writeRegisters(0X2B, 8, Group1);
  writeRegisters(0x7B, 1, Group7);
  writeRegisters(0x7D, 3, Group6);
 
}



bool EVs_NumericPad::GetKeyPress(int waitPeriod/* seconds */, byte &keyHolder)
{
  uint8_t *regValue;
  int Touch;
  int Previous_Touch;
  int bit_test;
  int i, j;
  int w, cw;
  w = waitPeriod * 1000;

  cw = 0;  // cumulative wait
  while(true)
  {

	 Touch  = readInteger(KEY_STATUS_REG);
   int b;
   b = 0x01 << 11;

    if(Previous_Touch != Touch)
    {
      Previous_Touch = Touch;

        for ( j=0, i=0; j < 12; j++)
        {
          if ( Touch & b ) {
            keyHolder = keyMap[j];
            return true;
        }
        b = b >> 1;
      }
    }
    delay(150);
    cw += 150;
    if ( w != 0 && cw > w ) {
      return false;
    }
  }
  return false;
}

int EVs_NumericPad::GetKeysPressed ()
{   //Returns a 12bit number containing the status of all 12 keys.
  uint8_t buf[4];
  int result;
	result = readInteger(KEY_STATUS_REG);
  return result;
}





