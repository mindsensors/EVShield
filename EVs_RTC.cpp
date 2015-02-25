
// EVs_RTC.cpp
//
// This is a class for reading from Real-time Clock, made by Mindsensors.
// See http://www.mindsensors.com/index.php?module=pagemaster&PAGE_user_op=view_page&PAGE_id=101

// Initial version: 2010-06-10 by Andrew Sylvester
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


#include "EVs_RTC.h"


EVs_RTC::EVs_RTC(uint8_t i2c_address)
 : EVShieldI2C(i2c_address)
{
}

uint8_t EVs_RTC::BCDToInteger(uint8_t b)
{
  uint8_t i;
	i = (b&0x0F) + (((b>>4)&0x0F)*10);
	return i;
}

uint8_t EVs_RTC::getSeconds()
{
	return BCDToInteger(readByte(RTC_Seconds));
}

uint8_t EVs_RTC::getMinutes()
{
	return BCDToInteger(readByte(RTC_Minutes));
}

uint8_t EVs_RTC::getHours()
{
	return BCDToInteger(readByte(RTC_Hours));
}

uint8_t EVs_RTC::getDayWeek()
{
	return BCDToInteger(readByte(RTC_Day_of_Week));
}

uint8_t EVs_RTC::getDayMonth()
{
	return BCDToInteger(readByte(RTC_Day_of_Month));
}

uint8_t EVs_RTC::getMonth()
{
	return BCDToInteger(readByte(RTC_Month));
}

uint8_t EVs_RTC::getYear()
{
	return BCDToInteger(readByte(RTC_Year));
}
