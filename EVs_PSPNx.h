
// EVs_PSPNx.h
//
// This is a class for reading from PSP-Nx, made by Mindsensors.
// See http://www.mindsensors.com/index.php?module=pagemaster&PAGE_user_op=view_page&PAGE_id=61

// Initial version: 2010-06-15 by Andrew Sylvester
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


#ifndef EVs_PSPNx_H
#define EVs_PSPNx_H

#define PSPNx_Command          0x41
#define PSPNx_ButtonSet1       0x42
#define PSPNx_ButtonSet2       0x43
#define PSPNx_XLeftJoystick    0x44
#define PSPNx_YLeftJoystick    0x45
#define PSPNx_XRightJoystick   0x46
#define PSPNx_YRightJoystick   0x47

#define BS2_Button_L2        0
#define BS2_Button_R2        1
#define BS2_Button_L1        2
#define BS2_Button_R1        3
#define BS2_Button_Triangle  4
#define BS2_Button_Circle    5
#define BS2_Button_Cross     6
#define BS2_Button_Square    7

#define BS1_Button_Select    0
#define BS1_Button_L3        1
#define BS1_Button_R3        2
#define BS1_Button_Start     3
#define BS1_Button_Up        4
#define BS1_Button_Right     5
#define BS1_Button_Down      6
#define BS1_Button_Left      7

#include "EVShieldI2C.h"

/**
  @brief This class interfaces with PSP-Nx attached to EVShield 
	*/
class EVs_PSPNx : public EVShieldI2C
{
public:
	/** class constructor for the EVs_PSPNx class with an optional custom i2c address parameter */
  EVs_PSPNx(uint8_t i2c_address = 0x02);

	/** issue a character command byte to the command register of the PSPNx */
  uint8_t     issueCommand(char command);
	
	/** power on the joystick receiver */
  bool        energize();
  
	/** power off the joystick receiver */
	bool        deEnergize();
  
	/** set the mode of the joystick to digital */
	bool        setDigitalMode();
	
	/** set the mode of the joystick to analog */
  bool        setAnalogMode();
  
	/** get the x-coordinate of the left joystick, 
	@return number between -100 and +100 and zero when the joystick is neutral.
	*/
	int8_t         getXLJoy();
  
	/** get the y-coordinate of the left joystick
	@return number between -100 and +100 and zero when the joystick is neutral.
	*/
	int8_t         getYLJoy();
  
	/** get the x-coordinate of the right joystick
	@return number between -100 and +100 and zero when the joystick is neutral.
	*/
	int8_t         getXRJoy();
  
	/** get the y-coordinate of the right joystick
	@return number between -100 and +100 and zero when the joystick is neutral.
	*/
	int8_t         getYRJoy();
	
	/** get the current button status of button set 1 and button set 2 */
  void        getButtons(int8_t *buttons1, int8_t *buttons2);

};

#endif
