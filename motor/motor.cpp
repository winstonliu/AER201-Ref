#include "Arduino.h"
#include "motor.h"

motor::motor(int pin_enable, int pin_direction)
{
	enable = pin_enable;
	direction = pin_direction;

	// Enable motor pins
	pinMode(enable, OUTPUT);
	pinMode(direction, OUTPUT);
}

void motor::stop()
{
	status = MOTOR_OFF;
    digitalWrite(enable, LOW);
    digitalWrite(direction, LOW);    
}

void motor::right(int speed)
{
	status = MOTOR_RIGHT;

	// PWM
	if (speed < 255)
		analogWrite(enable, speed);
	else
		digitalWrite(enable, HIGH);

    digitalWrite(direction, LOW);
}

void motor::left(int speed)
{
	status = MOTOR_LEFT;

	// PWM
	if (speed < 255)
		analogWrite(enable, speed);
	else
		digitalWrite(enable, HIGH);

    digitalWrite(direction, HIGH);    
}

void motor::adjustSpeed(int speed)
{
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

motor_states motor::get_status() 
{ 
	return status; 
}
