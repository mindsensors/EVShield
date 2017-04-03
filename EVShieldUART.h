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

#ifndef EVShieldUART_H
#define EVShieldUART_H


#include "SHDefines.h"
#include "EVShield.h"

/**
  @brief EVShield UART Sensor class.
  also provides support for the EV3 Touch Sensor
 */
class EVShieldUART
{
    public:
        /** pointer to the EVShield class instantiation used */
        EVShield * mp_shield;

        /** bank port the analog device is connected to */
        SH_BankPort m_bp;

        /** the data for uart sensors is stored in the bank, and 
          there is a offset based on port */
        int m_offset;

        /** null constructor for the EVShieldUART class; need to init later */
        EVShieldUART();

        /** class constructor with pointer to EVShield and the bankport as a parameter; init is not needed */
        EVShieldUART(EVShield * shield, SH_BankPort bp);

        /** get the mode of the sensor */
        uint8_t	getMode( );

        /** When the device is initially connected (or type is changed) it takes a while for the sensor to negotiate UART communication with host and be ready to provide readings. This funciton will return True if the sensor is ready, False if it is not ready*/
        bool isDeviceReady();

        /** set the type of the device on this port of the EVShield */
        bool  setType(uint8_t type);

        /**  write a byte at the given location (selects appropriate bank) */
        bool writeLocation(uint8_t loc, uint8_t data);

        /** read integer value from specificed location */
        int16_t readLocationInt(uint8_t loc);

        /** read the value from the device at given location and return as an integer */
        uint8_t readLocationByte(uint8_t loc);

        /** initialize the analog device with a pointed to the EVShield and the bank port it is connected to */
        bool init(EVShield * shield, SH_BankPort bp);

        /** set mode of the sensor */
        uint8_t  setMode(char newMode);

        /** read sensor reading */
        uint16_t	readValue();

        /**  internal function to examine the buffer */
        bool	readAndPrint(uint8_t loc, uint8_t len);
};


#endif

