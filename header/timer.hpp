#ifndef TIMER_H
#define TIMER_H

class Timer {
public:
	Timer(double intervalTimeInMS); // Create a new timer that starts as default
	Timer(double intervalTimeInMS, bool startTimer); // Create a new timer with option to no start from the start
	~Timer();

	bool isTimeUp() const; // Check if the clock interval is depleted 
	void update(double elapsedTime); // run the clock
	void stop(); // pause the clock to where is at
	void resetAndStart(); // resets the clock and starts the timer
	void start(); // starts the timer
	void stopAndReset(); // pauses clock and reset the clock back to zero
	void resume(); // resumes the clock on where it was last stopped
	bool isClockRunning() const; // check if the clock is paused/stopped
	void resetClock(); // reset clock 
private:
	const double INTERVAL;
	double clock;
	bool isRunning;
};
#endif
