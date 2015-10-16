
/** \file EVShield.h
* EVShield.h defines main interfaces used in the EVShield library.
 \mainpage  EVShield Library Reference
 \section intro_sec Introduction
 EVShield library provides interfaces to use EVShield by mindsensors.com on Arduino.
 
 At the time of this writing, EVShield and this library can be used with the following boards:

   <b>Arduino boards:</b>\n
      Uno, Uno R3\n
      Duemilanove\n
		 

 \section getting_started  Getting Started
 If you need help to begin with your first program, please download and review <b>EVShield-AVR-Library-Tutorial.pdf</b>
 from following url: http://www.mindsensors.com/index.php?controller=attachment&id_attachment=136

 \section more_info  More Information
 More information about EVShield is available at: http://www.mindsensors.com/arduino/16-evshield-for-arduino-duemilanove-or-uno

 Online documentation of this Library Reference is available at:
 http://www.mindsensors.com/reference/EVShield/html/
 (Note however, the online version may not match exactly with the library files you have installed on your computer).

 \section install_sec Installation Instructions
 To install this library in your Arduino IDE, download the latest zip file from following location:
 https://github.com/openelectrons/EVShield

 And follow the instructions at this url to install it on your computer.
*/

/*
 * EVShield interface library
 * Copyright (C) 2015 mindsensors.com
 * 12/18/2014  Nitin Patil --  modified to work with EVshield 
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

#ifndef EVShield_H
#define EVShield_H

#include "SHDefines.h"

// Motor control related constants.
#define SH_CONTROL_SPEED      0x01
#define SH_CONTROL_RAMP       0x02
#define SH_CONTROL_RELATIVE   0x04
#define SH_CONTROL_TACHO      0x08
#define SH_CONTROL_BRK        0x10
#define SH_CONTROL_ON         0x20
#define SH_CONTROL_TIME       0x40
#define SH_CONTROL_GO         0x80

#define SH_STATUS_SPEED       0x01
#define SH_STATUS_RAMP        0x02
#define SH_STATUS_MOVING      0x04
#define SH_STATUS_TACHO       0x08
#define SH_STATUS_BREAK       0x10
#define SH_STATUS_OVERLOAD    0x20
#define SH_STATUS_TIME        0x40
#define SH_STATUS_STALL       0x80

#define SH_COMMAND     0x41
#define SH_VOLTAGE     0x6E

#define SH_SETPT_M1     0x42
#define SH_SPEED_M1     0x46
#define SH_TIME_M1      0x47
#define SH_CMD_B_M1     0x48
#define SH_CMD_A_M1     0x49

#define SH_SETPT_M2     0x4A
#define SH_SPEED_M2     0x4E
#define SH_TIME_M2      0x4F
#define SH_CMD_B_M2     0x50
#define SH_CMD_A_M2     0x51

/*
 * Read registers.
 */
#define SH_POSITION_M1  0x52
#define SH_POSITION_M2  0x56
#define SH_STATUS_M1    0x5A
#define SH_STATUS_M2    0x5B
#define SH_TASKS_M1     0x5C
#define SH_TASKS_M2     0x5D

#define SH_ENCODER_PID  0x5E
#define SH_SPEED_PID  0x64
#define SH_PASS_COUNT  0x6A
#define SH_TOLERANCE  0x6B

#define SH_S1_MODE  0x6F
#define SH_S1_EV3_MODE  0x6F
#define SH_S1_ANALOG   0x70

#define SH_S2_MODE  0xA3
#define SH_S2_EV3_MODE  0x6F
#define SH_S2_ANALOG   0xA4

#define SH_BTN_PRESS     0xDA
#define SH_RGB_LED     0xD7
#define SH_CENTER_RGB_LED     0xDE

/* constants to be used by user programs */
/**
 * \enum SH_Motor Motor selection related constants
 */
typedef enum {
  SH_Motor_1     = 0x01,   /*!< Choose Motor 1 for selected operation */
  SH_Motor_2     = 0x02,   /*!< Choose Motor 2 for selected operation  */
  SH_Motor_Both  = 0x03    /*!< Choose Both Motors for selected operation */
} SH_Motor;

/*
 * \enum SH_Next_Action Next action related constants
 */
typedef enum {
  SH_Next_Action_Float  = 0x00, /*!< stop and let the motor coast. */
  SH_Next_Action_Brake = 0x01, /*!< apply brakes, and resist change to tachometer, but if tach position is forcibly changed, do not restore position */
  SH_Next_Action_BrakeHold = 0x02 /*!< apply brakes, and restore externally forced change to tachometer */
} SH_Next_Action;

/**
 * \enum SH_Direction Motor direction related constants.
 */
typedef enum {
  SH_Direction_Reverse = 0x00,   /*!< Run motor in reverse direction */
  SH_Direction_Forward = 0x01   /*!< Run motor in forward direction */
} SH_Direction;

/*
 * \enum SH_Move Tachometer movement related constants
 */
typedef enum {
  SH_Move_Absolute = 0x00,   /*!< Move the tach to absolute value provided */
  SH_Move_Relative = 0x01   /*!< Move the tach relative to previous position */
} SH_Move;

/*
 * \enum SH_Completion_Wait Whether to wait for motor to finish it's current task or not
 */
typedef enum {
  SH_Completion_Dont_Wait    = 0x00,  /*!< Don't wait for motor to finish, program will continue with next function */
  SH_Completion_Wait_For     = 0x01  /*!< Wait for motor to finish, program will wait until current function finishes it's operation */
} SH_Completion_Wait;

/*
 * Speed constants, these are just convenience constants,
 * You can use any value between 0 and 100.
 */
#define SH_Speed_Full 90
#define SH_Speed_Medium 60
#define SH_Speed_Slow 25

/*
 * EVShield has two banks, and each of them has different I2C address.
 * each bank has 2 motors and 2 sensors.
 *
 */
/*!
  \def SH_Bank_A
	I2C address of bank A
*/
#define SH_Bank_A 0x34
/*!
  \def SH_Bank_B
	I2C address of bank B
*/
#define SH_Bank_B 0x36


/*
 *  Sensor type primitives
 *
 */

 /*!
  \def SH_Type_NONE
	In this type the sensor port is not defined and used.
*/
#define SH_Type_NONE   0x00

#define SH_Type_SWITCH    0x01
 
/*!
  \def SH_Type_ANALOG
	In this type the sensor port is not powered (for sensors like touch sensor).
*/
#define SH_Type_ANALOG   0x02


/*!
  \def SH_Type_LIGHT_REFLECTED
	Used for detection of Refelected Light from Light sensors, 
*/
#define SH_Type_LIGHT_REFLECTED      0x03
/*!
  \def SH_Type_LIGHT_AMBIENT
	Used for detection of ambient Light using the light sensors, 
*/
#define SH_Type_LIGHT_AMBIENT      0x04
/*!
  \def SH_Type_I2C
	In this type the sensor connected should be an i2c device.
*/
#define SH_Type_I2C                 0x09

/*!
  \def SH_Type_COLORFULL 
	In this type the sensor connected is NXT color sensor in color mode
*/
#define SH_Type_COLORFULL            13
/*!
  \def SH_Type_COLORRED   
	In this type the sensor connected is NXT color sensor in RED color mode
*/
#define SH_Type_COLORRED             14
/*!
  \def SH_Type_COLORGREEN     
	In this type the sensor connected is NXT color sensor in GREEN color mode
*/
#define SH_Type_COLORGREEN           15
/*!
  \def SH_Type_COLORBLUE 
	In this type the sensor connected is NXT color sensor in BLUE color mode
*/
#define SH_Type_COLORBLUE            16
/*!
  \def SH_Type_COLORNONE
	In this type the sensor connected is NXT color sensor in ambient light mode
*/
#define SH_Type_COLORNONE            17
/*!
  \def SH_Type_EV3_SWITCH 
	In this type the sensor connected is EV3 touch sensor
*/
#define SH_Type_EV3_SWITCH           18
/*!
  \def SH_Type_EV3
	In this type the sensor connected is EV3 UART sensor
*/
#define SH_Type_EV3                  19



/*
 * Sensor defines.
 */
/*!
  \def SH_S1
	This is used internally to address Sensor Port 1.
	Do not use this in sketches.
	Sketches should use SH_BankPort enums.
*/
#define SH_S1   1
/*!
  \def SH_S2
	This is used internally to address Sensor Port 2.
	Do not use this in sketches.
	Sketches should use SH_BankPort enums.
*/
#define SH_S2   2

#include "EVShieldI2C.h"
#if defined(__AVR__)
  #include <avr/io.h>
  #include <avr/interrupt.h>
#endif

/**
  @brief This class defines methods for the EVShield Bank(s).
  */
class EVShieldBank : public EVShieldI2C
{
public:
  /** Constructor for bank a of the EVShield device */
  EVShieldBank(uint8_t i2c_address = SH_Bank_A);
  
  /** Get the battery voltage (milli-volts) for this bank of the EVShield
    @return voltage value in milli-volts 
    The voltage reported by this function is actual voltage at VIN pin on Arduino
    This will be lower than your supply voltage due to drops at various points in the circuit.
    The drop will be different based on where the power source is connected.
    (i.e. source through EVShield Green connector Vs Arduino black adapater Vs Arduino USB.)
    */
  int  evshieldGetBatteryVoltage();

  /** nxshieldGetBatteryVoltage() is provided for backword compatibility with nxshield programs.
   */
  int  nxshieldGetBatteryVoltage();

  /** 
  Issue a command to this bank of the EVShield
  @param command Refer to user guide for list of commands.
  */
  uint8_t  EVShieldIssueCommand(char command);

  //
  //  Motor Operation APIs.
  //
  /** Set the target encoder position for the motor
    @param which_motor    Provide which motor to operate on
    @param target         Encode value to achieve
  */
  bool     motorSetEncoderTarget(SH_Motor which_motor, long target);
  
  /** 
  Get the target encoder position for the motor
    @param which_motor    Provide which motor to operate on
    @return long encoder value that the motor is trying to achieve.
  */
  long     motorGetEncoderTarget(SH_Motor which_motor);
  
  /** 
  Set the speed of the motor
    @param which_motor    Provide which motor to operate on
    @param speed          The speed value between 0 and 100
  */
  bool     motorSetSpeed(SH_Motor which_motor, int speed);
  
  /** 
  Get the speed of the motor
    @param which_motor    Provide which motor to operate on
    @return  the speed value set to the motor
  */
  int8_t   motorGetSpeed(SH_Motor which_motor);
  
  /** 
  Set the time in seconds for which the motor should run for
    @param which_motor    Provide which motor to operate on
    @param seconds          The time duration the motor should run
  */
  bool     motorSetTimeToRun(SH_Motor which_motor, int seconds);
  
  /** 
  Get the time in seconds that the motor is running for
    @param which_motor    Provide which motor to operate on
    @return  time the motor has been running since last start.
  */
  uint8_t  motorGetTimeToRun(SH_Motor which_motor);
  
  /**
    Set the Command Register B
    There are two command registers, A and B.

		For more information on what register does, please refer to 'Motor Command Register Explained' section of EVShield-Advanced-Development-Guide.pdf from following url:
		http://www.openelectrons.com/index.php?module=documents&JAS_DocumentManager_op=viewDocument&JAS_Document_id=1

    @param which_motor    Provide which motor to operate on
    @param value       The command register value to set
  */
  bool     motorSetCommandRegB(SH_Motor which_motor, uint8_t value);
  /**
    Get the command register B

		For more information on what register does, please refer to 'Motor Command Register Explained' section of EVShield-Advanced-Development-Guide.pdf from following url:
		http://www.openelectrons.com/index.php?module=documents&JAS_DocumentManager_op=viewDocument&JAS_Document_id=1
    @param which_motor    Provide which motor to operate on
    @return the last set command register value.
  */
  uint8_t  motorGetCommandRegB(SH_Motor which_motor);
  /**
    Set the Command Register A
    There are two command registers, A and B.

		For more information on what register does, please refer to 'Motor Command Register Explained' section of EVShield-Advanced-Development-Guide.pdf from following url:
		http://www.openelectrons.com/index.php?module=documents&JAS_DocumentManager_op=viewDocument&JAS_Document_id=1
    @param which_motor    Provide which motor to operate on
    @param value       The command register value to set
    */
  bool     motorSetCommandRegA(SH_Motor which_motor, uint8_t value);
  /**
    Get the command register A

		For more information on what register does, please refer to 'Motor Command Register Explained' section of EVShield-Advanced-Development-Guide.pdf from following url:
		http://www.openelectrons.com/index.php?module=documents&JAS_DocumentManager_op=viewDocument&JAS_Document_id=1
    @param which_motor    Provide which motor to operate on
    @return the last set command register value.
  */
  uint8_t  motorGetCommandRegA(SH_Motor which_motor);
  
  /** 
  Get the current encoder position of the motor in degrees
    @param which_motor    Provide which motor to operate on
    @return              current encoder value
  */
  int32_t  motorGetEncoderPosition(SH_Motor which_motor);
  
  /** 
  Get the current status of the motor
    @param which_motor    Provide which motor to operate on
    @return  The current status of the motor.
    This is a byte with various bits set based on motor's state.
    Refer to User Guide for details of bits.
  */  
  uint8_t  motorGetStatusByte(SH_Motor which_motor);
  
  /** 
  Get the tasks that are running on the specific motor
    @param which_motor    Provide which motor to operate on
    @return  The task byte that's currently running for this motor.
    (Currently only one task is supported.)
  */
  uint8_t  motorGetTasksRunningByte(SH_Motor which_motor);
  
  /** 
  Set the PID control factors for the encoders
  All motors on this bank will use the same PID values.
    @param Kp The proportionate factor of the PID.
    @param Ki The integreal factor of the PID.
    @param Kd The differential factor of the PID.
  */
  bool     motorSetEncoderPID(uint16_t Kp, uint16_t Ki, uint16_t Kd);
  
  /** 
  Set the PID control factors for the speed of the motors
  All motors on this bank will use the same PID values.
    @param Kp The proportionate factor of the PID.
    @param Ki The integreal factor of the PID.
    @param Kd The differential factor of the PID.
  */
  bool     motorSetSpeedPID(uint16_t Kp, uint16_t Ki, uint16_t Kd);
  
  bool centerLedSetRGB(uint8_t R, uint8_t G, uint8_t B);

  // Set the RGBLED that shows RGB color

  bool    ledSetRGB(uint8_t R, uint8_t G, uint8_t B);
  
  /** 
  Set how many times the PID controller is allowed to oscillate at the set point
  Depending on your situation of load and power characteristics, your PID algorithm
  may oscillate indefinitly trying to achieve it's target.
  To prevent that from happening there is a limit set.
    @param pass_count the maximum number of times the PID is allowed to cross it's target.
  */
  bool     motorSetPassCount(uint8_t pass_count);
  
  /** 
  Set how far away from the set point the PID controller is allowed to oscillate (amplitude)
  Depending on your situation of load and power characteristics, your PID algorithm
  may oscillate above or below the target.
    @param tolerance the maximum amplititude allowed.
  */
  bool     motorSetTolerance(uint8_t tolerance);
  
  /** 
  Reset all the set values for the motors
  Applies to all motors on this bank.
  */
  bool     motorReset();
  
  /** 
  Start both motors at the same time to follow the set conditions
  This will execute the commands specified in the command register on both motors at once.
  */
  bool     motorStartBothInSync();
  
  /** 
  Reset the current encoder position to zero for the motor
    @param which_motor    Provide which motor to operate on
  */
  bool     motorResetEncoder(SH_Motor which_motor);
  
  /**
  Set the speed, duration to run, and control for the motor through register A (or B)

		For more information on what register does, please refer to 'Motor Command Register Explained' section of EVShield-Advanced-Development-Guide.pdf from following url:
		http://www.openelectrons.com/index.php?module=documents&JAS_DocumentManager_op=viewDocument&JAS_Document_id=1
    @param which_motors    Provide which motor(s) to operate on
    @param speed          Speed value between 0 and 100
    @param duration       time to run in seconds
    @param control        command register value
  */
  bool     motorSetSpeedTimeAndControl(SH_Motor which_motors, int speed,
                                      uint8_t duration, uint8_t control);

  /** 
 This function sets the speed, the number of seconds, and
 the control (a.k.a. command register A)

		For more information on what register does, please refer to 'Motor Command Register Explained' section of EVShield-Advanced-Development-Guide.pdf from following url:
		http://www.openelectrons.com/index.php?module=documents&JAS_DocumentManager_op=viewDocument&JAS_Document_id=1
    @param which_motors    Provide which motor(s) to operate on
    @param encoder        Target encoder position to achieve
    @param speed          Speed value between 0 and 100
    @param duration       time to run in seconds
    @param control        command register value
  */
  bool     motorSetEncoderSpeedTimeAndControl(SH_Motor which_motors,
                                      long encoder, int speed,
                                      uint8_t duration, uint8_t control);
  
  /**
  Validate if the motor has finished running for the set time duration
    @param which_motors    Provide which motor(s) to operate on
    @return                0 when motor(s) has completed a timed move properly,
    If the return value is non-zero, either motor has not finished yet or has encountered an error condition.
  */
  uint8_t     motorIsTimeDone(SH_Motor which_motors);
  
  /**
  Wait until the motor has finished running for its set respective time duration
    @param which_motors    Provide which motor(s) to operate on
    @return                function waits until when motor(s) has stopped, returns 0 if the set goal was achieved.
    If the return value is non-zero, you should check for error condition such as stall.
  */
  uint8_t     motorWaitUntilTimeDone(SH_Motor which_motors);
  
  /**
  Validate if the motor has reached its set target tachometer position
    @param which_motors    Provide which motor(s) to operate on
    @return                0 when motor(s) has completed a encoder based move properly,
    If the return value is non-zero, either motor has not finished yet or has encountered an error condition.
  */
  uint8_t     motorIsTachoDone(SH_Motor which_motors);
  
  /** 
  Wait until the motor has reached its set target tachometer position
    @param which_motors    Provide which motor(s) to operate on
    @return                function waits until when motor(s) has stopped, returns 0 if the set goal was achieved.
    If the return value is non-zero, you should check for error condition such as stall.
  */
  uint8_t     motorWaitUntilTachoDone(SH_Motor which_motors);
  
  /**
  Run the motor endlessly at the desired speed in the desired direction
   @param which_motors     specifiy the motor(s) to operate on
   @param direction        specifiy the direction to run the motor
   @param speed            the speed value (between 0 and 100)
   @return  Starts the motors and function returns immediately
  */
  void     motorRunUnlimited(SH_Motor which_motors, SH_Direction direction,
                                      int speed);
                                      
  /** Run the motor for a set duration at a set speed and do the next action
   @param which_motors     specifiy the motor(s) to operate on
   @param direction        specifiy the direction to run the motor
   @param speed            the speed value (between 0 and 100)
   @param duration         in seconds
   @param wait_for_completion    whether this API should wait for competion or not
   @param next_action      for these motor being operated on
   @return        0 if the operation was finished satisfactorily,
            in case return value is non-zero you should check for the bits for error conditions.
  */
  uint8_t     motorRunSeconds(SH_Motor which_motors, SH_Direction direction,
                                      int speed, uint8_t duration,
                                      SH_Completion_Wait wait_for_completion,
                                      SH_Next_Action next_action);
                                      
  /**
  run until the tachometer target has been reached and do next action
   @param which_motors     specifiy the motor(s) to operate on
   @param direction        specifiy the direction to run the motor
   @param speed            the speed value (between 0 and 100)
   @param tachometer       the target for the encoder value to achieve.
   @param relative         is the tachometer relative or absolute.
   @param wait_for_completion    whether this API should wait for competion or not
   @param next_action      for these motor being operated on
   @return        0 if the operation was finished satisfactorily,
            in case return value is non-zero you should check for the bits for error conditions.
  */
  uint8_t     motorRunTachometer(SH_Motor which_motors, SH_Direction direction,
                                      int speed, long tachometer,
                                      SH_Move relative,
                                      SH_Completion_Wait wait_for_completion,
                                      SH_Next_Action next_action);
                                      
  /**
  Run the motor for a set number of degrees and proceed to the next action
   @param which_motors     specifiy the motor(s) to operate on
   @param direction        specifiy the direction to run the motor
   @param speed            the speed value (between 0 and 100)
   @param degrees          The degrees the motor should turn through
   @param wait_for_completion    whether this API should wait for competion or not
   @param next_action      for these motor being operated on
   @return        0 if the operation was finished satisfactorily,
            in case return value is non-zero you should check for the bits for error conditions.
  */
  uint8_t     motorRunDegrees(SH_Motor which_motors, SH_Direction direction,
                                      int  speed, long degrees,
                                      SH_Completion_Wait wait_for_completion,
                                      SH_Next_Action next_action);
                                      
  /**
  Run the motor for a set number of complete rotations and proceed to the next action
   @param which_motors     specifiy the motor(s) to operate on
   @param direction        specifiy the direction to run the motor
   @param speed            the speed value (between 0 and 100)
   @param rotations        The rotations the motor should rotate through
   @param wait_for_completion    whether this API should wait for competion or not
   @param next_action      for these motor being operated on
   @return        0 if the operation was finished satisfactorily,
            in case return value is non-zero you should check for the bits for error conditions.
  */
  uint8_t     motorRunRotations(SH_Motor which_motors, SH_Direction direction,
                                      int speed, long rotations,
                                      SH_Completion_Wait wait_for_completion,
                                      SH_Next_Action next_action);
                                      
  /**
  stop the motor and do the next action
   @param which_motors     specifiy the motor(s) to operate on
   @param next_action      for these motor being operated on
  */
  bool     motorStop(SH_Motor which_motors, SH_Next_Action next_action);


  //
  // EVShield sensor functions.
  //
public:
  /**
  Set the sensor type of the sensor on this bank
  @param  which_sensor the sensor to set the type to.
  @param  sensor_type     type value of the sensor,
  refer to Advanced User Guide for available values of sensor types.
  */
  bool     sensorSetType(uint8_t which_sensor, uint8_t sensor_type);
  
  /**
  Read the raw analog value from the sensor and return as an int
  @param  which_sensor the sensor to read the raw value from
  @return   raw value from the sensor
  */
  int      sensorReadRaw(uint8_t which_sensor);

};

/**
  @brief EVShield has two banks. Bank B has few differences from Bank A.
  This class defines overriding methods for the EVShield Bank B.
  */
class EVShieldBankB : public EVShieldBank
{
private:

public:
  /** constructor for bank be of the EVShield; optional custom i2c address can be supplied */
  EVShieldBankB(uint8_t i2c_address_b = SH_Bank_B);
  /**
  Read the raw analog value from the sensor and return as an int
  @param  which_sensor the sensor to read the raw value from
  @return   raw value from the sensor
  */
  int      sensorReadRaw(uint8_t which_sensor);

  /**
  Set the sensor Type of the sensor on this bank
  @param  which_sensor the sensor to set the type to.
  @param  sensor_type     type value of the sensor,
  refer to Advanced User Guide for available values of sensor types.
  */
  bool     sensorSetType(uint8_t which_sensor, uint8_t sensor_type);
};


/**
  @brief This class defines methods to access EVShield features
*/
class EVShield
{
public:
  /**
  Global variable representing the i2c protocol to use; whether software or hardware
  */
  uint8_t m_protocol;
  /** Variable for the bank_a of EVShield
  */
  EVShieldBank   bank_a;
  /** Variable for the bank_b of EVShield
  */
  EVShieldBankB  bank_b;

  /** class constructor for EVShield; optional custom i2c addresses may be supplied for both banks */
  EVShield(uint8_t i2c_address_a = SH_Bank_A,
           uint8_t i2c_address_b = SH_Bank_B);
  
  /**
  the initialization of the EVShield; 
	This function initializes the LED related timers, and communication protocols.
  @param protocol optional, specify the i2c protocol to use for the EVShield and highspeed i2c port
  */
  void init(SH_Protocols protocol=SH_HardwareI2C);

  /**
  the initialization of the EVShield LED timers.
  */
	void initLEDTimers();

  /**
    the initialization of the EVShield I2C timer.
  */
	void I2CTimer();
    
  /**
  the initialization of EVShield communication protocols.
  @param protocol optional, specify the i2c protocol to use for the EVShield and highspeed i2c port
  */
	void initProtocols(SH_Protocols protocol=SH_HardwareI2C);

  
  /**
  Get the button state of the specific button on EVShield.
  @param btn      Button to get state for (BTN_GO, BTN_LEFT, BTN_RIGHT)
  @return true or false for specified button on the EVShield 
  */
  bool getButtonState(uint8_t btn);
  
  /** 
  Wait inside function until specified button is pressed on EVShield (BTN_GO, BTN_LEFT, BTN_RIGHT)
  @param btn      Button to get state for (BTN_GO, BTN_LEFT, BTN_RIGHT)
  @param led_pattern   0 for LED off.
  1 to brighten/lighten LED with breathing pattern (default).
  2 to brighten/lighten LED with heart beat pattern.
  */
  void waitForButtonPress(uint8_t btn, uint8_t led_pattern=0);
  

  /**
  Set the colors of LED on the EVShield;
  The values of red, green, blue are between 0 to 8 (for 8 intensity levels).
  @param red      Intensity for red color (between 0 and 8)
  @param green      Intensity for green color (between 0 and 8)
  @param blue      Intensity for blue color (between 0 and 8)
  */
  void ledSetRGB(uint8_t red = 0, uint8_t green = 0, uint8_t blue = 0);

  /**
    The LED is brightened and dimmed in a breathing pattern.
    Call this function repeatedly to make the pattern.
  */
  void ledBreathingPattern();

  /**
    The LED is brightened and dimmed in a HeartBeat pattern.
    Call this function repeatedly to make the pattern.
  */
  void ledHeartBeatPattern();
};

/** This function formats an integer in binary format.
  @param i 8 bit integer value
  @param s returned string of the binary representation
  */
extern bool format_bin(uint8_t i, char *s);

#endif
