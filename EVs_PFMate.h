
// EVs_PFMate.h
//
// This is a class for controlling the PF Motor Controller, made by Mindsensors.
// See http://www.mindsensors.com/index.php?module=pagemaster&PAGE_user_op=view_page&PAGE_id=107 .

// Initial version: 2010-06-17 by Andrew Sylvester
// Modified for EVShield: 2015-02-17 by Michael Giles
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


#ifndef EVs_PFMate_H
#define EVs_PFMate_H

#define PF_Commmand               0x41

#define PF_Channel                0x42
#define PF_Channel_1              1
#define PF_Channel_2              2
#define PF_Channel_3              3
#define PF_Channel_4              4

#define PF_Control                0x43
#define PF_Control_Both            0   
#define PF_Control_A               1
#define PF_Control_B               2

#define PF_Speed_A                0x45
#define PF_Speed_B                0x47
#define PF_Speed_Slow             1
#define PF_Speed_Medium           4
#define PF_Speed_Full             7

#define PF_Operation_A            0x44
#define PF_Operation_B            0x46
#define PF_Operation_Float        0
#define PF_Operation_Forward      1
#define PF_Operation_Reverse      2
#define PF_Operation_Brake        3

#include "EVShieldI2C.h"

/**
  @brief This class interfaces with PFMate attached to EVShield 
	*/
class EVs_PFMate : public EVShieldI2C
{
public:
	/** class constructor for PFMate with optional custom i2c address as a parameter */
	EVs_PFMate(uint8_t i2c_address = 0x48);

	/** issue char command byte to the command register of the PFMate */
	uint8_t		issueCommand(char command);
	
	/** send the data to the PF receiver */
	bool		sendSignal();
	
	/** control the PF motors on the channel the receiver is set to, which motors to control, the operation for the motors, and the speed to run them */
  void		controlMotor(uint8_t channel, uint8_t control, uint8_t operation, uint8_t speed);
	
	/** set which channel the PF receiver is on so the PFMate can talk with it */
	bool		setChannel(uint8_t channel);
	
	/** set which motor to control */
  bool		setControl(uint8_t control);
	
	/** set the operation of motor A */
	bool		setOperationA(uint8_t operation);
	
	/** set the operation of motor B */
	bool		setOperationB(uint8_t operation);
	
	/** set the speed of motor A */
	bool		setSpeedA(uint8_t speed);
	
	/** set the speed of motor B */
	bool		setSpeedB(uint8_t speed);
};

#endif
