
// EVs_NXTMMX.cpp
//
// Initial version: 2010-06-07 by Clinton Blackmore
// Modified for EVShield: 2015-02-16 by Michael Giles
// Corrected encoder cast: 2017-02-08 by Seth Tenembaum
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

#include "EVs_NXTMMX.h"


EVs_NXTMMX::EVs_NXTMMX(uint8_t i2c_address)
: EVShieldI2C(i2c_address)
{
	// for some reason the reset command doesn't work here
	//reset();	// start all encoder positions off at 0
}

uint8_t EVs_NXTMMX::getBatteryVoltage()
{
	return readByte(MMX_VOLTAGE)*39;
}

uint8_t EVs_NXTMMX::issueCommand(char command)
{
	return writeByte(MMX_COMMAND, (uint8_t)command);
}

// Set/get the encoder target for the motor (ie. a position to go
// to and stop at)
bool EVs_NXTMMX::setEncoderTarget(uint8_t which_motor, long target)
{
	uint8_t reg = (which_motor == MMX_Motor_1) ? MMX_SETPT_M1 : MMX_SETPT_M2; 
	return writeLong(reg, target);
}
long EVs_NXTMMX::getEncoderTarget(uint8_t which_motor)
{
	uint8_t reg = (which_motor == MMX_Motor_1) ? MMX_SETPT_M1 : MMX_SETPT_M2; 
	return (long)readLong(reg);
}

// Set/get the speed of the motor
// (I believe this is in the range [-100, +100])
bool EVs_NXTMMX::setSpeed(uint8_t which_motor, int speed)
{
	uint8_t reg = (which_motor == MMX_Motor_1) ? MMX_SPEED_M1 : MMX_SPEED_M2; 
	return writeByte(reg, (uint8_t)(int8_t)speed);
}
int8_t EVs_NXTMMX::getSpeed(uint8_t which_motor)
{
	uint8_t reg = (which_motor == MMX_Motor_1) ? MMX_SPEED_M1 : MMX_SPEED_M2; 
	return (int8_t)readByte(reg);
}

// This is the time, in seconds, for the motor to run
bool EVs_NXTMMX::getTimeToRun(uint8_t which_motor, int seconds)
{
	uint8_t reg = (which_motor == MMX_Motor_1) ? MMX_TIME_M1 : MMX_TIME_M2; 
	return writeByte(reg, seconds);
}
uint8_t EVs_NXTMMX::getTimeToRun(uint8_t which_motor)
{
	uint8_t reg = (which_motor == MMX_Motor_1) ? MMX_TIME_M1 : MMX_TIME_M2; 
	return readByte(reg);
}

// Command Register 'B' is currently unused, but reserved for future expansion
// If you set it, you must set it to zero.
bool EVs_NXTMMX::setCommandRegB(uint8_t which_motor, uint8_t value)
{
	uint8_t reg = (which_motor == MMX_Motor_1) ? MMX_CMD_B_M1 : MMX_CMD_B_M2; 
	return writeByte(reg, value);
}
uint8_t EVs_NXTMMX::getCommandRegB(uint8_t which_motor)
{
	uint8_t reg = (which_motor == MMX_Motor_1) ? MMX_CMD_B_M1 : MMX_CMD_B_M2; 
	return readByte(reg);
}

// See User's Guide for what command register A does
bool EVs_NXTMMX::setCommandRegA(uint8_t which_motor, uint8_t value)
{
	uint8_t reg = (which_motor == MMX_Motor_1) ? MMX_CMD_A_M1 : MMX_CMD_A_M2; 
	return writeByte(reg, value);
}
uint8_t EVs_NXTMMX::getCommandRegA(uint8_t which_motor)
{
	uint8_t reg = (which_motor == MMX_Motor_1) ? MMX_CMD_A_M1 : MMX_CMD_A_M2; 
	return readByte(reg);
}

// Get the current encoder position
int32_t EVs_NXTMMX::getEncoderPosition(uint8_t which_motor)
{
	uint8_t location = (which_motor == MMX_Motor_1) ? MMX_POSITION_M1 : MMX_POSITION_M2;
	return (int32_t)readLong(location);
}

// See User's Guide for documentation on the status byte
uint8_t EVs_NXTMMX::getMotorStatusByte(uint8_t which_motor)
{
	uint8_t location = (which_motor == MMX_Motor_1) ? MMX_STATUS_M1 : MMX_STATUS_M2;
	return readByte(location);
}

// (I couldn't find an explanation for this in the User's Guide)
uint8_t EVs_NXTMMX::getMotorTasksRunningByte(uint8_t which_motor)
{
	uint8_t location = (which_motor == MMX_Motor_1) ? MMX_TASKS_M1 : MMX_TASKS_M2;
	return readByte(location);
}

// Set the PID that controls how we stop as we approach the
// angle we're set to stop at
bool EVs_NXTMMX::setEncoderPID(uint16_t Kp, uint16_t Ki, uint16_t Kd)
{
	writeIntToBuffer(_buffer + 0, Kp);
	writeIntToBuffer(_buffer + 2, Ki);
	writeIntToBuffer(_buffer + 4, Kd);
	return writeRegisters(MMX_ENCODER_PID, 6, _buffer);
}

// Sets the PID that controls how well that motor maintains its speed
bool EVs_NXTMMX::setSpeedPID(uint16_t Kp, uint16_t Ki, uint16_t Kd)
{
	writeIntToBuffer(_buffer + 0, Kp);
	writeIntToBuffer(_buffer + 2, Ki);
	writeIntToBuffer(_buffer + 4, Kd);
	return writeRegisters(MMX_SPEED_PID, 6, _buffer);
}

// See user's guide for details.
bool EVs_NXTMMX::setPassCount(uint8_t pass_count)
{
	return writeByte(MMX_PASS_COUNT, pass_count);
}

// Sets tolerance which adjust accuracy while positioning.
// See user's guide for more details.
bool EVs_NXTMMX::setTolerance(uint8_t tolerance)
{
	return writeByte(MMX_TOLERANCE, tolerance);
}


// Special I2C commands

// Resets all encoder values and motor parameters.  Leaves PIDs untouched.
bool EVs_NXTMMX::reset()
{
	return issueCommand('R');
}

// Tells the motors to start at the same time.
bool EVs_NXTMMX::startMotorsInSync()
{
	return issueCommand('S');
}

// Reset the encoder for motor 1 or motor 2
bool EVs_NXTMMX::resetEncoder(uint8_t which_motor)
{
	char code = (which_motor == MMX_Motor_1) ? 'r' : 's';
	return issueCommand(code);
}


// This function sets the speed, the number of seconds, and
// the control (a.k.a. command register A)
bool EVs_NXTMMX::setSpeedTimeAndControl(
	uint8_t which_motors,	// MMX_Motor_ 1, 2, or Both
	int     speed,			// in range [-100, +100]
	uint8_t duration,		// in seconds
	uint8_t control)		// bit flags for control purposes
{
	if (which_motors == MMX_Motor_Both)
	{
		control &= ~MMX_CONTROL_GO;	// Clear the 'go right now' flag
		bool m1 = setSpeedTimeAndControl(MMX_Motor_1, speed, duration, control);
		bool m2 = setSpeedTimeAndControl(MMX_Motor_2, speed, duration, control);
		startMotorsInSync();
		return m1 && m2;
	}

	_buffer[0] = (uint8_t)(int8_t)speed;
	_buffer[1] = duration;
	_buffer[2] = 0;			// command register B
	_buffer[3] = control;	// command register A

	uint8_t reg = (which_motors == MMX_Motor_1) ? MMX_SPEED_M1 : MMX_SPEED_M2;
	return writeRegisters(reg, 4);
}

void setEncoderSpeedTimeAndControlInBuffer(
	uint8_t* buffer,	// pointer to the buffer
	long 	encoder,	// encoder value
	int 	speed,		// speed, in range [-100, +100]
	uint8_t duration,	// in seconds
	uint8_t control)	// control flags
{
	writeLongToBuffer(buffer + 0, (uint32_t)(int32_t)encoder);
	buffer[4] = (uint8_t)(int8_t)speed;
	buffer[5] = duration;
	buffer[6] = 0;			// command register B
	buffer[7] = control;	// command register A
}


// This function sets the speed, the number of seconds, and
// the control (a.k.a. command register A)
bool EVs_NXTMMX::setEncoderSpeedTimeAndControl(
	uint8_t which_motors,	// MMX_Motor_ 1, 2, or Both
	long  	encoder,		// encoder/tachometer position
	int  	speed,			// speed, in range [-100, +100]
	uint8_t duration,		// in seconds
	uint8_t control)		// control flags
{
	if (which_motors == MMX_Motor_Both)
	{
		// The motor control registers are back to back, and both can be written in one command
		control &= ~MMX_CONTROL_GO;	// Clear the 'go right now' flag
		setEncoderSpeedTimeAndControlInBuffer(_buffer + 0, encoder, speed, duration, control);
		setEncoderSpeedTimeAndControlInBuffer(_buffer + 8, encoder, speed, duration, control);
		bool success = writeRegisters(MMX_SETPT_M1, 16);
		startMotorsInSync();
		return success;
	}

	// Or, just issue the command for one motor
	setEncoderSpeedTimeAndControlInBuffer(_buffer, encoder, speed, duration, control);
	uint8_t reg = (which_motors == MMX_Motor_1) ? MMX_SETPT_M1 : MMX_SETPT_M2;
	return writeRegisters(reg, 8);
}

// True when a motor has completed a timed move
bool EVs_NXTMMX::isTimeDone(uint8_t which_motors)
{
	if (which_motors == MMX_Motor_Both)
	{
		return isTimeDone(MMX_Motor_1) && isTimeDone(MMX_Motor_2);
	}
	uint8_t status = getMotorStatusByte(which_motors);
	return (status & MMX_CONTROL_TIME) == 0;
}

// waited until a timed command finishes
void EVs_NXTMMX::waitUntilTimeDone(uint8_t which_motors)
{
	delay(50);	// this delay is required for the status byte to be available for reading.
	while (!isTimeDone(which_motors)) delay(50);
}

// True when a command based on using the motor encoder completes
bool EVs_NXTMMX::isTachoDone(uint8_t which_motors)
{
	if (which_motors == MMX_Motor_Both)
	{
		return isTachoDone(MMX_Motor_1) && isTachoDone(MMX_Motor_2);
	}
	uint8_t status = getMotorStatusByte(which_motors);
	return (status & MMX_CONTROL_TACHO) == 0;
}

// waited until a turn-by-degrees command ends
void EVs_NXTMMX::waitUntilTachoDone(uint8_t which_motors)
{
	delay(50);	// this delay is required for the status byte to be available for reading.
	while (!isTachoDone(which_motors)) delay(50);
}


// Utility functions for motor control

// Take a speed and direction and give just a speed
inline int calcFinalSpeed(int initialSpeed, uint8_t direction)
{
	if (direction == MMX_Direction_Forward)
		return initialSpeed;
	return -initialSpeed;
}

// Calculate the bits that control what happens when this action finishes
inline uint8_t calcNextActionBits(uint8_t next_action)
{
	if (next_action == MMX_Next_Action_Brake)
		return MMX_CONTROL_BRK;
	else if (next_action == MMX_Next_Action_BrakeHold)
		return MMX_CONTROL_BRK | MMX_CONTROL_ON;
}

void EVs_NXTMMX::runUnlimited(
	uint8_t which_motors,			// MMX_Motor_ 1, 2, or Both
	uint8_t direction,				// MMX_Direction_ Forward or Reverse
	int 	speed)					// in range [-100, +100]
{
	uint8_t ctrl = MMX_CONTROL_SPEED | MMX_CONTROL_GO;
	int sp = calcFinalSpeed(speed, direction);
	setSpeedTimeAndControl(which_motors, sp, 0, ctrl);
}

// runs the motors for a given number of seconds
void EVs_NXTMMX::runSeconds(
		uint8_t which_motors,			// MMX_Motor_ 1, 2, or Both
		uint8_t direction,				// MMX_Direction_ Forward or Reverse
		int	 	speed,					// [-100, +100]
		uint8_t duration,				// in seconds
		uint8_t wait_for_completion,	// MMX_Completion_ Wait_For or Dont_Wait
		uint8_t next_action)			// MMX_Next_Action_ Brake, BrakeHold or Float
{
	uint8_t ctrl = MMX_CONTROL_SPEED | MMX_CONTROL_TIME | MMX_CONTROL_GO;
	ctrl |= calcNextActionBits(next_action);
	int sp = calcFinalSpeed(speed, direction);
	setSpeedTimeAndControl(which_motors, sp, duration, ctrl);

	if (wait_for_completion == MMX_Completion_Wait_For)
	{
		waitUntilTimeDone(which_motors);
	}
}

// runs the motors until the tachometer reaches a certain position
void EVs_NXTMMX::runTachometer(
		uint8_t which_motors,			// MMX_Motor_ 1, 2, or Both
		uint8_t direction,				// MMX_Direction_ Forward or Reverse
		int 	speed,					// [-100, +100]
		long    tachometer,				// in degrees
		uint8_t relative,				// MMX_Move_ Relative or Absolute
		uint8_t wait_for_completion,	// MMX_Completion_ Wait_For or Dont_Wait
		uint8_t next_action)			// MMX_Next_Action_ Brake, BrakeHold or Float
{
	uint8_t ctrl = MMX_CONTROL_SPEED | MMX_CONTROL_TACHO | MMX_CONTROL_GO;
	ctrl |= calcNextActionBits(next_action);
	int final_speed = calcFinalSpeed(speed, direction);

	// The tachometer can be absolute or relative.
	// If it is absolute, we ignore the direction parameter.
	long final_tach = tachometer;

	if (relative == MMX_Move_Relative)
	{
		ctrl |= MMX_CONTROL_RELATIVE;

		// a (relative) forward command is always a positive tachometer reading
		final_tach = abs(tachometer);
		if (final_speed < 0)
		{
			// and a (relative) reverse command is always negative
			final_tach = -final_tach;
		}
	}

	setEncoderSpeedTimeAndControl(which_motors, final_tach, final_speed, 0, ctrl);

	if (wait_for_completion == MMX_Completion_Wait_For)
	{
		waitUntilTachoDone(which_motors);
	}
}

// Turns the motors the specified number of degrees
void EVs_NXTMMX::runDegrees(
		uint8_t which_motors,			// MMX_Motor_ 1, 2, or Both
		uint8_t direction,				// MMX_Direction_ Forward or Reverse
		int 	speed,					// [-100, +100]
		long    degrees,				// in degrees
		uint8_t wait_for_completion,	// MMX_Completion_ Wait_For or Dont_Wait
		uint8_t next_action)			// MMX_Next_Action_ Brake, BrakeHold or Float
{
	runTachometer(which_motors, direction, speed, degrees,
			MMX_Move_Relative, wait_for_completion, next_action);
}

// runs the motor(s) the specified number of rotations
void EVs_NXTMMX::runRotations(
		uint8_t which_motors,			// MMX_Motor_ 1, 2, or Both
		uint8_t direction,				// MMX_Direction_ Forward or Reverse
		int 	speed,					// [-100, +100]
		long    rotations,				// number of full rotations of the motor
		uint8_t wait_for_completion,	// MMX_Completion_ Wait_For or Dont_Wait
		uint8_t next_action)			// MMX_Next_Action_ Brake, BrakeHold or Float
{
	runTachometer(which_motors, direction, speed, 360 * rotations,
			MMX_Move_Relative, wait_for_completion, next_action);
}

// The stop command will only stop the motor(s) by making them float/coast
// or brake.  Even if you specify MMX_Next_Action_BrakeHold, the motor
// will only brake, not hold.
bool EVs_NXTMMX::stop(uint8_t which_motors, uint8_t next_action)
{
	if (which_motors >= MMX_Motor_1 && which_motors <= MMX_Motor_Both)
	{
		// The magic variables become clear in the user's guide
		uint8_t base_code = (next_action != MMX_Next_Action_Float) ? 'A' - 1 : 'a' - 1;

		return issueCommand(base_code + which_motors);
	}

	setWriteErrorCode(5);	// bad parameters
	return false;
}
