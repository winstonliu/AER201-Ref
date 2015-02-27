#pragma once

enum motor_states
{
	MOTOR_RIGHT,
	MOTOR_LEFT,
	MOTOR_OFF
};

class motor
{
	private:
		int enable;
		int direction;
		motor_states status;
	public:
		motor(int pin_enable, int pin_direction);	
		void stop();
		// LOW direction pin implies rightward rotation
		void right(int speed = 255);
		// HIGH direction pin implies leftward rotation
		void left(int speed = 255);
		void adjustSpeed(int speed = 255);
		motor_states get_status();
};