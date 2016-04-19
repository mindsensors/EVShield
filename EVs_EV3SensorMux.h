//EVs_EV3SensorMux.h
//
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
*/
/*
 * History
 * ------------------------------------------------
 * Author         Date      Comments
 * Deepak         11/21/13  Initial Authoring.
 * Benjamin J.    12/15/15  modified for EVShield.
 */


#ifndef	EV3_SENSOR_MUX_H
#define	EV3_SENSOR_MUX_H

#define	ESA_Command	0x41

#include	"EVShieldI2C.h"
	/** @brief This class 
 	  * interfaces with sensor attached to NXShield */
class EVs_EV3SensorMux : public EVShieldI2C
{
public:
	/** Constructor for the class; may supply an optional custom i2c address 	*/
	EVs_EV3SensorMux(uint8_t i2c_address = 0x32);
	/** Write a command byte at the command register of the device */  
	uint8_t	issueCommand(char command);
	/** The EV3 sensors have different modes, you can change the mode of attached sensor with this function. To learn what all modes are availale, refer to LEGO's documentation */
    uint8_t	setMode(char newMode);
    /** it is possible to read back the mode that was set last time.
    use getMode to read the current mode */
    byte	getMode( );
    /** Read the value from the sensor attached to EVs_EV3SensorMux
    */
    int readValue();


};

#endif
