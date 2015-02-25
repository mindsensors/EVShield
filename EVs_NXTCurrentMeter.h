//EVs_NXTCurrentMeter.h
//
// This is a class for reading from NXTCurrentMeter, made by Mindsensors.
// See http://www.mindsensors.com/index.php?module=pagemaster&PAGE_user_op=view_page&PAGE_id=163

// Initial version: 2013-01-24 by Michael Giles
// Modified for EVShield: 2015-2-16 by Michael Giles
// Large parts of the code is ported from the NXC library for the device,
// written by Deepak Patil.
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

#ifndef	EVs_NXTCurrentMeter_H
#define	EVs_NXTCurrentMeter_H

#define	IM_Command	0x41

#define	ABSOLUTE_I	0X43
#define	RELATIVE_I	0x45

#define	REFERENCE_I	0X47

#include	"EVShieldI2C.h"
	/** @brief This class 
 	  * interfaces with sensor attached to EVShield */
class EVs_CurrentMeter : public EVShieldI2C
{
public:
	/** Constructor for the class; may supply an optional custom i2c address 	*/
	EVs_CurrentMeter(uint8_t i2c_address = 0x28);
	/** Write a command byte at the command register of the device */  
	uint8_t	issueCommand(char command);
	/** Get the Absolute Current  
	 *  @return Absolute Current value*/
	int	getACurrent();
	/** Get the Relative Current  
	 *  @return Relative Current value*/
	int	getRCurrent();
	/** Get the Reference Current  
	 *  @return Reference Current value*/
	int	getReference();
	/** Set the Reference Current to Absolute Current */
	int	setReferenceI();

};

#endif
