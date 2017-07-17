#include "../header/timer.hpp"
#include "../header/logger.hpp"

Timer::Timer(double intervalTimeInMS) : 
Timer(intervalTimeInMS, true){}

Timer::Timer(double intervalTimeInMS, bool startTimer) : INTERVAL(intervalTimeInMS), 
clock(0.0), isRunning(startTimer) {}

Timer::~Timer(){}

bool Timer::isTimeUp() const {
	return this->clock >= this->INTERVAL;
}

void Timer::update(double elaspedTime){
	if(this->isRunning){
		this->clock += elaspedTime;
	}
}

void Timer::stop(){
	if(this->isRunning)
		this->isRunning = !this->isRunning;
}

void Timer::resume(){
	if(!this->isRunning)
		this->isRunning = !this->isRunning;
} 
void Timer::start(){
	if(!this->isRunning){
		this->isRunning = !this->isRunning;
	}
}

void Timer::stopAndReset(){
	this->stop();
	this->resetClock();
}
void Timer::resetAndStart(){
	this->resetClock();
	this->start();
}

bool Timer::isClockRunning() const {
	return this->isRunning;
}

void Timer::resetClock(){
	this->clock = 0.0;
}
