// EVShield.cpp

// Initial version: 2010-06-07 by Clinton Blackmore
// Large ports of the code is ported from the NXC library for the device,
// written by Deepak Patil.
// 12/18/2014  Nitin Patil --  modified to work with EVshield   
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

#include "EVShield.h"
#include "Wire.h"
#include "MsTimer2.h"
static void pingEV();

#if defined(__AVR__)
	static void callbackLED();
#elif defined(__PIC32MX__)
	uint32_t callbackLED(uint32_t);
#endif

byte initCounter = 0;
bool btnState_go, btnState_left, btnState_right;
uint8_t redLED, redLED_cp;
uint8_t greenLED, greenLED_cp;
uint8_t blueLED, blueLED_cp;

bool toggle2 = 0;

bool format_bin(uint8_t i, char *s)
{
  int j;
  int b = 0x80;
 
  s[0] = '\0';
  for ( j = 0; j < 8; j++) {
    if ( i&b ) {
      strcat(s, "1");
    } else {
      strcat(s, "0");
    }
    b = b>>1;
  }
}


EVShield::EVShield(uint8_t i2c_address_a, uint8_t i2c_address_b)
{
  if ( i2c_address_a != SH_Bank_A) bank_a.setAddress(i2c_address_a);
  if ( i2c_address_b != SH_Bank_B) bank_b.setAddress(i2c_address_b);
}

void EVShield::init(SH_Protocols protocol)
{
    while (initCounter < 5){
    //Serial.println(initCounter);
    I2CTimer();
	initProtocols(protocol);    
   }
}

void EVShield::initProtocols(SH_Protocols protocol)
{
  m_protocol = protocol;
  if (!m_protocol ) {
    bank_a._i2c_buffer = bank_a._buffer;
    bank_b._i2c_buffer = bank_b._buffer;
  } else {
    bank_a._i2c_buffer = bank_a._so_buffer;
    bank_b._i2c_buffer = bank_b._so_buffer;
  }
  bank_a.init((void *) this, (SH_BankPort)-1);
  bank_b.init((void *) this, (SH_BankPort)-1);

// ensure firmware compatibility.
// assuming that both banks are identical,
// it's adequate to check on one of the banks
  char v[10];
  char d[10];
  char str[80];
  
  strcpy(d, bank_a.getDeviceID());
  strcpy(v, bank_a.getFirmwareVersion());
  if ( ( strcmp(d, "PiStorms") == 0 && (strcmp(v, "V1.09") >= 0 )) ||
       ( strcmp(d, "EVShld")   == 0 && (strcmp(v, "V1.09") >= 0)) )
  {
     // firmware is ok for this library
     initCounter = 6;
  } else {
    ++initCounter;
    if (initCounter == 5){
    sprintf (str,"ERROR: Version mismatch. Version: %s",  v);
    Serial.println(str);
    Serial.println("V1.09 or later expected");
    Serial.println("Please upgrade your EVshield Firmware");
      while (true) { // stop here with red blinking light.
        ledSetRGB(100, 0, 0);
        delay(500);
        ledSetRGB(0, 0, 0);
        delay(500);
      }
    }
    delay(100);
  }
  // end of firmware compatibility check
}

void EVShield::I2CTimer()
{
 //TCNT2  = 0; 
 MsTimer2::set(300, pingEV); // 300ms period
 MsTimer2::start();  
}

void EVShield::initLEDTimers()
{
  #if defined(__AVR__)

	  MsTimer2::set(3, callbackLED);
	  MsTimer2::start();
#elif defined(__PIC32MX__)
	  attachCoreTimerService(callbackLED);
#endif
}

EVShieldBankB::EVShieldBankB(uint8_t i2c_address)
: EVShieldBank(i2c_address)
{

}

EVShieldBank::EVShieldBank(uint8_t i2c_address)
: EVShieldI2C(i2c_address)
{

}
/*
void EVShield::I2CTimer(){
  //set timer2 interrupt at 64kHz
  TCCR2A = 0;// set entire TCCR2A register to 0
  TCCR2B = 0;// same for TCCR2B
  TCNT2  = 0;//initialize counter value to 0
  // set compare match register for 64khz increments or 300ms
  OCR2A = 74;// = (16*10^6) / (64000*3.3333) - 1 (must be <256)
  // turn on CTC mode
  TCCR2A |= (1 << WGM21);
  // Set CS21 bit for 64 prescaler
  TCCR2B |= (1 << CS22);   
  // enable timer compare interrupt
  TIMSK2 |= (1 << OCIE2A);  
}
*/
// provided for backword compatibility with nxshield programs.
int EVShieldBank::nxshieldGetBatteryVoltage()
{
  return evshieldGetBatteryVoltage();
}
// Voltage value returned in milli-volts.
int EVShieldBank::evshieldGetBatteryVoltage()
{
  int v;
  int factor = 40;
  v = readByte(SH_VOLTAGE);
  return (v * factor);
}

uint8_t EVShieldBank::EVShieldIssueCommand(char command)
{
  return writeByte(SH_COMMAND, (uint8_t)command);
}

// Set/get the encoder target for the motor (ie. a position to go
// to and stop at)
bool EVShieldBank::motorSetEncoderTarget(SH_Motor which_motor, long target)
{
  uint8_t reg = (which_motor == SH_Motor_1) ? SH_SETPT_M1 : SH_SETPT_M2;
  return writeLong(reg, target);
}

long EVShieldBank::motorGetEncoderTarget(SH_Motor which_motor)
{
  uint8_t reg = (which_motor == SH_Motor_1) ? SH_SETPT_M1 : SH_SETPT_M2;
  return (long)readLong(reg);
}

// Set/get the speed of the motor
// (I believe this is in the range [-100, +100])
bool EVShieldBank::motorSetSpeed(SH_Motor which_motor, int speed)
{
  uint8_t reg = (which_motor == SH_Motor_1) ? SH_SPEED_M1 : SH_SPEED_M2;
  return writeByte(reg, (uint8_t)(int8_t)speed);
}
int8_t EVShieldBank::motorGetSpeed(SH_Motor which_motor)
{
  uint8_t reg = (which_motor == SH_Motor_1) ? SH_SPEED_M1 : SH_SPEED_M2;
  return (int8_t)readByte(reg);
}

// This is the time, in seconds, for the motor to run
bool EVShieldBank::motorSetTimeToRun(SH_Motor which_motor, int seconds)
{
  uint8_t reg = (which_motor == SH_Motor_1) ? SH_TIME_M1 : SH_TIME_M2; 
  return writeByte(reg, seconds);
}
uint8_t EVShieldBank::motorGetTimeToRun(SH_Motor which_motor)
{
  uint8_t reg = (which_motor == SH_Motor_1) ? SH_TIME_M1 : SH_TIME_M2; 
  return readByte(reg);
}

// Command Register 'B' is currently unused, but reserved for future expansion
// If you set it, you must set it to zero.
bool EVShieldBank::motorSetCommandRegB(SH_Motor which_motor, uint8_t value)
{
  uint8_t reg = (which_motor == SH_Motor_1) ? SH_CMD_B_M1 : SH_CMD_B_M2; 
  return writeByte(reg, value);
}
uint8_t EVShieldBank::motorGetCommandRegB(SH_Motor which_motor)
{
  uint8_t reg = (which_motor == SH_Motor_1) ? SH_CMD_B_M1 : SH_CMD_B_M2; 
  return readByte(reg);
}

// See User's Guide for what command register A does
bool EVShieldBank::motorSetCommandRegA(SH_Motor which_motor, uint8_t value)
{
  uint8_t reg = (which_motor == SH_Motor_1) ? SH_CMD_A_M1 : SH_CMD_A_M2; 
  return writeByte(reg, value);
}
uint8_t EVShieldBank::motorGetCommandRegA(SH_Motor which_motor)
{
  uint8_t reg = (which_motor == SH_Motor_1) ? SH_CMD_A_M1 : SH_CMD_A_M2; 
  return readByte(reg);
}

// Get the current encoder position
int32_t EVShieldBank::motorGetEncoderPosition(SH_Motor which_motor)
{
  uint8_t location = (which_motor == SH_Motor_1) ? SH_POSITION_M1 : SH_POSITION_M2;
  return (int32_t)readLong(location);
}

// See User's Guide for documentation on the status byte
uint8_t EVShieldBank::motorGetStatusByte(SH_Motor which_motor)
{
  uint8_t location = (which_motor == SH_Motor_1) ? SH_STATUS_M1 : SH_STATUS_M2;
  return readByte(location);
}

// (I couldn't find an explanation for this in the User's Guide)
uint8_t EVShieldBank::motorGetTasksRunningByte(SH_Motor which_motor)
{
  uint8_t location = (which_motor == SH_Motor_1) ? SH_TASKS_M1 : SH_TASKS_M2;
  return readByte(location);
}

// Set the PID that controls how we stop as we approach the
// angle we're set to stop at
bool EVShieldBank::motorSetEncoderPID(uint16_t Kp, uint16_t Ki, uint16_t Kd)
{
  writeIntToBuffer(_i2c_buffer + 0, Kp);
  writeIntToBuffer(_i2c_buffer + 2, Ki);
  writeIntToBuffer(_i2c_buffer + 4, Kd);
  return writeRegisters(SH_ENCODER_PID, 6);
}

// Sets the PID that controls how well that motor maintains its speed
bool EVShieldBank::motorSetSpeedPID(uint16_t Kp, uint16_t Ki, uint16_t Kd)
{
  writeIntToBuffer(_i2c_buffer + 0, Kp);
  writeIntToBuffer(_i2c_buffer + 2, Ki);
  writeIntToBuffer(_i2c_buffer + 4, Kd);
  return writeRegisters(SH_SPEED_PID, 6);
}

bool EVShieldBank::centerLedSetRGB(uint8_t R, uint8_t G, uint8_t B)
{
  bool b;
  writeByteToBuffer(_i2c_buffer, R);
  writeByteToBuffer(_i2c_buffer+1,G);
  writeByteToBuffer(_i2c_buffer+2,B);
  b = writeRegisters(SH_CENTER_RGB_LED, 3);
  delay(1);   // required to avoid subsequent i2c errors.
  return b;
}
// Set the RGBLED that shows RGB color

// TODO: it's noticed that i2c call made after ledSetRGB call fails.
// a delay is added to avoid the errors, but
// see why it fails and find a better solution.

bool EVShieldBank::ledSetRGB(uint8_t R, uint8_t G, uint8_t B)
{
  bool b;
  writeByteToBuffer(_i2c_buffer, R);
  writeByteToBuffer(_i2c_buffer+1,G);
  writeByteToBuffer(_i2c_buffer+2,B);
  b = writeRegisters(SH_RGB_LED, 3);
  delay(1);   // required to avoid subsequent i2c errors.
  return b;
}

// See user's guide for details.
bool EVShieldBank::motorSetPassCount(uint8_t pass_count)
{
  return writeByte(SH_PASS_COUNT, pass_count);
}

// Sets tolerance which adjust accuracy while positioning.
// See user's guide for more details.
bool EVShieldBank::motorSetTolerance(uint8_t tolerance)
{
  return writeByte(SH_TOLERANCE, tolerance);
}


// Special I2C commands

// Resets all encoder values and motor parameters.  Leaves PIDs untouched.
bool EVShieldBank::motorReset()
{
  return EVShieldIssueCommand('R');
}

// Tells the motors to start at the same time.
bool EVShieldBank::motorStartBothInSync()
{
  return EVShieldIssueCommand('S');
}

// Reset the encoder for motor 1 or motor 2
bool EVShieldBank::motorResetEncoder(SH_Motor which_motor)
{
  char code = (which_motor == SH_Motor_1) ? 'r' : 's';
  return EVShieldIssueCommand(code);
}


// This function sets the speed, the number of seconds, and
// the control (a.k.a. command register A)
bool EVShieldBank::motorSetSpeedTimeAndControl(
  SH_Motor which_motors,  // Motor_ 1, 2, or Both
  int     speed,      // in range [-100, +100]
  uint8_t duration,    // in seconds
  uint8_t control)    // bit flags for control purposes
{
  if (which_motors == SH_Motor_Both)
  {
    control &= ~SH_CONTROL_GO;  // Clear the 'go right now' flag
    bool m1 = motorSetSpeedTimeAndControl(SH_Motor_1, speed, duration, control);
    bool m2 = motorSetSpeedTimeAndControl(SH_Motor_2, speed, duration, control);
    motorStartBothInSync();
    return m1 && m2;
  }

  _i2c_buffer[0] = (uint8_t)(int8_t)speed;
  _i2c_buffer[1] = duration;
  _i2c_buffer[2] = 0;      // command register B
  _i2c_buffer[3] = control;  // command register A

  uint8_t reg = (which_motors == SH_Motor_1) ? SH_SPEED_M1 : SH_SPEED_M2;
  return writeRegisters(reg, 4);
}

void evshieldSetEncoderSpeedTimeAndControlInBuffer(
  uint8_t* buffer,  // pointer to the buffer
  long   encoder,  // encoder value
  int   speed,    // speed, in range [-100, +100]
  uint8_t duration,  // in seconds
  uint8_t control)  // control flags
{
  writeLongToBuffer(buffer + 0, encoder);
  buffer[4] = (uint8_t)(int8_t)speed;
  buffer[5] = duration;
  buffer[6] = 0;      // command register B
  buffer[7] = control;  // command register A
}


// This function sets the speed, the number of seconds, and
// the control (a.k.a. command register A)
bool EVShieldBank::motorSetEncoderSpeedTimeAndControl(
  SH_Motor which_motors,  // Motor_ 1, 2, or Both
  long    encoder,    // encoder/tachometer position
  int    speed,      // speed, in range [-100, +100]
  uint8_t duration,    // in seconds
  uint8_t control)    // control flags
{
  if (which_motors == SH_Motor_Both)
  {
    // The motor control registers are back to back, and both can be written in one command
    control &= ~SH_CONTROL_GO;  // Clear the 'go right now' flag
    evshieldSetEncoderSpeedTimeAndControlInBuffer(_i2c_buffer, encoder, speed, duration, control);
    evshieldSetEncoderSpeedTimeAndControlInBuffer(_i2c_buffer + 8, encoder, speed, duration, control);
    bool success = writeRegisters(SH_SETPT_M1, 16);
    motorStartBothInSync();
    return success;
  }

  // Or, just issue the command for one motor
  evshieldSetEncoderSpeedTimeAndControlInBuffer(_i2c_buffer, encoder, speed, duration, control);
  uint8_t reg = (which_motors == SH_Motor_1) ? SH_SETPT_M1 : SH_SETPT_M2;
  return writeRegisters(reg, 8);
}

// returns 0 when a motor has completed a timed move
uint8_t EVShieldBank::motorIsTimeDone(SH_Motor which_motors)
{
  uint8_t s1, s2;
  if (which_motors == SH_Motor_Both)
  {
    s1 = motorGetStatusByte(SH_Motor_1);
    s2 = motorGetStatusByte(SH_Motor_2);
    
    if ( (s1 & SH_STATUS_TIME) == 0 && (s2 & SH_STATUS_TIME) == 0 )
    {
      // if stall bit was on there was an error
      /*if ( (s1 & SH_STATUS_STALL) != 0 || (s2 & SH_STATUS_STALL) != 0 )
      {
        return SH_STATUS_STALL;
      } else {*/
        return 0;
      //}
    }
  } else {
    s1 = motorGetStatusByte(which_motors);
    if ( (s1 & SH_STATUS_TIME) == 0 ) {
      /*if ( (s1 & SH_STATUS_STALL) != 0 )
      {
        return SH_STATUS_STALL;
      } else {*/
        return 0;
      //}
    }
  }

}

// waited until a timed command finishes
uint8_t EVShieldBank::motorWaitUntilTimeDone(SH_Motor which_motors)
{
  uint8_t s;
  delay(50);  // this delay is required for the status byte to be available for reading.
  s = motorIsTimeDone(which_motors);  // fixed.
  while (( s & SH_STATUS_TIME ) != 0 ) {
    delay (50);
    s = motorIsTimeDone(which_motors);  // fixed.
  }
}

// True when a command based on using the motor encoder completes
uint8_t EVShieldBank::motorIsTachoDone(SH_Motor which_motors)
{
  uint8_t s1, s2;
  if (which_motors == SH_Motor_Both)
  {
    s1 = motorGetStatusByte(SH_Motor_1);
    s2 = motorGetStatusByte(SH_Motor_2);
    
    if ( (s1 & SH_STATUS_TACHO) == 0 && (s2 & SH_STATUS_TACHO) == 0 )
    {
      // if stall bit was on there was an error
      /*if ( (s1 & SH_STATUS_STALL) != 0 || (s2 & SH_STATUS_STALL) != 0 )
      {
        return SH_STATUS_STALL;
      } else {*/
        return 0;
      //}
    }
  } else {
    s1 = motorGetStatusByte(which_motors);
    if ( (s1 & SH_STATUS_TACHO) == 0 ) {
      /*if ( (s1 & SH_STATUS_STALL) != 0 )
      {
        return SH_STATUS_STALL;
      } else {*/
        return 0;
      //}
    }
  }
}

// waited until a turn-by-degrees command ends
uint8_t EVShieldBank::motorWaitUntilTachoDone(SH_Motor which_motors)
{
  uint8_t s;
  delay(50);  // this delay is required for the status byte to be available for reading.
  s = motorIsTachoDone(which_motors);
  while (( s & SH_STATUS_TACHO ) != 0 ) {
    delay (50);
    s = motorIsTachoDone(which_motors);
  }
}


// Utility functions for motor control

// Take a speed and direction and give just a speed
inline int calcFinalSpeed(int initialSpeed, SH_Direction direction)
{
  if (direction == SH_Direction_Forward)
    return initialSpeed;
  return -initialSpeed;
}

// Calculate the bits that control what happens when this action finishes
inline uint8_t calcNextActionBits(SH_Next_Action next_action)
{
  if (next_action == SH_Next_Action_Brake)
    return SH_CONTROL_BRK;
  else if (next_action == SH_Next_Action_BrakeHold)
    return SH_CONTROL_BRK | SH_CONTROL_ON;
}

void EVShieldBank::motorRunUnlimited(
  SH_Motor which_motors,      // Motor_ 1, 2, or Both
  SH_Direction direction,        // Direction_ Forward or Reverse
  int   speed)          // in range [-100, +100]
{
  uint8_t ctrl = SH_CONTROL_SPEED | SH_CONTROL_GO;
  int sp = calcFinalSpeed(speed, direction);
  motorSetSpeedTimeAndControl(which_motors, sp, 0, ctrl);
}

// runs the motors for a given number of seconds
uint8_t EVShieldBank::motorRunSeconds(
    SH_Motor which_motors,      // Motor_ 1, 2, or Both
    SH_Direction direction,        // Direction_ Forward or Reverse
    int     speed,          // [-100, +100]
    uint8_t duration,        // in seconds
    SH_Completion_Wait wait_for_completion,  // Completion_ Wait_For or Dont_Wait
    SH_Next_Action next_action)      // Next_Action_ Brake, BrakeHold or Float
{
  uint8_t ctrl = SH_CONTROL_SPEED | SH_CONTROL_TIME | SH_CONTROL_GO;
  ctrl |= calcNextActionBits(next_action);
  int sp = calcFinalSpeed(speed, direction);
  motorSetSpeedTimeAndControl(which_motors, sp, duration, ctrl);

  if (wait_for_completion == SH_Completion_Wait_For)
  {
    return motorWaitUntilTimeDone(which_motors);
  }
}

// runs the motors until the tachometer reaches a certain position
uint8_t EVShieldBank::motorRunTachometer(
    SH_Motor which_motors,      // Motor_ 1, 2, or Both
    SH_Direction direction,        // Direction_ Forward or Reverse
    int   speed,          // [-100, +100]
    long    tachometer,        // in degrees
    SH_Move relative,        // Move_ Relative or Absolute
    SH_Completion_Wait wait_for_completion,  // Completion_ Wait_For or Dont_Wait
    SH_Next_Action next_action)      // Next_Action_ Brake, BrakeHold or Float
{
  uint8_t ctrl = SH_CONTROL_SPEED | SH_CONTROL_TACHO | SH_CONTROL_GO;
  ctrl |= calcNextActionBits(next_action);
  int final_speed = calcFinalSpeed(speed, direction);
  uint8_t s;

  // The tachometer can be absolute or relative.
  // If it is absolute, we ignore the direction parameter.
  long final_tach = tachometer;

  if (relative == SH_Move_Relative)
  {
    ctrl |= SH_CONTROL_RELATIVE;

    // a (relative) forward command is always a positive tachometer reading
    final_tach = abs(tachometer);
    if (final_speed < 0)
    {
      // and a (relative) reverse command is always negative
      final_tach = -final_tach;
    }
  }

  motorSetEncoderSpeedTimeAndControl(which_motors, final_tach, final_speed, 0, ctrl);

  if (wait_for_completion == SH_Completion_Wait_For)
  {
    //delay(50);
    s = motorWaitUntilTachoDone(which_motors);
  }
  return s;
}

// Turns the motors the specified number of degrees
uint8_t EVShieldBank::motorRunDegrees(
    SH_Motor which_motors,      // Motor_ 1, 2, or Both
    SH_Direction direction,        // Direction_ Forward or Reverse
    int   speed,          // [-100, +100]
    long    degrees,        // in degrees
    SH_Completion_Wait wait_for_completion,  // Completion_ Wait_For or Dont_Wait
    SH_Next_Action next_action)      // Next_Action_ Brake, BrakeHold or Float
{
  return motorRunTachometer(which_motors, direction, speed, degrees,
      SH_Move_Relative, wait_for_completion, next_action);
}

// runs the motor(s) the specified number of rotations
uint8_t EVShieldBank::motorRunRotations(
    SH_Motor which_motors,      // Motor_ 1, 2, or Both
    SH_Direction direction,        // Direction_ Forward or Reverse
    int   speed,          // [-100, +100]
    long    rotations,        // number of full rotations of the motor
    SH_Completion_Wait wait_for_completion,  // Completion_ Wait_For or Dont_Wait
    SH_Next_Action next_action)      // Next_Action_ Brake, BrakeHold or Float
{
  return motorRunTachometer(which_motors, direction, speed, 360 * rotations,
      SH_Move_Relative, wait_for_completion, next_action);
}

// The stop command will only stop the motor(s) by making them float/coast
// or brake.  Even if you specify Next_Action_BrakeHold, the motor
// will only brake, not hold.
bool EVShieldBank::motorStop(SH_Motor which_motors, SH_Next_Action next_action)
{
  if (which_motors >= SH_Motor_1 && which_motors <= SH_Motor_Both)
  {
    // The magic variables become clear in the user's guide
    uint8_t base_code = (next_action != SH_Next_Action_Float) ? 'A' - 1 : 'a' - 1;

    return EVShieldIssueCommand(base_code + which_motors);
  }

  setWriteErrorCode(5);  // bad parameters
  return false;
}

bool EVShieldBank::sensorSetType(uint8_t which_sensor, uint8_t sensor_type)
{
  /*
   * which_sensor can only be 1 or 2,
   * reject any other value
   */
  switch (which_sensor) {
    case 1:
      return writeByte(SH_S1_MODE, sensor_type);
      break;
    case 2:
      return writeByte(SH_S2_MODE, sensor_type);
      break;
    default:
      return false;
      break;
  }
  return false;
}

/* register locations
  unsigned char Sensor1_mode;    //0x8A
  unsigned char Sensor2_mode;        //0x8B
  unsigned int Sensor_1_reading;    //0x70
  unsigned int Sensor_2_reading;    //0x8E
*/
int EVShieldBank::sensorReadRaw(uint8_t which_sensor)
{
  /*
   * sensor can only be 1 or 2,
   * otherwise return -1;
   */
  switch (which_sensor) {
    case 1:
        return readInteger(SH_S1_ANALOG);    
        break;
    case 2:
        return readInteger(SH_S2_ANALOG);
        break;
    default:
      return -1;
      break;
  }
}

bool EVShieldBankB::sensorSetType(uint8_t which_sensor, uint8_t sensor_type)
{
  /*
   * which_sensor can only be 1 or 2,
   * reject any other value
    */
  
  
  switch (which_sensor) {
    case 1:
      return EVShieldBankB::writeByte(SH_S1_MODE, sensor_type);
      break;
    case 2:
      return EVShieldBankB::writeByte(SH_S2_MODE, sensor_type);
      break;
    default:
      return false;
      break;
    }
  return false;
}

int EVShieldBankB::sensorReadRaw(uint8_t which_sensor)
{
  int a;
  switch (which_sensor) {
    case 1:
      // sensor port 1 behaves same as BankA
      // so call parent function.
      return EVShieldBankB::readInteger(SH_S1_ANALOG); 
      break;
      
    case 2:
      return EVShieldBankB::readInteger(SH_S2_ANALOG); 
      break;
    default:
      return -1;
      break;
  }
}

void pingEV()
{
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
    while ((TWCR & (1<<TWINT)) == 0);
    TWDR = 0x34;
    TWCR = (1<<TWINT)|(1<<TWEN);
    while ((TWCR & (1<<TWINT)) == 0);
    TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
    TCNT2  = 0;//initialize counter value to 0
    /*
    if (toggle2)
    {
      digitalWrite(13, HIGH);
      toggle2 = 0;
    }
    else
    {
      digitalWrite(13, LOW);
      toggle2 = 1; 
    }
    */
}

#if defined(__AVR__)

void callbackLED()
{
  static uint8_t index = 1;

  //pinMode(BTN_GO,INPUT);
  //btnState_go = !digitalRead(BTN_GO);
  //pinMode(BTN_GO,OUTPUT);

  pinMode(BTN_LEFT,INPUT);
  btnState_left = !digitalRead(BTN_LEFT);
  pinMode(BTN_LEFT,OUTPUT);

  pinMode(BTN_RIGHT,INPUT);
  btnState_right = !digitalRead(BTN_RIGHT);
  pinMode(BTN_RIGHT,OUTPUT);

  digitalWrite(LED_RED, !redLED_cp&0x01);
  digitalWrite(LED_GREEN, !greenLED_cp&0x01);
  digitalWrite(LED_BLUE, !blueLED_cp&0x01);

  if (index == 8){
    index = 1;
    redLED_cp   = redLED;
    greenLED_cp = greenLED;
    blueLED_cp  = blueLED;
  }
  else{
    redLED_cp    = redLED_cp   >>1;
    greenLED_cp  = greenLED_cp >>1;
    blueLED_cp   = blueLED_cp  >>1;
    index ++;
  }

}
#elif defined(__PIC32MX__)
uint32_t callbackLED(uint32_t currentTime)
{
  static uint8_t index = 1;

  //pinMode(BTN_GO,INPUT);
  //btnState_go = !digitalRead(BTN_GO);
  //pinMode(BTN_GO,OUTPUT);

  pinMode(BTN_LEFT,INPUT);
  btnState_left = !digitalRead(BTN_LEFT);
  pinMode(BTN_LEFT,OUTPUT);

  pinMode(BTN_RIGHT,INPUT);
  btnState_right = !digitalRead(BTN_RIGHT);
  pinMode(BTN_RIGHT,OUTPUT);

  digitalWrite(LED_RED, !redLED_cp&0x01);
  digitalWrite(LED_GREEN, !greenLED_cp&0x01);
  digitalWrite(LED_BLUE, !blueLED_cp&0x01);

  if (index == 8){
    index = 1;
    redLED_cp   = redLED;
    greenLED_cp = greenLED;
    blueLED_cp  = blueLED;
  }
  else{
    redLED_cp    = redLED_cp   >>1;
    greenLED_cp  = greenLED_cp >>1;
    blueLED_cp   = blueLED_cp  >>1;
    index ++;
  }
	return (currentTime + CORE_TICK_RATE*3);
}

#endif

bool EVShield::getButtonState(uint8_t btn) {
  uint8_t bVal;
  bVal = bank_a.readByte(SH_BTN_PRESS);

  return (bVal == btn);
}

void EVShield::waitForButtonPress(uint8_t btn, uint8_t led_pattern) {
  while(!getButtonState(btn)){
      switch (led_pattern) {
        case 1:
          ledBreathingPattern();
          break;
        case 2:
          ledHeartBeatPattern();
          break;
        default:
          delay (300);
          break;
      }
  }
  if (led_pattern != 0) ledSetRGB(0,0,0);
}

void EVShield::ledBreathingPattern() {
    static int breathNow = 0;
    int i;

    if ( breathNow > 800 && breathNow < 6400 ) {
        // LED intensity rising
        i = breathNow/800;
        ledSetRGB(0, i, i);
        delayMicroseconds(150);
        if ( i == 8 ) delayMicroseconds(200);
    } else if (breathNow > 6400 && breathNow < 13400 ) {
        // LED intensity falling
        i = (14400-breathNow)/1000;
        ledSetRGB(0, i, i);
        delayMicroseconds(200);
        if ( i == 8 ) delayMicroseconds(200);
    } else {
        // LED intensity stable.
        ledSetRGB(0,1,1);
        delayMicroseconds(50);
    }
    breathNow ++;
}

void EVShield::ledSetRGB(uint8_t red, uint8_t green, uint8_t blue)
{
  bank_a.ledSetRGB(red,green,blue);
  //delay(100);
  bank_b.ledSetRGB(red,green,blue);
  //delay(100);
}

void EVShield::ledHeartBeatPattern() {
  static int breathNow = 0;
  int i;

  if ( breathNow > 800 && breathNow < 6400 ) {
    // LED intensity rising
    i = breathNow/800;
    ledSetRGB(0, i, i);
    //delayMicroseconds(150);
    if ( i == 8 ) delayMicroseconds(200);
  } else if (breathNow > 6400 && breathNow < 13400 ) {
    // LED intensity falling
    i = (14400-breathNow)/1000;
    ledSetRGB(0, i, i);
    //delayMicroseconds(200);
    if ( i == 8 ) delayMicroseconds(200);
  } else {
    // LED intensity stable.
    ledSetRGB(0,1,1);
    delayMicroseconds(10);
  }
  breathNow ++;
}
