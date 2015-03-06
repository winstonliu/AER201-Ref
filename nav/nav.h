#pragma once
#include <QueueArray.h>

enum isr
{
	LINE_ISR,
	TOUCH_ISR
};

enum action
{
	MOVEONGRID,
	MOVEOFFGRID, // 1 forward, 0 reverse
	ROTATETO,
	HOPPERALIGN,
	CLAWMOVE, // 1 extend, 0 retract
	PAUSE,
	IDLE
};

struct task
{
	action do_now;
	int value;

	task(action a, int v) : do_now(a), value(v) {}
};

struct grid
{
	int x;	// x coordinates
	int y;  // y coordinates
	int d;	// 0 to 359, N:0, E:90, S:180, W:270

	grid() {}
	grid(int a, int b, int c) : x(a), y(b), d(c) {}

	grid& operator=(const grid& a)
	{
		x = a.x;
		y = a.y;
		d = a.d;
		return *this;
	}

	bool operator==(const grid& a) const
	{
		return (x == a.x && y == a.y && d == a.d);
	}
};

class nav
{
	// Navigation class with event-driven interrupts
	// DEBUG make stuff to private after
	public:
		QueueArray <task> tasklist;
		bool on_grid;
		action currentAction;
		grid currentGrid;
		grid destination;
		grid hopperEast;
		grid hopperWest;

		bool check_validity(grid new_position);
		grid directionalLineIncrement(int i);

		grid taskdestination;
		nav(grid);
		bool FLAG_unpause;

		int interrupt(isr sensor_interrupt);	
		int computeRectilinearPath(grid new_destination);
		void startTask();
		int checkTaskComplete();
		int reset(grid);
		int set_destination(grid new_destination);
		bool doneTasks();
		int countRemaining();
		action getAction();
		grid getGrid();
		grid getDestination();
};
