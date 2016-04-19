/* Arduino SoftI2cMaster Library
 * Copyright (C) 2009 by William Greiman
 * Modified by: Teja Chiluvuri
 *
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
#include "SoftI2cMaster.h"
const int BUFF_LEN = 16;
//------------------------------------------------------------------------------
// WARNING don't change anything unless you verify the change with a scope
//------------------------------------------------------------------------------
// set device address to begin
SoftI2cMaster::SoftI2cMaster(uint8_t devAddr){
  initialized = false;
  deviceAddr = devAddr;
  _so_buffer = (uint8_t*) calloc(BUFF_LEN, sizeof(uint8_t));
}
//------------------------------------------------------------------------------
// init pins and set bus high
void SoftI2cMaster::initProtocol(uint8_t sclPin, uint8_t sdaPin){
  if ( initialized ) return;

  if (!sclPin && !sdaPin){
   #if defined(__AVR__)
    #if defined(__AVR_ATmega168__) || defined(__AVR_ATmega8__) || defined(__AVR_ATmega328P__)
      sclPin_ = 19;   // A5
      sdaPin_ = 18;   // A4
    #else
      sclPin_ = 21;
      sdaPin_ = 20;
    #endif
#elif defined(__PIC32MX__)
     #if defined(_BOARD_UNO_)
     	 sclPin_ = 46;   // use SCL pin 
    	 sdaPin_ = 45;   // use SDA pin 
     #elif defined(_BOARD_MEGA_)
     	 sclPin_ = 21;
       sdaPin_ = 20;
     #endif

#endif
  }
  else {
    sclPin_ = sclPin;
    sdaPin_ = sdaPin;
  }
  digitalWrite(sclPin_, LOW);
  digitalWrite(sdaPin_, LOW);
  pinMode(sclPin_,INPUT);
  pinMode(sdaPin_,INPUT);
  initialized = true;
}
//------------------------------------------------------------------------------
// read a byte and send Ack if last is false else Nak to terminate read
uint8_t SoftI2cMaster::read(uint8_t last){
  uint8_t b = 0;
  // make sure pullup enabled
  pinMode(sdaPin_,INPUT);
  // read byte
  for (uint8_t i = 0; i < 8; i++) {
  // don't change this loop unless you verify the change with a scope
  b <<= 1;
  delayMicroseconds(I2C_DELAY_USEC);
  pinMode(sclPin_,INPUT);
  if (digitalRead(sdaPin_)) b |= 1;
  delayMicroseconds(I2C_DELAY_USEC);
  pinMode(sclPin_,OUTPUT);
  }
  // send Ack or Nak
  pinMode(sdaPin_, OUTPUT);
  if (last)  pinMode(sdaPin_, INPUT);
  delayMicroseconds(I2C_DELAY_USEC);
  pinMode(sclPin_,INPUT);
  delayMicroseconds(I2C_DELAY_USEC);
  pinMode(sclPin_,OUTPUT);
  pinMode(sdaPin_,INPUT);
  return b;
}
//------------------------------------------------------------------------------
// send new address and read/write with stop
uint8_t SoftI2cMaster::restart(uint8_t addressRW){
  uint8_t e;
  delayMicroseconds(I2C_DELAY_USEC);
  stop();
  delayMicroseconds(I2C_DELAY_USEC);
  pinMode(sclPin_,OUTPUT);
  delayMicroseconds(I2C_DELAY_USEC);
  pinMode(sclPin_,INPUT);
  delayMicroseconds(I2C_DELAY_USEC);
  e = start(addressRW);
  delayMicroseconds(I2C_DELAY_USEC);
  return e;
}
//------------------------------------------------------------------------------
// issue a start condition for i2c address with read/write bit
uint8_t SoftI2cMaster::start(uint8_t addressRW){
  pinMode(sdaPin_,OUTPUT);
  delayMicroseconds(I2C_DELAY_USEC);
  pinMode(sclPin_,OUTPUT);
  delayMicroseconds(I2C_DELAY_USEC);
  return write(addressRW);
}
//------------------------------------------------------------------------------
// issue a stop condition
void SoftI2cMaster::stop(void){
  delayMicroseconds(I2C_DELAY_USEC);
  pinMode(sclPin_,INPUT);
  delayMicroseconds(I2C_DELAY_USEC);
  pinMode(sdaPin_,INPUT);
  delayMicroseconds(I2C_DELAY_USEC);
}
//------------------------------------------------------------------------------
// write byte and return true for Ack or false for Nak
uint8_t SoftI2cMaster::write(uint8_t b){
  // write byte
  for (uint8_t m = 0X80; m != 0; m >>= 1) {
    if(m & b) pinMode(sdaPin_, INPUT);
    else pinMode(sdaPin_, OUTPUT);
    // don't change this loop unless you verify the change with a scope
    pinMode(sclPin_,INPUT);
    delayMicroseconds(I2C_DELAY_USEC);
    pinMode(sclPin_,OUTPUT);
    delayMicroseconds(I2C_DELAY_USEC);
  }
  // get Ack or Nak
  pinMode(sdaPin_,INPUT);
  pinMode(sdaPin_, INPUT);
  delayMicroseconds(I2C_DELAY_USEC);
  pinMode(sclPin_,INPUT);
  delayMicroseconds(I2C_DELAY_USEC);
  b = digitalRead(sdaPin_);
  pinMode(sclPin_,OUTPUT);
  delayMicroseconds(I2C_DELAY_USEC);
  pinMode(sdaPin_, OUTPUT);
  if ( b != 0 ) stop ();
  return b == 0;
}
//------------------------------------------------------------------------------
// read number of bytes from start register and return values; optional buffer
uint8_t* SoftI2cMaster::readRegisters(uint8_t startRegister, uint8_t bytes, uint8_t* buf){
  //delay(20);
  if (!buf)    buf = _so_buffer;
  bytes = min(bytes,BUFF_LEN);  // avoid buffer overflow
  memset(buf, 0, BUFF_LEN);
  _error_code = 0;
  // issue a start condition, send device address and write direction bit
  if (!start(deviceAddr | I2C_WRITE)) {
		_error_code = 2;
	  return false;
	}
  // send the start register address  
  if (!write(startRegister)) {
		_error_code = 1;
	  return false;
	}
  // issue a repeated stop and start condition, send device address and read direction bit  
  if (!restart(deviceAddr | I2C_READ)) {
		_error_code = 3;
	  return false;
	}
  // read data from the device and store into buffer  
  for (uint8_t i = 0; i < bytes; i++) {
    // send Ack until last byte then send Ack
    buf[i] = read(i == (bytes-1));
  }
  // issue a stop condition  
  stop();
  return buf;
}
//------------------------------------------------------------------------------
// write number of bytes from buffer, location is included in the buf
bool SoftI2cMaster::writeRegistersWithLocation(int bytes, uint8_t* buf){
  if (!start(deviceAddr | I2C_WRITE)) return false;
  for (int i = 0; i < bytes; i++){
    if (!write(buf[i]))  return false;
  }
  stop();
  return true;
}

//------------------------------------------------------------------------------
// write number of bytes from buffer at specified location.
bool SoftI2cMaster::writeRegisters  (uint8_t location, uint8_t bytes_to_write,
              uint8_t* buffer)
{
  if (!buffer) buffer = _so_buffer;

  uint8_t buf[BUFF_LEN];
  memset(buf, 0, BUFF_LEN);
  buf[0] = location;
  memmove(buf+1, buffer, bytes_to_write);
  return writeRegistersWithLocation(bytes_to_write+1, buf);
}

//------------------------------------------------------------------------------
// write a single byte at speccified location.
bool SoftI2cMaster::writeByte  (uint8_t location, uint8_t data)
{
  return writeRegisters(location, 1, &data);
}

//------------------------------------------------------------------------------
// write one integer (2 bytes) at speccified location.
bool SoftI2cMaster::writeInteger(uint8_t location, uint16_t data)
{
  uint8_t buf[2];
  buf[0] = data & 0xFF;
  buf[1] = (data >> 8) & 0xFF;
  return writeRegisters(location, 2, buf);
}

//------------------------------------------------------------------------------
// write one long (4 bytes) at speccified location.
bool SoftI2cMaster::writeLong  (uint8_t location, uint32_t data)
{
  uint8_t buf[4];

  buf[0] = data & 0xFF;
  buf[1] = (data >>  8) & 0xFF;
  buf[2] = (data >> 16) & 0xFF;
  buf[3] = (data >> 24) & 0xFF;
  return writeRegisters(location, 4, buf);
}

//------------------------------------------------------------------------------
// read string: convert read registers to character string
char* SoftI2cMaster::readString(uint8_t startRegister, uint8_t bytes,
                    uint8_t* buf, uint8_t len)
{
	char *x;
	x = (char *) readRegisters(startRegister, bytes, buf);
	if ( x == false ) {
	  return (char *) "";
	}
  return (char *) x;
}
//------------------------------------------------------------------------------
// read one byte, total of 8 bits
uint8_t SoftI2cMaster::readByte (uint8_t location){
  if ( readRegisters(location, 1) != false ) {
		return _so_buffer[0];
  } else {
	  return 0;
	}
}
//------------------------------------------------------------------------------
// read integer, total of 2 bytes or 16 bits
int16_t SoftI2cMaster::readInteger (uint8_t location){

  if ( readRegisters(location, 2) != false ) {
		return _so_buffer[0] | (_so_buffer[1] << 8);
  } else {
	  return 0;
	}
}
//------------------------------------------------------------------------------
// read long integer, total of 4 bytes or 32 bits
uint32_t SoftI2cMaster::readLong (uint8_t location){

  if ( readRegisters(location, 4) != false ) {
		return (uint32_t)_so_buffer[0] |
               (((uint32_t)_so_buffer[1]) << 8) |
               (((uint32_t)_so_buffer[2]) << 16) |
               (((uint32_t)_so_buffer[3]) << 24);
  } else {
	  return 0;
	}
}

// This is the status value returned from the last write command.
// A return value of zero indicates success.
// Non-zero results indicate failures.  From libraries/Wire/utility/twi.c, they are:
//                1: write fail
//                2: start fail
//                3: restart fail
uint8_t SoftI2cMaster::getWriteErrorCode()
{
  return _error_code;
}

//------------------------------------------------------------------------------
// get firmware version
char* SoftI2cMaster::getFirmwareVersion(){
  return readString(0x00, 8);
}
//------------------------------------------------------------------------------
// get vendor ID
char* SoftI2cMaster::getVendorID(){  
  return readString(0x08, 8);
}
//------------------------------------------------------------------------------
// get device ID
char* SoftI2cMaster::getDeviceID(){
  return readString(0x10, 8);
}
/**
 * this function checks to see if there is 
 * any device at its specified address 
 */
bool SoftI2cMaster::checkAddress()
{
// FIXME: This function is not working correctly.
  uint8_t *txBuffer;
  int8_t x = 1;
	if (!start(deviceAddr | I2C_WRITE)) return false;
	stop();
	return true;
}

bool SoftI2cMaster::setAddress(uint8_t address)
{
  deviceAddr = address;
  return true;
}
