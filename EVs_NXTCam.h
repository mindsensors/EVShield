
// EVs_NXTCam.h
//
// This is a class for controlling the NXT Cam, made by Mindsensors.
// See http://www.mindsensors.com/index.php?module=pagemaster&PAGE_user_op=view_page&PAGE_id=78 .

// Initial version: 2010-06-18 by Andrew Sylvester
// Modified for EVShield: 2015-02-15 by Michael Giles
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


#ifndef EVs_NXTCam_H
#define EVs_NXTCam_H

#define Cam_Command               0x41
#define Cam_Number_Objects           0x42
#define Start_Reg               0x43

#include "EVShieldI2C.h"

/**
  @brief This class interfaces with NXTCam attached to EVShield 
  */
class EVs_NXTCam : public EVShieldI2C
{
public:
  /** class constructor for NXTCam with optional custom i2c address parameter */
  EVs_NXTCam(uint8_t i2c_address = 0x02);
  
  /** issue character command byte to the command register of the NXTCam 
   (command such as enable tracking, stop tracking, etc).  Refer to User Guide for available commands.
*/
  uint8_t    issueCommand(char command);
  
  /** sort the blobs from the NXTCam byt blobs */
  bool    sortSize();
  
  /** configure the tracking mode of the device to object tracking */
  bool    selectObjectMode();
  
  /** write to the image registers of the CCD */
  bool    writeImageRegisters();
  
  /** disable tracking for the NXTCam */
  bool    disableTracking();
  
  /** enable tracking for the NXTCam */
  bool    enableTracking();
  
  /** get the current colormap of the NXTCam */
  bool    getColorMap();
  
/** not impmemented yet */
  bool    illuminationOn();
  
  /** read the image registers of the CCD */
  bool    readImageRegisters();
  
  /** put the NXTCam in line tracking mode */
  bool    selectLineMode();
  
  /** ping the NXTCam to test connection */
  bool    pingCam();
  
  /** reset the NXTCam */
  bool    resetCam();
  
  /** send ColorMap to the NXTCam */
  bool    sendColorMap();
  
/** not impmemented yet */
  bool    illuminationOff();
  
  /** sort the blobs by color */
  bool    sortColor();
  
  /** clear any selected sort configuration */
  bool    sortNone();
  
  /** get the firmware of the NXTCam */
  bool    camFirmware();
  
  /** get the total number of objected tracked by the NXTCam */
  int      getNumberObjects();
  

/**
This function gets the blob information of all the blobs that NXTCam is tracking.
There could be upto 8 blobs being tracked by NXTCam.
All the parameters of this function are return values.
This function will return color and coordinate information for all the blobs.
  @param nblobs      In this variable, number of blobs NXTCam sees are returned.
The blobs NXTCam sees could be of different color or same color.
For e.g. if you have 3 colors defined, say red (color 1), blue (color 2) and green (color3), and you have 3 red objects and 2 blue objects and 1 green object in front of NXTCam, nblobs will be 6.
color[]: a array of colors for the blobs
in above example, Color array will have 6 valid elements - three bytes will say 1 (for color1), and 2 bytes will say (for color 2), and 1 byte will say 3 (for color 3).
Based on sorting chosen, they will be sorted by size or color (if the sorting was color, first 3 bytes will be 1, next two will be 2 and next one will be 3).
  @param color      a array of colors for the blobs (array has 8 elements)
  @param left       the coordinate values of the blobs (array of 8 elements)
  @param top        the coordinate values of the blobs (array of 8 elements)
  @param right      the coordinate values of the blobs (array of 8 elements)
  @param bottom     the coordinate values of the blobs (array of 8 elements)
@return look at the nblobs first to see how many blobs are being tracked, and then read the respective color and coordinate infromation.
*/
  void    getBlobs(int *nblobs, uint8_t *color, uint8_t *left, uint8_t *top, uint8_t *right, uint8_t *bottom);

};

#endif
