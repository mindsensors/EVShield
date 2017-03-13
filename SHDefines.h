/** \file SHDefines.h
* SHDefines.h defines global definitions and constants used by EVShield library.
*/

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

#ifndef SHDEFINES_H
#define SHDEFINES_H

#if defined(__AVR__)
  #if defined(__AVR_ATmega168__) || defined(__AVR_ATmega8__) || defined(__AVR_ATmega328P__) 
      #define MODEL_EVSHIELD_D
  #else
      #define MODEL_EVSHIELD_M
  #endif

#elif defined(__PIC32MX__)

  #if defined(_BOARD_UNO_) 
      #define MODEL_EVSHIELD_D
  #elif defined(_BOARD_MEGA_)
      #define MODEL_EVSHIELD_M
  #endif

#endif
#if defined(ARDUINO_ARC32_TOOLS)
  #define MODEL_EVSHIELD_D
#endif


/**
  \enum SH_BankPort for the sensor bank ports
*/
typedef enum {
  SH_BAS1 = 0x01,  /*!<  Bank A Sensor Port 1 */
  SH_BAS2 = 0x02,  /*!<  Bank A Sensor Port 2 */
  SH_BBS1 = 0x03,  /*!<  Bank B Sensor Port 1 */
  SH_BBS2 = 0x04   /*!<  Bank B Sensor Port 2 */
} SH_BankPort;

//! Protocols supported by EVShield.
/**
  \enum SH_Protocols Protocol enums - to initialize your EVShield with appropriate protocol.
*/
typedef enum {
  SH_HardwareI2C  = 0,  /*!< It's best to use hardware i2c as it is faster, (but it does not work with Ultrasonic Sensor). */
  SH_SoftwareI2C,  /*!< Software I2C is slower, and designed to work with Ultrasonic sensor.  */
} SH_Protocols;

#if defined(MODEL_EVSHIELD_D)
  // Arduino Duemilanove, Uno
  #define SCL_BAS1  A5
  #define SDA_BAS1  A4
  #define SCL_BAS2  2
  #define SDA_BAS2  A0
  #define SCL_BBS1  4
  #define SDA_BBS1  A1
  #define SCL_BBS2  7
  #define SDA_BBS2  A2

  // deepak
  #define BTN_RIGHT  4
  #define BTN_LEFT  1
  // deepak end

  #define BTN_GO  2
  #define LED_RED  8
  #define LED_GREEN  A3
  #define LED_BLUE  12

#else
  // Arduino mega, 2560
  #define SCL_BAS1  21
  #define SDA_BAS1  20
  #define SCL_BAS2  19
  #define SDA_BAS2  A13
  #define SCL_BBS1  17
  #define SDA_BBS1  A14
  #define SCL_BBS2  18
  #define SDA_BBS2  A15

  #define BTN_LEFT  16
  #define BTN_GO  15
  #define BTN_RIGHT 14
  #define LED_RED  16
  #define LED_GREEN  15
  #define LED_BLUE  14
  
#endif

#endif
