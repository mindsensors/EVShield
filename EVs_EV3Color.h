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

#ifndef EVs_EV3Color_H
#define EVs_EV3Color_H

#include "EVShieldUART.h"

/**
 * \enum MODE_Color, Modes supported by EV3 Color (Color Sensor).
 */
typedef enum {
  MODE_Color_ReflectedLight     = 0x00,   /*!< Choose for measuring reflected light */
  MODE_Color_AmbientLight     = 0x01,   /*!< Choose for measuring ambient light */
  MODE_Color_MeasureColor   = 0x02,     /*!< Choose for measuring color*/ 
} MODE_Color;   

/**
  @brief This class interfaces with LEGO EV3 Color sensor attached to EVShield 
	*/
class EVs_EV3Color : public EVShieldUART
{
public:
    /** initialize the device and tell where it is connected */
    bool init(EVShield * shield, SH_BankPort bp);

    /** get the color value */
    float getVal();
};

#endif

