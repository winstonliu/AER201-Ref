#include "Arduino.h"
#include "motor.h"

motor::motor(int pin_enable, int pin_direction, int speed)
{
	enable = pin_enable;
	direction = pin_direction;
	motorspeed = 255;

	// Enable motor pins
	pinMode(enable, OUTPUT);
	pinMode(direction, OUTPUT);
}

void motor::stop()
{
	motorspeed = 0;
	status = MOTOR_OFF;
    digitalWrite(enable, LOW);
    digitalWrite(direction, LOW);    
}

void motor::right(int speed)
{
	status = MOTOR_RIGHT;
	motorspeed = speed;

	// PWM
	analogWrite(enable, speed);
    digitalWrite(direction, LOW);
}

void motor::left(int speed)
{
	status = MOTOR_LEFT;
	motorspeed = speed;

	// PWM
	analogWrite(enable, speed);
    digitalWrite(direction, HIGH);
}

void motor::adjustSpeed(int speed)
{
	motorspeed = speed;
	switch(status)
	{
		case MOTOR_RIGHT:
			right(speed);
			break;
		case MOTOR_LEFT:
			left(speed);
			break;
	}	
}

void motor::reverseDirection(int speed)
{
	motorspeed = speed;
	switch(status)
	{
		case MOTOR_RIGHT:
			left(speed);
			break;
		case MOTOR_LEFT:
			right(speed);
			break;
	}	
}

motor_states motor::get_status() { return status; }
