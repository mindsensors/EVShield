
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

#ifndef EVShieldI2C_H
#define EVShieldI2C_H

#include "SHDefines.h"
#include "BaseI2CDevice.h"
#include "SoftI2cMaster.h"

/**
  @brief This class implements I2C interfaces used by EVShield.
	*/
class EVShieldI2C : public BaseI2CDevice, public SoftI2cMaster
{
public:
	/** Pointer to the EVShield
	*/
  void * mp_shield;
	/** Pointer to internal i2c buffer
	*/
	uint8_t *_i2c_buffer;

public:
	/** Class constructor for the EVShieldI2C; derived from both BaseI2CDevice and SoftI2cMaster; i2c address must be passed as a parameter */
  EVShieldI2C(uint8_t i2c_address);
  
	/** global variable of the i2c protocol used */
	uint8_t m_protocol;

	/** initialized this i2c address with a pointer to the EVShield and the bankport it is connected to */
	void init(void * shield, SH_BankPort bp);
  
	/** Read a byte from specified location
	 @param location address to read at
	 @return  a byte value read from the location
	*/
  uint8_t  readByte  (uint8_t location);
  
	/** Read an integer from specified location. Integer comprises of 2 bytes.
	 @param location address to read at
	 @return  an integer value read from the location
	*/
	uint16_t readInteger  (uint8_t location);
	
	/** Read a long from specified location. Long comprises of 4 bytes.
	 @param location address to read at
	 @return  a long value read from the location
	*/
    uint32_t readLong  (uint8_t location);
	
	/** read the specified number of bytes from the buffer starting from the specified start register 
	 @param start_register location to start reading from
	 @param bytes Number of bytes to read
	 @param buf buffer to read the data into
	 @return the character array that was read.
	*/
	uint8_t*  readRegisters  (uint8_t  start_register, uint8_t  bytes, uint8_t* buf);

	/** Read a string from specified location
	 @param location address to read at
	 @param bytes_to_read  number of bytes to read
	 @param buffer optional, a buffer to read the data into.
	 @param buffer_length optional, length of the buffer supplied.
	 @return  a char array read from the location
	*/
  char*    readString  (uint8_t  location, uint8_t  bytes_to_read,
               uint8_t* buffer = 0, uint8_t  buffer_length = 0);

	/** write data bytes to the i2c device starting from the start register
	@param start_register location to write at.
	@param bytes_to_write Number of bytes to write
	@param buffer (optional) data buffer, if not supplied, data from internal buffer is used.
	*/
  bool     writeRegisters  (uint8_t start_register, uint8_t bytes_to_write,
                uint8_t* buffer = 0);

	/** write one byte to the specified register location
	@param location location to write to.
	@param data the data to write.
	*/
  bool     writeByte  (uint8_t location, uint8_t data);
  
	/** write two bytes (int) to the specified register location
	@param location location to write to.
	@param data the data to write.
	*/
	bool     writeInteger(uint8_t location, uint16_t data);
  
	/** write four bytes (long) to the specified register location 
	@param location location to write to.
	@param data the data to write.
	*/
	bool     writeLong  (uint8_t location, uint32_t data);

	/** get the firmware version of the device */
	char*		getFirmwareVersion();
	
	/** get the name of the vendor of the device */
	char*		getVendorID();
	
	/** get the name of the device */
	char*		getDeviceID();
	
	/** get the features the device is capable of; only supported by some devices */
	char*		getFeatureSet();

	/** get the error code of last i2c operation */
	uint8_t getErrorCode();

	bool checkAddress();

	/** set the i2c address for this device 
	@param address new device address.
	*/
    bool setAddress(uint8_t address);

};


#endif

