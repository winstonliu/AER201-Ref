#include "line_pid.h"

int mapLinePid(bool l, bool m, bool r) 
{
	int state;
	//static int state = 0;
	// false is 0, true is 1
	
	/*
	// 000
	if ((l|m|r) == ON_WHITE)
		state = ((state > 0) ? 3 : -3);
	*/
	// 110
	if ((!l|!m|r) == ON_WHITE)
		state = 20;
	// 001
	else if ((l|m|!r) == ON_WHITE)
		state = 10;
	// 010 or 111 or 000
	else if ((l|!m|r) == ON_WHITE || (!l|!m|!r) == ON_WHITE || (l|m|r) == ON_WHITE)
		state = 0;
	// 100
	else if ((!l|m|r) == ON_WHITE)
		state = -10;
	// 011
	else if ((l|!m|!r) == ON_WHITE)
		state = -20;

	return state;
}
