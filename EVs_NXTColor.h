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

#ifndef EVs_NXTColor_H
#define EVs_NXTColor_H

#include "SHDefines.h"
#include "EVShield.h"

/**
  @brief EVShield Analog Sensor class.
 */
class EVs_NXTColor
{
    public:
        /** pointer to the EVShield class instantiation used */
        EVShield * mp_shield;

        /** bank port the device is connected to */
        SH_BankPort m_bp;

        /** the data for uart sensors is stored in the bank, and 
          there is a offset based on port */
        int m_offset;

        /** null constructor for the class; need to init later */
        EVs_NXTColor();

        /** class constructor with pointer to EVShield and the bankport as a parameter; if object is instantiated using this constructor, init is not needed */
        EVs_NXTColor(EVShield * shield, SH_BankPort bp);

        /** set the type of the device on this port of the EVShield */
        bool  setType(uint8_t type);

        /** read the raw analog value from the device and return as an integer */
        //int   readRaw();

        /** initialize the analog device with a pointer to the EVShield and the bank port it is connected to */
        bool init(EVShield * shield, SH_BankPort bp);

        uint8_t readValue();
        
        uint8_t readColor();
        
};


#endif

