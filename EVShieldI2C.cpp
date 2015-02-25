
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

#include "EVShieldI2C.h"
#include "EVShield.h"
//bool toggle2 = 0;

EVShieldI2C::EVShieldI2C(uint8_t i2c_address)
  : BaseI2CDevice(i2c_address), SoftI2cMaster(i2c_address)
{
}

uint8_t  EVShieldI2C::readByte  (uint8_t location)
{
  if (!m_protocol) return BaseI2CDevice::readByte( location );
  else             return SoftI2cMaster::readByte( location );
}


uint16_t EVShieldI2C::readInteger  (uint8_t location)
{
  if (!m_protocol) return BaseI2CDevice::readInteger( location );
  else             return SoftI2cMaster::readInteger( location );
}


uint32_t EVShieldI2C::readLong  (uint8_t location)
{
  if (!m_protocol) return BaseI2CDevice::readLong( location );
  else             return SoftI2cMaster::readLong( location );
}


uint8_t*  EVShieldI2C::readRegisters  (uint8_t  startRegister, uint8_t  bytes, uint8_t* buf)
{
  if (!m_protocol) return BaseI2CDevice::readRegisters(startRegister, bytes, buf);
	else             return SoftI2cMaster::readRegisters(startRegister, bytes, buf);
}


char*    EVShieldI2C::readString  (uint8_t  location, uint8_t  bytes_to_read,
            uint8_t* buffer, uint8_t  buffer_length)
{
  if (!m_protocol) return BaseI2CDevice::readString(location, bytes_to_read, buffer, buffer_length);
  else             return SoftI2cMaster::readString(location, bytes_to_read, buffer, buffer_length);
}


bool EVShieldI2C::writeRegisters  (uint8_t start_register, uint8_t bytes_to_write, uint8_t* buffer)
{
  if (!m_protocol) return BaseI2CDevice::writeRegisters(start_register, bytes_to_write, buffer);
  else             return SoftI2cMaster::writeRegisters(start_register, bytes_to_write, buffer);
}

bool EVShieldI2C::writeByte  (uint8_t location, uint8_t data)
{
    uint8_t dd[3];
    if (!m_protocol) {
        BaseI2CDevice::writeByte(location, data);
    } else {
        SoftI2cMaster::writeByte(location, data);
    }
    return true;
}

bool EVShieldI2C::writeInteger(uint8_t location, uint16_t data)
{
  if (!m_protocol) return BaseI2CDevice::writeInteger(location, data);
  else             return SoftI2cMaster::writeInteger(location, data);
}

bool EVShieldI2C::writeLong  (uint8_t location, uint32_t data)
{
  if (!m_protocol) return BaseI2CDevice::writeLong(location, data);
  else             return SoftI2cMaster::writeLong(location, data);
}

uint8_t EVShieldI2C::getErrorCode  ( )
{
  if (!m_protocol) return BaseI2CDevice::getWriteErrorCode();
  else             return SoftI2cMaster::getWriteErrorCode();
}

bool EVShieldI2C::checkAddress  ( )
{
  if (!m_protocol) return BaseI2CDevice::checkAddress();
  else             return SoftI2cMaster::checkAddress();
}

bool EVShieldI2C::setAddress  (uint8_t address)
{
    // regardless of protocol, set the address
  BaseI2CDevice::setAddress(address);
  SoftI2cMaster::setAddress(address);
	return true;
}


// READ INFORMATION OFF OF THE DEVICE
// returns a string with the current firmware version of the device
char* EVShieldI2C::getFirmwareVersion()
{
  return readString(0, 8);
}

// returns a string indicating the vendor of the device
char* EVShieldI2C::getVendorID()
{
  return readString(0x08, 8);
}

// returns a string indicating the device's ID
char* EVShieldI2C::getDeviceID()
{
  return readString(0x10, 8);
}
// returns a string indicating the features on this device
// some devices may return null.
char* EVShieldI2C::getFeatureSet()
{
  return readString(0x18, 8);
}

void EVShieldI2C::init(void * shield, SH_BankPort bp)
{
    mp_shield = shield;
    // on all banks hardware as well as software protocols are possible.
    // so store the main shield's protocol value with us.
    // and initialize with appropriate function
    //
    // For BAS2, BBS1, BBS2 only software i2c is possible.
    m_protocol = ((EVShield *)shield)->m_protocol;
    switch (m_protocol) {
        case SH_HardwareI2C:
            BaseI2CDevice::initProtocol ( );
            break;
        case SH_SoftwareI2C:
            SoftI2cMaster::initProtocol ( ); // no arguments, ie use default h/w i2c pins: (A5,A4)
            break;
    }
    switch (bp) {
        case SH_BAS1:
            ((EVShield *)shield)->bank_a.writeByte(SH_S1_MODE,SH_Type_I2C);
            break;
        case SH_BAS2:
            ((EVShield *)shield)->bank_a.writeByte(SH_S2_MODE,SH_Type_I2C);
            break;
        case SH_BBS1:
            ((EVShield *)shield)->bank_b.writeByte(SH_S1_MODE,SH_Type_I2C);
            break;
        case SH_BBS2:
            ((EVShield *)shield)->bank_b.writeByte(SH_S2_MODE,SH_Type_I2C);
            break;
    }
}