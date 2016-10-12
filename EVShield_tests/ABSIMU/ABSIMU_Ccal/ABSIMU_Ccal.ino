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
For beginners tutorial (and user guide) visit:
http://www.openelectrons.com/docs/viewdoc/25
*/

#include <Wire.h>
#include <EVShield.h>
#include <EVs_AbsoluteIMU.h>

// setup for this example:
// attach AbsoluteIMU to Port BAS1
// Open the Serial terminal to view.

//
// declare the EVShield(s) attached to your Arduino.
//
EVShield    evshield(0x34,0x36);

//
// declare the i2c devices used on EVShield(s).
//

EVs_AbsoluteIMU imu (0x22);

void setup()
{
  char str[256];
/**  Start serial for output
 */
  Serial.begin(115200);  // 
/**  Wait, allowing time to activate the serial monitor
 */ 
  delay(500); // wait, allowing time to activate the serial monitor

/**  Initialize the Hardware I2C protocol for EVShield
 */
 evshield.init( SH_HardwareI2C );

/**  Initialize the i2c sensors.
 */
  imu.init( &evshield, SH_BAS1 );

/**  Wait until user presses GO button to continue the program
 */
  while (!evshield.getButtonState(BTN_GO)) {
    if (millis() % 1000 < 3) {
      Serial.println("Press GO button to continue");
    }
  }
 
  Serial.println ("Press  LEFT button to begin calibration");
  evshield.waitForButtonPress(BTN_LEFT);
  imu.beginCompassCalibration();
  
  Serial.println ("Press Right button when calibration finished");
  evshield.waitForButtonPress(BTN_RIGHT);
  imu.endCompassCalibration();  
}

#define DELAY_T 0

void loop()
{
  char aa[80];        
  char str[256];          //sets length of character string
  uint8_t  result;
  char str2[20];          //sets length of character string 2
  char str3[20];          //sets length of character string 3 
  gyro mygyro;            //declares mygyro variable
  cmps mycmps;            //declares mycmps variable
  accl myaccl;            //declares myaccl variable
  magnetic_field mymgnt;  //declares mymgnt variable

  strcpy(aa, imu.getFirmwareVersion() );
  sprintf (str, "imu: getFirmwareVersion: %s", aa);
  Serial.println(str);
/**  Displays Device ID of sensor
 */
  strcpy(aa, imu.getDeviceID() );
  sprintf (str, "imu: DeviceID: %s", aa);
  Serial.println(str);
/**  Gets and displays Vendor ID of sensor
 */
  strcpy(aa, imu.getVendorID() );
  sprintf (str, "imu: VendorID: %s", aa);
  Serial.println(str);
/**  Displays Magnetometer reading
 */
  imu.readGyro(mygyro);
  sprintf (str, "imu: gyro      x:%d | y:%d | z:%d", mygyro.gx, mygyro.gy, mygyro.gz);
  Serial.println(str);
/**  Displays Tilt reading
 */  
  imu.readAccelerometer(myaccl);
  sprintf (str, "imu: tilt      x:%d | y:%d | z:%d", myaccl.tx, myaccl.ty, myaccl.tz);
  Serial.println(str);
/**  Displays Accelerometer reading
 */  
  sprintf (str, "imu: accl      x:%d | y:%d | z:%d", myaccl.ax, myaccl.ay, myaccl.az);
  Serial.println(str);
/**  Displays Magnetic Field reading
 */
  imu.readMagneticField(mymgnt);
  sprintf (str, "imu: magfield  x:%d | y:%d | z:%d", mymgnt.mx, mymgnt.my, mymgnt.mz);
  Serial.println(str);
/**  Displays Compass reading
 */
  imu.readCompass(mycmps);
  sprintf (str, "imu: compass:  %d", mycmps.heading );
  Serial.println(str);
  sprintf (str, "imu: error:  %d", mycmps.error );
  Serial.println(str);
 
  Serial.println( "-------------" );
  delay (1500);
}


