
/*
 * EVShield interface library
 * Copyright (C) 2011 mindsensors.com
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


#ifndef EVs_SUMOEYES_H
#define EVs_SUMOEYES_H

#include "EVShieldAGS.h"

typedef enum {
  SE_None = 0,
	SE_Front,
	SE_Left,
	SE_Right
} SE_Zone;

/**
  @brief This class interfaces with EVTSumoEyes sensor attached to EVShield 
	*/
class EVs_SumoEyes : public EVShieldAGS
{
public:
	/** initialize the SumoEyes with a pointer to the EVShield and the bankport it is connected to */
	bool init(EVShield * shield, SH_BankPort bp);
	
	/** set the analog type of the sensor */
	bool setType(int8_t type);
	
	/** set the analog mode of the sensor to get readings for long range */
	bool setLongRange();
	
	/** set the analog mode of the sensor to get readings for short range */
	bool setShortRange();
	
	/** detect the where the obstacle is */
	SE_Zone detectObstacleZone();
	
	/** convert the detected zone to a readable string */
	char *OBZoneToString(SE_Zone ob);

private:
 bool isNear(int reference, int delta, int comet);

};

#endif


