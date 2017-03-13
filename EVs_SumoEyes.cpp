
/*
 * EVShield interface library
 * Copyright (C) 2011 mindsensors.com
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

#include "EVs_SumoEyes.h"

bool EVs_SumoEyes::init(EVShield * shield, SH_BankPort bp)
{
  EVShieldAGS::init(shield, bp);
}
  

bool EVs_SumoEyes::setType(int8_t type)
{
  if ( mp_shield == NULL) return false;
  switch (m_bp) {
    case SH_BAS1:
      return mp_shield->bank_a.sensorSetType(SH_S1, type);
      
    case SH_BAS2:
      return mp_shield->bank_a.sensorSetType(SH_S2, type);
     
    case SH_BBS1:
      return mp_shield->bank_b.sensorSetType(SH_S1, type);
    
    case SH_BBS2:
      return mp_shield->bank_b.sensorSetType(SH_S2, type);
  
  }
}

bool EVs_SumoEyes::setShortRange()
{
  return setType( SH_Type_LIGHT_AMBIENT );
}

bool EVs_SumoEyes::setLongRange()
{
  return setType( SH_Type_LIGHT_REFLECTED );
}

bool EVs_SumoEyes::isNear(int reference, int delta, int comet)
{
  if ( (comet > (reference - delta))
    && (comet < (reference + delta)) ) {
       return true;
  }
  return false;
}

SE_Zone EVs_SumoEyes::detectObstacleZone()
{
  int se_value;
  
  se_value = readRaw();

  if ( isNear(830, 10, se_value) ) return SE_Front;
  if ( isNear(580, 10, se_value) ) return SE_Left;
  if ( isNear(487, 10, se_value) ) return SE_Right;

  return (SE_None);
}

char *EVs_SumoEyes::OBZoneToString(SE_Zone ob)
{
  switch (ob) {
    case SE_None:
    return (char *) "NONE";
    break;
    case SE_Front:
    return (char *) "FRONT";
    break;
    case SE_Left:
    return (char *) "LEFT";
    break;
    case SE_Right:
    return (char *) "RIGHT";
    break;
  }
}
