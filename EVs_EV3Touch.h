
/*
 * EVShield interface library
 * Copyright (C) 2015 mindsensors.com
 *
 * This file is part of EVShield interface library.
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

#ifndef EVs_EV3Touch_H
#define EVs_EV3Touch_H

#include "EVShieldUART.h"

/**
  @brief This class interfaces with LEGO EV3 Touch sensor attached to EVShield 
	*/
class EVs_EV3Touch : public EVShieldUART
{
public:
    /** initialize the interface and tell the shield where the sensor is connected */
    bool init(EVShield * shield, SH_BankPort bp);

	/** check if the touch sensor is pressed (or bumped) */
    bool isPressed();

    /** You can get bump count for EV3Touch Sensor (an incremental
     pressed value) this function will return the bump count since last reset.
     (The max value of bumpCount is 254, after that it will not increment).

     Programming Tip:
     If you don't want to wait to see if button is pressed, 
     use this bump count,
     store the old bumpCount in a variable and see if the new
     bumpCount is larger than the old value.
     */
    int  getBumpCount();

    /** reset the bump count and start the incremental bumps from zero */
    bool resetBumpCount();
};

#endif

