#include "nav.h"

nav::nav(grid start_position)
{
	currentGrid = start_position;	
	destination = start_position;
	currentAction = IDLE;
}

// Check the validity of grid coordinates
bool nav::check_validity(grid coordinates)
{
	if (coordinates.x < 1 || coordinates.x > 7)
		return false;
	else if (coordinates.y < 1 || coordinates.y > 8)
		return false;
	else if (coordinates.d < 0 || coordinates.d > 359)
		return false;
	else
		return true;
}

// FOR EMERGENCIES ONLY, reset grid coordinates
int nav::reset(grid new_position)
{
	if (nav::check_validity(new_position) == true)
	{
		currentGrid = new_position;
		return 0;
	}
	return -1;
}

// Set next destination coordinates of the robot
int nav::set_destination(grid new_destination)
{
	if (nav::check_validity(new_destination) == true)
	{
		destination = new_destination;
		return 0;
	}
	return -1;
}

grid nav::directionalLineIncrement(int i)
{
	grid temp_grid = currentGrid;
	switch(currentGrid.d)
	{
		case 0:
			temp_grid.y + i;
			break;
		case 90:
			temp_grid.x + i;
			break;
		case 180:
			temp_grid.y - i;
			break;
		case 270:
			temp_grid.x - i;
			break;
	}
	return temp_grid;
}

int nav::interrupt(isr senInt)
{
	// Forward drive intersects line
	if (senInt == LINE_ISR && currentAction == MOVEFORWARD)	
	{
		grid new_grid = directionalLineIncrement(1);
		if (check_validity(new_grid) == true)
		{
			currentGrid = new_grid;
		}
	}
	// Rotation intersects line
	else if (senInt == LINE_ISR && currentAction == ROTATETO)
	{
		// XXX Assuming that the robot only turns to the left
		currentGrid.d = (currentGrid.d - 90) % 360;
	}
}

int nav::computeRectilinearPath(grid new_destination)
{
	// Check validity and set destination
	if (set_destination(new_destination) == -1)
		return -1;

	// Computes the path the robot will take
	int next_xd;
	int next_yd;
	task thendo;
	grid difference;

	difference.x = destination.x - currentGrid.x;
	difference.y = destination.y - currentGrid.y;	

	// Calculate taxicab distance
	// XXX Does not take into account hopper locations
	
	if (difference.x < 0) // destination is WEST
	{
		next_xd = 270;
	}
	else if (difference.x > 0) // destination is EAST
	{
		next_xd = 90;
	}

	if (difference.y < 0) // destination is SOUTH
	{
		next_yd = 180;
	}
	else if (difference.x > 0) // destination is NORTH
	{
		next_yd = 0;
	}

	// Rotate to face x
	thendo.do_now = ROTATETO;		
	thendo.value = next_xd;
	tasklist.push(thendo);

	// Move x
	thendo.do_now = MOVEFORWARD;
	thendo.value = difference.x;
	tasklist.push(thendo);

	// Rotate to face y
	thendo.do_now = ROTATETO;		
	thendo.value = next_yd;
	tasklist.push(thendo);

	// Move y
	thendo.do_now = MOVEFORWARD;
	thendo.value = difference.y;
	tasklist.push(thendo);

	// Rotate to face final
	thendo.do_now = ROTATETO;		
	thendo.value = destination.d;
	tasklist.push(thendo);

	return 0;
}

void nav::startTask()
{
	currentAction = tasklist.peek().do_now;
	taskdestination = directionalLineIncrement(tasklist.peek().value);
}

int nav::checkTaskComplete() 
{ 
	if (currentGrid == taskdestination)
	{
		tasklist.pop(); 
		currentAction = IDLE;
		return 0;
	}
}

bool nav::doneTasks() { return tasklist.isEmpty(); }
int nav::countRemaining() { return tasklist.count(); }
action nav::getAction() { return currentAction; }
grid nav::getGrid() { return currentGrid; }
grid nav::getDestination() { return destination; }
