#pragma once

#include "sensor.h"

class IRSensor: public Sensor
{
	private:
		int prevState;
		int numCyclesTrack;
	public:
		IRSensor() {};
		IRSensor(int pin, int numCyclesTrack = 1);
		int detect(int black_white_diff_thresh = 100);
		int pastEncounters();	
};
