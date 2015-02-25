#include <Wire.h>
#include <EVShield.h>
#include <EVs_NXTVoltMeter.h>

// setup for this example:
// attach external power to EVShield.
// attach NXTVoltMeter to Port BAS1
// Open the Serial terminal to view.

//
// declare the EVShield(s) attached to your Arduino.
//
EVShield    evshield(0x34,0x36);

//
// declare the i2c devices used on EVShield(s).
//

EVs_VoltMeter  vm  (0x26);

void setup()
{
  char str[256];
/**  Start serial for output
 */
  Serial.begin(115200);  // 
/**  Wait, allowing time to activate the serial monitor
 */ 
  delay(500); // wait, allowing time to activate the serial monitor


/**  Initialize the protocol for EVShield
     It is best to use Hardware I2C (unless you want to use Ultrasonic).
 */
  evshield.init( SH_HardwareI2C );
/**  Wait until user presses GO button to continue the program
 */
  Serial.println ("Press GO button to continue");
  evshield.waitForButtonPress(BTN_GO);
/**  Initialize the i2c sensors.
 */
  vm.init( &evshield, SH_BAS1 );
/**  Set the Reference Voltage to Absolute Voltage.
 */
   vm.setReferenceV();

}


#define DELAY_T 0

void loop()
{
  char  str[256];      //declares character string length
  int  avolt;          //declares "avolt" variable
  int  rvolt;          //declares "rvolt" variable
  int  refV;           //declares "refV" variable
  
/**  Displays Absolute Voltage value
 */
  avolt = vm.getAVoltage();
  sprintf (str, "VMeter: Absolute Volts:   %d", avolt);
  Serial.println(str);
/**  Displays Relative Voltage value
 */  
  rvolt = vm.getRVoltage();
  sprintf (str, "VMeter: Relative Volts:   %d", rvolt);
  Serial.println(str);
/**  Displays Reference Voltage value
 */
  refV = vm.getReference();
  sprintf (str, "VMeter: Reference Volts: %d", refV);
  Serial.println(str);
  
  Serial.println( "-------------" );
  delay (1500);
  
  
}

