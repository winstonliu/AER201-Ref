#pragma once

#include "sensor.h"

class IRSensor: public Sensor
{
	private:
		static const int readingSize = 3;
		int sensorReadings[readingSize]; // Perform 3 readings
		int prevState;
		int cyclesPast;
		int numCyclesTrack;
		int blackthresh; // for ~4.7k
	public:
		IRSensor() {};
		IRSensor(int pin, int numCyclesTrack = 1);
		void dynamicCalibration();
		int readSensor(); // overload
		int detect();
		int pastEncounters();	
};
