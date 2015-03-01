#pragma once

#include "sensor.h"

class IRSensor: public Sensor
{
	private:
		int prevState;
		int numCyclesTrack;
	public:
		IRSensor() {};
		IRSensor(int pin, int numCyclesTrack = 3);
		int detect(int black_white_diff_thresh = 500);
		int pastEncounters();	
};
