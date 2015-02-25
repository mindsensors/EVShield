/*
  Copyright (c) 2015 mindsensors.com
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

#include "EVs_NXTColor.h"


EVs_NXTColor::EVs_NXTColor()
{
    mp_shield = NULL;
}

EVs_NXTColor::EVs_NXTColor(EVShield * shield, SH_BankPort bp)
{
    mp_shield = shield;
    m_bp = bp;
    switch(m_bp) {
        case SH_BAS1:
        case SH_BBS1:
            m_offset = 0;
            break;
        case SH_BAS2:
        case SH_BBS2:
            m_offset = 52;
            break;
    }
    //setType(SH_Type_COLORFULL);
}

bool EVs_NXTColor::init(EVShield * shield, SH_BankPort bp)
{
    mp_shield = shield;
    m_bp = bp;
    switch(m_bp) {
        case SH_BAS1:
        case SH_BBS1:
            m_offset = 0;
            break;
        case SH_BAS2:
        case SH_BBS2:
            m_offset = 52;
            break;
    }
    //setType(SH_Type_COLORFULL);
    return true;
}

bool EVs_NXTColor::setType(uint8_t type)
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

uint8_t EVs_NXTColor::readValue()
{
    char str[100];
    uint8_t val;
    switch (m_bp) {
        case SH_BAS1:
        case SH_BAS2:
        val = (mp_shield->bank_a.readByte((0x70 + m_offset)));
        return (val*100)/255;
        case SH_BBS1:
        case SH_BBS2:
        val = (mp_shield->bank_b.readByte((0x70 + m_offset)));
        return (val*100)/255;
    }
}

uint8_t EVs_NXTColor::readColor()
{
    char str[100];
    uint8_t val;
    /*
    Serial.println("NXTColor::readValue: ");
    for (int i=0x70; i< 0x70+10;i++) {
        Serial.print(" "); Serial.print(mp_shield->bank_a.readByte(i));
    }
    Serial.println("");
    */
    switch (m_bp) {
        case SH_BAS1:
        case SH_BAS2:
        return (mp_shield->bank_a.readByte((0x70 + m_offset)));
        case SH_BBS1:
        case SH_BBS2:
        return (mp_shield->bank_b.readByte((0x70 + m_offset)));
    }
}
