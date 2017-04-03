
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

  Modification history:
  Date      Author      reason
  12/24/14  Deepak      Initial development
*/

#include "EVShieldUART.h"

EVShieldUART::EVShieldUART()
{
    mp_shield = NULL;
}

EVShieldUART::EVShieldUART(EVShield * shield, SH_BankPort bp)
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
}

bool EVShieldUART::setType(uint8_t type)
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

bool EVShieldUART::writeLocation(uint8_t loc, uint8_t data)
{
    if ( mp_shield == NULL) return false;

    switch (m_bp) {
        case SH_BAS1:
        case SH_BAS2:
            return mp_shield->bank_a.writeByte(loc, data);

        case SH_BBS1:
        case SH_BBS2:
            return mp_shield->bank_b.writeByte(loc, data);

    }
}

int16_t EVShieldUART::readLocationInt(uint8_t loc)
{
    if ( mp_shield == NULL) return -1;

    switch (m_bp) {
        case SH_BAS1:
        case SH_BAS2:
            return mp_shield->bank_a.readInteger(loc);

        case SH_BBS1:
        case SH_BBS2:
            return mp_shield->bank_b.readInteger(loc);

    }
}

uint8_t EVShieldUART::readLocationByte(uint8_t loc)
{
    if ( mp_shield == NULL) return -1;

    switch (m_bp) {
        case SH_BAS1:
        case SH_BAS2:
            return mp_shield->bank_a.readByte(loc);

        case SH_BBS1:
        case SH_BBS2:
            return mp_shield->bank_b.readByte(loc);

    }
}

bool EVShieldUART::init(EVShield * shield, SH_BankPort bp)
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
    return true;
}

uint8_t	EVShieldUART::getMode( )
{
    if ( mp_shield == NULL) return -1;
    switch (m_bp) {
        case SH_BAS1:
        case SH_BAS2:
            return mp_shield->bank_a.readByte(0x81+m_offset);
        case SH_BBS1:
        case SH_BBS2:
            return mp_shield->bank_b.readByte(0x81+m_offset);
    }
}


uint8_t	EVShieldUART::setMode(char newMode)
{
    if ( mp_shield == NULL) return -1;
    switch (m_bp) {
        case SH_BAS1:
        case SH_BAS2:
            return mp_shield->bank_a.writeByte(0x81+m_offset, (uint8_t) newMode);
        case SH_BBS1:
        case SH_BBS2:
            return mp_shield->bank_b.writeByte(0x81+m_offset, (uint8_t) newMode);
    }
}

bool	EVShieldUART::isDeviceReady()
{
    if ( mp_shield == NULL) return false;
    switch (m_bp) {
        case SH_BAS1:
        case SH_BAS2:
            return (mp_shield->bank_a.readByte(0x70+m_offset) == 1);
        case SH_BBS1:
        case SH_BBS2:
            return (mp_shield->bank_b.readByte(0x70+m_offset) == 1);
    }

}


bool	EVShieldUART::readAndPrint(uint8_t loc, uint8_t len)
{
    uint8_t result;
    Serial.print(" ");
    for (int i=loc; i<loc+len; i++) {
        Serial.print (readLocationByte(i), DEC); Serial.print(" ");
    }
    //Serial.println("");
}


uint16_t	EVShieldUART::readValue()
{
    uint16_t result;
    result = readLocationInt(0x83+m_offset);
    return (result);
}
