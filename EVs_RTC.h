
// EVs_RTC.h
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


#ifndef EVs_RTC_H
#define EVs_RTC_H

#define RTC_Seconds      0x00
#define RTC_Minutes      0x01
#define RTC_Hours      0x02
#define RTC_Day_of_Week    0x03
#define RTC_Day_of_Month  0x04
#define RTC_Month      0x05
#define RTC_Year      0x06

#include "EVShieldI2C.h"

/**
  @brief This class interfaces with RTC attached to EVShield 
	*/
class EVs_RTC : public EVShieldI2C
{
public:
	/** class constructor of the RTC with an optional custom i2c address parameter */
  EVs_RTC(uint8_t i2c_address = 0xD0);
  
	/** get the current seconds reading of the clock (0-59) */
  uint8_t getSeconds();
	
	/** get the current minutes reading of the clock (0-59) */
  uint8_t getMinutes();
  
	/** get the current hours reading of the clock (1-24) */
	uint8_t getHours();
  
	/** get the current day of the week reading of the clock (0-7 starting on Sunday) */
	uint8_t getDayWeek();
  
	/** get the current day reading of the clock (1-31) */
	uint8_t getDayMonth();
  
	/** get the current month of the year reading of the clock (1-12) */
	uint8_t getMonth();
  
	/** get the current year reading of the clock */
	uint8_t getYear();

private:
  uint8_t BCDToInteger(uint8_t b);

};

#endif /* RTC_H_ */
