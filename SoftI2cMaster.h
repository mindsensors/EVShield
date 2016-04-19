/* Arduino SoftI2cMaster Library
 * Copyright (C) 2009 by William Greiman
 * Modified by: Teja Chiluvuri
 
 * This file is part of the Arduino SoftI2cMaster Library
 *
 * This Library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the Arduino SoftI2cMaster Library.  If not, see
 * <http://www.gnu.org/licenses/>.
 */
#ifndef SOFT_I2C_MASTER
#define SOFT_I2C_MASTER
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <stddef.h>

// delay used to tweek signals
#define I2C_DELAY_USEC 30

// R/W direction bit to OR with address for start or restart
#define I2C_READ 1
#define I2C_WRITE 0

/**
  @brief This class implements software i2c interface used by EVShield/NXShield on Arduino
	*/
class SoftI2cMaster {

	bool initialized;
private:
	uint8_t sclPin_;
	uint8_t sdaPin_;
	uint8_t deviceAddr;
	uint8_t _error_code;	// Error code 

public:
	/** internal buffer */
	uint8_t* _so_buffer;
	
	/** issue a start condition for i2c address with read/write bit */
	uint8_t start(uint8_t addressRW);

	/** issue a stop condition */
	void stop(void);
	
	/** issue stop condition, pull down scl, and start again */
	uint8_t restart(uint8_t addressRW);
	
	/** write byte and return true for Ack or false for Nak */
	uint8_t write(uint8_t b);

	/** read a byte and send Ack if last is false else Nak to terminate read */
	uint8_t read(uint8_t last);

	/** class constructor supplies the device address */
	SoftI2cMaster(uint8_t devAddr);
	
	/** init bus custom scl and sda pins are optional */
	void initProtocol(uint8_t sclPin = (uint8_t)NULL, uint8_t sdaPin = (uint8_t)NULL);
	
	/** read number of bytes from start register and return values; optional buffer */
	uint8_t* readRegisters(uint8_t startRegister, uint8_t bytes, uint8_t* buf = NULL);
	
	/** write number of bytes from buffer */
	bool writeRegistersWithLocation(int bytes, uint8_t* buf);
	
	/** write bytes starting at the specified register location */
  bool     writeRegisters  (uint8_t location, uint8_t bytes_to_write,
                uint8_t* buffer = 0);
  
	/** write one byte starting at the specified register location */
	bool     writeByte  (uint8_t location, uint8_t data);
	
	/** write integer starting at the specified register location */
  bool     writeInteger(uint8_t location, uint16_t data);
	
	/** write integer type long starting at the specified register location */
  bool     writeLong  (uint8_t location, uint32_t data);

	/** read specified number of bytes starting at the startRegister */
	char* readString(uint8_t startRegister, uint8_t bytes, uint8_t* buf = NULL, uint8_t len=0);
	
	/** read one byte starting at the location */
	uint8_t readByte	(uint8_t location);
	
	/** read two bytes and parse as an integer starting at the location */
	int16_t readInteger	(uint8_t location);
	
	/** read and parse as integer type long at the location */
	uint32_t readLong	(uint8_t location);

	/** get the version of the firmware */
	char*		getFirmwareVersion();
	
	/** get the name of the vendor */
	char*		getVendorID();
	
	/** get the name of the device */
	char*		getDeviceID();
	
	/** Get error of last i2c operation */
	uint8_t getWriteErrorCode();

	bool checkAddress();

	/** set the i2c address for this device 
	@param address new device address.
	*/
	bool setAddress(uint8_t address);
};
#endif //SOFT_I2C_MASTER
