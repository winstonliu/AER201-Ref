#include "irsensor.h"

IRSensor::IRSensor(int sv, int nct):Sensor(sv), numCyclesTrack(nct) {};

int IRSensor::readSensor()
{
	int avg = 0;
	for (int i = 0; i < readingSize; ++i)
	{
		sensorReadings[i] = analogRead(sensorPin);	
		avg += sensorReadings[i];
	}
	avg /= readingSize;
	
	return avg;
}

int IRSensor::detect()
{
	int numBlack = 0;
	int retVal;
	for (int i = 0; i < readingSize; ++i)
	{
		if (sensorReadings[i] > blackthresh) ++numBlack;
	}

	return ((numBlack >=  2) ? BLACK : WHITE);
}

void IRSensor::dynamicCalibration()
{
	const int cycles = 10;
	int valmax = 0;
	int valmin = 1000;
	int sum = 0;
	int avg;
	// White is lowest value, black is highest value. Red is always 0
	for (int i = 0; i < cycles; ++i)
	{
		sum += readSensor();			
	}
	avg = sum / cycles;	
}

// May not be necessary
int IRSensor::pastEncounters()
{
	if (prevState != BLACK)
		cyclesPast = numCyclesTrack;
	else if (cyclesPast > 0)
		--cyclesPast;

	if (cyclesPast > 0)
		return WHITE;
	else
		return BLACK;
}
