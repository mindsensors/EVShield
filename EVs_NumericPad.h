// EVs_NumericPad.h
//
// This is a class for reading from NumericPad, made by Mindsensors.
// See http://www.mindsensors.com/index.php?module=pagemaster&PAGE_user_op=view_page&PAGE_id=138

// Initial version: 2011-07-19 by Michael Giles
// Modified for EVShield: 2015-02-16 Michael Giles   
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


#ifndef  EVs_NumericPad_H
#define  EVs_NumericPad_H

#include "EVShieldI2C.h"

/**
  @brief This class interfaces with NumericPad attached to EVShield 
	*/
class EVs_NumericPad : public EVShieldI2C
{        
public:
  /** class constructor for the NumericPad with an optional custom i2c address parameter */
  EVs_NumericPad(uint8_t i2c_address = 0xB4);

  /** Initialize the keypad for communication with host.
    This function also sets up the capacitance values for
    the keypad with appropriate sensitiviy */
  void   InitializeKeypad();
  
  /** Get the key pressed on the keypad. 
    @param waitPeriod   how long to wait for user to press key (seconds).
    @param keyHolder    return value of the key user pressed in that time. 
    @return true        if there was a key pressed in specified time.
    @return false       if no key pressed in the specified time.
  */
  bool   GetKeyPress(int waitPeriod/* seconds */, byte &keyHolder);
  
  /** Get all the keys pressed by the user at the present moment
  function returns:
  integer value of all keys, each bit that is set to 1 represents a key that is pressed.
  the bits are set as per keyMap. Only 12 bits can be 1.
  */
  int  GetKeysPressed();

};

#endif /* EVs_NumericPad_H_ */
