
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

#include "EVs_EV3Touch.h"

bool EVs_EV3Touch::init(EVShield * shield, SH_BankPort bp)
{
    EVShieldUART::init(shield, bp);
    EVShieldUART::setType(SH_Type_EV3_SWITCH);
}

bool EVs_EV3Touch::isPressed()
{
    return ( readLocationByte(0x83+m_offset) );
}

int  EVs_EV3Touch::getBumpCount()
{
    return (readLocationByte(0x84+m_offset));
}

bool  EVs_EV3Touch::resetBumpCount()
{
    return (writeLocation(0x84+m_offset, 0));
}

