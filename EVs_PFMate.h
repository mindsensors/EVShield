
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
class EVs_PFMate : public EVShieldI2C {
public:
	/** 
	 * Class constructor for PFMate. 
	 * @param i2c_address Optional custom i2c address. 
	 */
	EVs_PFMate(uint8_t i2c_address = 0x48);

	/** 
	 * Issues char command byte to the command register of the PFMate.
	 * @param command The command to be issued.
	 */
	uint8_t issueCommand(char command);
	
	/** Sends the data to the PF receiver */
	bool sendSignal();
	
	/** 
	 * Controls the PF motors.
	 * @param channel   The channel the receiver is set to. Inputs: PF_Channel_1, 2, 3, or 4.
	 * @param control   Which motors to control. Inputs: F_Control_Both, A, or B.
	 * @param operation The operation for the motors. Inputs: PF_Operation_Forward, Reverse, Float, or Brake
	 * @param speed     The speed to run them. Inputs: [1, 7] or PF_Speed_Full, Medium, or Slow
	 */
	void controlMotor(uint8_t channel, uint8_t contorl, uint8_t operation, uint8_t speed);
	
	/** 
	 * Sets which channel the PF receiver is on, so the PFMate can talk with it.
	 * @param channel The channel the PF receiver is on.
	 */
	bool setChannel(uint8_t channel);
	
	/** 
	 * Sets which motor to control.
	 * @param control The motor to be controlled.
	 */
	bool setControl(uint8_t contol);
	
	/** 
	 * Sets the operation of motor A.
	 * @param operation The operation to be set.
	 */
	bool setOperationA(uint8_t operation);
	
	/** 
	 * Sets the operation of motor B.
	 * @param operation The operation to be set.*/
	bool setOperationB(uint8_t operation);
	
	/** 
	 * Sets the speed of motor A.
	 * @param speed The speed to be set.
	 */
	bool setSpeedA(uint8_t speed);
	
	/** 
	* Sets the speed of motor B.
	* @param speed The speed to be set.
	*/
	bool setSpeedB(uint8_t speed);
};

#endif
