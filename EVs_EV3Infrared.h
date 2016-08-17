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

#ifndef EVs_EV3Infrared_H
#define EVs_EV3Infrared_H

#include "EVShieldUART.h"

/**
 * \enum MODE_Infrared, Modes supported by EV3 Infrared Sensor.
 */
typedef enum {
  MODE_Infrared_Proximity     = 0x00,   /*!< for measuring Proximity with EV3 Infrared sensor */
  MODE_Infrared_Beacon     = 0x01,   /*!< for measuring in Mode Beacon (returns 8 bytes values - 2 per channel) */
  MODE_Infrared_Remote     = 0x02   /*!< for Remote mode  */

} MODE_Infrared;

/**
  @brief This class interfaces with LEGO EV3 IR sensor attached to EVShield 
	*/
class EVs_EV3Infrared : public EVShieldUART
{
public:
	/** check if the touch sensor is pressed */
    bool init(EVShield * shield, SH_BankPort bp);


    /** for mode MODE_Infrared_Proximity */
    uint16_t readProximity();

    /** in mode: MODE_Infrared_Beacon  and MODE_InfraRed_Proximity */
    int8_t readChannelHeading(uint8_t channel);

    /** in mode: MODE_InfraRed_Proximity */
    uint8_t readChannelProximity(uint8_t channel);

    /** in mode MODE_Infrared_Remote */
    uint8_t readChannelButton(uint8_t channel);
};

#endif

