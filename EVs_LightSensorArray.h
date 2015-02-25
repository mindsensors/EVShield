
// EVs_LightSensorArray.h
//
// This is a class for reading from LightSensorArray made by Mindsensors.
// See http://www.mindsensors.com/index.php?module=pagemaster&PAGE_user_op=view_page&PAGE_id=168

// Initial version: 2013-01-25 by Michael Giles
// Modified for EVShield: 2015-02-16 by Michael Giles
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


#ifndef EVs_LightSensorArray_H
#define EVs_LightSensorArray_H

#define LightSensorArray_Calibrated    0x42
#define LightSensorArray_Uncalibrated    0x6A
#define LightSensorArray_White_Limit      0x4A
#define LightSensorArray_Black_Limit      0x52
#define LightSensorArray_White_Calibration  0x5A
#define LightSensorArray_Black_Calibration  0x62

#define LightSensorArray_Command          0x41

#include "EVShieldI2C.h"


  /** @brief This class interfaces with LightSensorArray attached to EVShield 
  */
class EVs_LightSensorArray : public EVShieldI2C
{
public:
  /** Class constructor for LightSensorArray; custom i2c address is an optional parameter */
  EVs_LightSensorArray(uint8_t i2c_address = 0x02);

  /** Write a command byte to the command register of the device */
  uint8_t issueCommand(char command);
  
  /** Calibrate the current input to the device as white */
  bool             calibrateWhite();
  
  /** Calibrate the current input to the device as black */
  bool             calibrateBlack();
  
  /** Turn off the LEDs on the device and put it in the sleep state */
  bool             sleep();
  
  /** Turn on the LEDs and wake up the device */
  bool             wakeUp();
  
  /** Configure Sensor for US region (and regions with 60 Hz electrical frequency). */
  bool             configureUS();
  
  /** Configure sensor for European region (and regions with 50 Hz electrical frequency). */
  bool             configureEurope();
  
  /** Configure sensor for universal frequency (in this mode the sensor adjusts for any frequency, this is also the default mode). */
  bool             configureUniversal();
  
  /** Get the raw readings from the sensor that is calibrated based on black and white calibration values
      @return  array of 8 bytes of the sensors' calibrated values. */
  uint8_t*         getCalibrated();
  
  /** Get the raw uncalibrated sensor values straight from the sensor 
      @return  array of 8 bytes of the sensors' uncalibrated values. */
  uint8_t*         getUncalibrated();
  
  /** Get the limit at which white changes to black */
  uint8_t*         getWhiteLimit();
  
  /** Get the limit at which black changes to white */
  uint8_t*         getBlackLimit();
  
  /** Calibrate White
      @return Current calibration of white */
  uint8_t*         getWhiteCalibration();
  
  /** Calibrate Black
      @return the current calibration of black */
  uint8_t*         getBlackCalibration();

};

#endif 
