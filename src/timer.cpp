#include "../header/timer.hpp"
#include "../header/logger.hpp"

Timer::Timer(double intervalTimeInMS) : 
Timer(intervalTimeInMS, true){}

Timer::Timer(double intervalTimeInMS, bool startTimer) : INTERVAL(intervalTimeInMS), 
clock(0.0), isRunning(startTimer) {}

Timer::~Timer(){}

bool Timer::isTimeUp() const {
	if(this->isPaused()) return false;

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
	this->clock = 0.0;
	if(!this->isRunning){
		this->isRunning = !this->isRunning;
	}
}

bool Timer::isPaused() const {
	return !this->isRunning;
}

/* Start Animation */
Animation::Animation(double duration) :
Animation(duration, true) {}

Animation::Animation(double duration, bool start):
ANIMATION_TIME(duration), animationCurrentTime(duration), isStarted (start){}

Animation::~Animation(){}

void Animation::update(double elapsedTime){
	if(this->isStarted && !this->isAnimationDone()){
		this->animationCurrentTime -= elapsedTime;
	}
}

bool Animation::isAnimationDone() const {
	if(!this->isStarted) return true;
	return this->animationCurrentTime < 0.0;
}

void Animation::start(){
	if(!this->isStarted) 
		this->isStarted = true;
}

void Animation::stop(){
	if(this->isStarted)
		this->isStarted = false;
}

void Animation::resetAnimationTimer(){
	if(this->animationCurrentTime < this->ANIMATION_TIME)
		this->animationCurrentTime = this->ANIMATION_TIME;
}
/* End Animation */
