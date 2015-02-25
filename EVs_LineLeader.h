
// EVs_LineLeader.h
//
// This is a class for reading from LineLeader Sensor made by Openelectrons.com.
// See http://www.mindsensors.com/index.php?module=pagemaster&PAGE_user_op=view_page&PAGE_id=111

// Initial version: 2010-06-15 by Andrew Sylvester
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


#ifndef EVs_LineLeader_H
#define EVs_LineLeader_H

#define LineLeader_Raw_Calibrated    0x49
#define LineLeader_Raw_Uncalibrated    0x74
#define LineLeader_White_Limit      0x51
#define LineLeader_Black_Limit      0x59
#define LineLeader_White_Calibration  0x64
#define LineLeader_Black_Calibration  0x6C


#define LineLeader_Command          0x41
#define LineLeader_Steering        0x42
#define LineLeader_Average          0x43
#define LineLeader_Result        0x44
#define LineLeader_SetPoint          0x45
#define LineLeader_Kp            0x46
#define LineLeader_Ki            0x47
#define LineLeader_Kd            0x48
#define LineLeader_Kp_Factor        0x61
#define LineLeader_Ki_Factor        0x62
#define LineLeader_Kd_Factor        0x63

#include "EVShieldI2C.h"

/**
  @brief This class interfaces with NXTLineLeader sensor attached to EVShield 
  */
class EVs_LineLeader : public EVShieldI2C
{
public:
  /** class constructor for LineLeader; custom i2c address is an optional parameter */
  EVs_LineLeader(uint8_t i2c_address = 0x02);

  /** write a command byte to the command register of the device */
  uint8_t issueCommand(char command);
  
  /** calibrate the current input to the device as white */
  bool             calibrateWhite();
  
  /** calibrate the current input to the device as black */
  bool             calibrateBlack();
  
  /** turn off the LEDs on the device and put it in the sleep state */
  bool             sleep();
  
  /** turn on the LEDs and wake up the device */
  bool             wakeUp();
  
  /** Color inversion (White line on a black background)
  */
  bool             invertLineColorToWhite();
  
  /** Reset Color inversion (black line on a white background, this is also the default).
  */
  bool             resetColorInversion();
  
  /**
Take a snapshot, this command looks at the line under the sensor and stores the width and position of the line in sensor’s memory. Subsequently, sensor will use these characteristics of line to track it. This command inverts the colors if it sees a white line on black background. (PID parameters are not affected).
  */
  bool             takeSnapshot();
  
  /** Configure Sensor for US region (and regions with 60 Hz electrical frequency).
  */
  bool             configureUS();
  
  /** Configure sensor for European region (and regions with 50 Hz electrical frequency)
  */
  bool             configureEurope();
  
  /** Configure sensor for universal frequency (in this mode the sensor adjusts for any frequency, this is also the default mode).
  */
  bool             configureUniversal();
  
  /** returns the current setpoint used by the PID control on the device */
  uint8_t          getSetPoint();
  
  /** set the desired point relative to the 8 sensors for PID control */
  bool              setSetPoint(uint8_t spoint);
  
  /** get the current proportion factor for PID control */
  uint8_t          getKp(uint8_t kp);
  
  /** set the proportion factor for PID control */
  bool             setKp(uint8_t kp);
  
  /** get the current integral factor for PID control */
  uint8_t          getKi(uint8_t ki);
  
  /** set the integral factor for PID control */
  bool             setKi(uint8_t ki);
  
  /** get the current derivative factor for PID control */
  uint8_t          getKd(uint8_t kd);
  
  /** set the derivative factor for PID control */
  bool             setKd(uint8_t kd);
  
  /**
	Get the Kp factor
	@return kp factor
	*/
  uint8_t          getKpFactor(uint8_t kpfact);
  
  /**
	Set the Kp factor
	*/
  bool             setKpFactor(uint8_t kpfact);
  
  /**
	Get the Ki factor
	@return ki factor
	*/
  uint8_t          getKiFactor(uint8_t kifact);
  
  /**
	Set the Ki factor
	*/
  bool             setKiFactor(uint8_t kifact);
  
  /**
	Get the Kd factor
	@return kd factor
	*/
  uint8_t          getKdFactor(uint8_t kdfact);
  
  /**
	Set the Kd factor
	*/
  bool             setKdFactor(uint8_t kdfact);
  
  /** current steering value, add or subtract from the speed of motors on each side */
  int              getSteering();
  
  /** returns a weighted average of the current position of the line in relation to the sensor */
  unsigned char    getAverage();
  
  /** returns a byte of the current result; each bit corresponds to one light sensor */
  unsigned char    getResult();
  
  /**
    get the raw readings from the sensor that is calibrated based on black and white calibration values
    @return  array of 8 bytes of the sensors' calibrated values.
  */
  uint8_t*         getRawCalibrated();
  
  /** get the raw uncalibrated sensor values straight from the sensor 
    @return  array of 8 bytes of the sensors' uncalibrated values.
	*/
  uint8_t*         getRawUncalibrated();
  
  /** get the limit at which white changes to black */
  uint8_t*         getWhiteLimit();
  
  /** get the limit at which black changes to white */
  uint8_t*         getBlackLimit();
  
  /** returns the current calibration of white */
  uint8_t*         getWhiteCalibration();
  
  /** returns the current calibration of black */
  uint8_t*         getBlackCalibration();

};

#endif /* LineLeader_H_ */
