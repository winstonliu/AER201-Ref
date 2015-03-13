#include "irsensor.h"

IRSensor::IRSensor(int sv, int nct):Sensor(sv), numCyclesTrack(nct) {};

int IRSensor::detect(int diffThresh)
{
	int wdiff = pow(sensorVal - thresh[WHITE], 2);
	int bdiff = pow(sensorVal - thresh[BLACK], 2);

	if (bdiff < diffThresh)
		prevState = BLACK;
	else
		prevState = WHITE;

	return prevState;
}

int IRSensor::pastEncounters()
{
	// Counts the number of past cycles that sensors has read black
	static int cyclesPast = 0;

	if (prevState != BLACK)
		cyclesPast = numCyclesTrack;
	else if (cyclesPast > 0)
		--cyclesPast;

	if (cyclesPast > 0)
		return WHITE;
	else
		return BLACK;
}
