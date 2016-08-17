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

#ifndef EVs_EV3Gyro_H
#define EVs_EV3Gyro_H

#include "EVShieldUART.h"

/**
 * \enum MODE_Sonar, Modes supported by EV3 Sonar (Ultrasonic Sensor).
 */
typedef enum {
  MODE_Gyro_Angle    = 0x00,   /*!< for Angle measurements */
  MODE_Gyro_Rate     = 0x01   /*!< for rate of change measurement */

} MODE_Gyro;

/**
  @brief This class interfaces with LEGO EV3 Gyro sensor attached to EVShield 
	*/
class EVs_EV3Gyro : public EVShieldUART
{
public:
    bool init(EVShield * shield, SH_BankPort bp);

    /** get the angle of the Gyro sensor */
    int getAngle();

    /** reset the angle to zero */
    int getRefAngle();

    /** reset the angle to zero */
    int setRef();
};
#endif
