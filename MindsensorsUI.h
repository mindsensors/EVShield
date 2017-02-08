/*
 * EVShield interface library
 * Copyright (C) 2017 mindsensors.com
 *
 * This file is part of EVShield interface library.
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.

 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef MINDSENSORSUI_H
#define MINDSENSORSUI_H

#include "EVShieldI2C.h"
#include "Adafruit_ILI9341.h"

// Touchscreen X-axis Raw Register.
#define SH_PS_TS_RAWX  0xE7
// Touchscreen Y-axis Raw Register.
#define SH_PS_TS_RAWY  0xE9

// Touchscreen calibration
#define SH_PS_TS_CALIBRATION_DATA_READY 0x70
#define SH_PS_TS_CALIBRATION_DATA 0x71

// I2C commands for manipulating touchscreen calibration values
#define SH_PS_TS_SAVE 0x77 // copy from temporary memory to permanent memory
#define SH_PS_TS_LOAD 0x6C // copy from permanent memory to temporary memory
#define SH_PS_TS_UNLOCK 0x45 // unlock permanent memory


/**
  @brief This class provides basic functions for the PiStorms touchscreen.
  
  MindsensorsUI inherits most all of its drawing functions from the Adafruit GFX library
  (through Adafruit_ILI9341). The primary purpose of this class is to add touchscreen
  functionality. It will load the touchscreen calibration values from the device
  and use those to calculate touch points.
  */
class MindsensorsUI : public Adafruit_ILI9341
{

private:
  EVShieldI2C i2c;
  
  /** touchscreen calibration values */
  uint16_t x1, y1, x2, y2, x3, y3, x4, y4;
  
  /** how close two consecutive touchscreen readings must be to be considered accurate */
  const uint8_t tolerance;
  
  /** read the raw x-coordinate of the touchscreen press */
  uint16_t RAW_X();
  
  /** read the raw x-coordinate of the touchscreen press */
  uint16_t RAW_Y();
  
  /** get raw touchscreen values, do some math using the calibration values, and write to the output parameters
    @param[out] x x-value of touchscreen press is written to this variable
    @param[out] y y-value of touchscreen press is written to this variable
  */
  void getReading(uint16_t *x, uint16_t *y);

public:
  /** Constructor, needs these parameters to initialize I2C */
  MindsensorsUI(void * shield, SH_BankPort bp);

  /** read the touchscreen press and write the coordinates to the output parameters
    @param[out] x x-value of touchscreen press is written to this variable
    @param[out] y y-value of touchscreen press is written to this variable
  */
  void getTouchscreenValues(uint16_t *x, uint16_t *y);
  
  /** reads the x-coordinate of the touchscreen press */
  uint16_t TS_X();
  
  /** reads the y-coordinate of the touchscreen press */
  uint16_t TS_Y();
  
  /** detect touchscreen presses and prevents false positives */
  bool isTouched();
  
  bool checkButton(uint16_t x, uint16_t y, uint16_t width, uint16_t height);
  
  /* returns 0 if none of the software buttons are touched, or 1-4 if one is. */
  uint8_t getFunctionButton();
  
  void clearScreen();

private:
  bool mirrorWriteToSerialEnabled = true;
  bool smartLineWrappingEnabled = true;

public:
  /** By default any calls to print or println will display on the 
    PiStorms touchscreen and the Serial Monitor. Use this method to change this behavior.
    True will print to both, false will print only to the touchscreen.
  */
  void mirrorWriteToSerial(bool enable = true);
  
  /** By default text will be wrapped by word when printed to the display.
    Use this method to enable or disable this functionality.
  */
  void smartLineWrapping(bool enable = true);
  
  size_t write(const uint8_t *buffer, size_t size);

};

#endif //MINDSENSORSUI_H
