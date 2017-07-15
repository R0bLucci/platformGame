#ifndef TIMER_H
#define TIMER_H

class Animation {
public:
	Animation(double duration);
	Animation(double duration, bool start);
	~Animation();
	void update(double elapsedTime);
	void start();
	void stop();
	void resetAnimationTimer();
	bool isAnimationDone() const;
private:
	const double ANIMATION_TIME;
	double animationCurrentTime;
	bool isStarted;
};

class Timer {
public:
	Timer(double intervalTimeInMS); // Create a new timer that starts as default
	Timer(double intervalTimeInMS, bool startTimer); // Create a new timer with option to no start from the start
	Timer(double intervalTimeInMS, bool inverse, bool startTimer);
	~Timer();

	bool isTimeUp() const; // Check if the clock interval is depleted 
	void update(double elapsedTime); // run the clock
	void stop(); // pause the clock to where is at
	void start(); // resets the clock and starts the timer
	void stopAndReset(); // pauses clock and reset the clock back to zero
	void resume(); // resumes the clock on where it was last stopped
	bool isPaused() const; // pauses the clock
private:
	const double INTERVAL;
	double clock;
	bool isInverse;
	bool isRunning;
};
#endif
