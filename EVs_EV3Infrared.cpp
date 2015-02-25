
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

#include "EVs_EV3Infrared.h"

bool EVs_EV3Infrared::init(EVShield * shield, SH_BankPort bp)
{
    EVShieldUART::init(shield, bp);
    EVShieldUART::setType(SH_Type_EV3);
}

uint16_t EVs_EV3Infrared::readProximity()
{
    return readValue();
}

int8_t EVs_EV3Infrared::readChannelHeading(uint8_t channel)
{
    if ( channel < 0 || channel > 3) return -1;
    return readLocationByte((0x81+(channel*2)+m_offset) );
}

uint8_t EVs_EV3Infrared::readChannelProximity(uint8_t channel)
{
    if ( channel < 0 || channel > 3) return -1;
    return readLocationByte((0x82+(channel*2)+m_offset) );
}

uint8_t EVs_EV3Infrared::readChannelButton(uint8_t channel)
{
    if ( channel < 0 || channel > 3) return -1;
    return readLocationByte((0x82+(channel)+m_offset) );
}

