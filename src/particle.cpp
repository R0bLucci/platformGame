#include "../header/particle.hpp"
#include "../header/graphic.hpp"
#include "../header/globals.hpp"
#include "../header/logger.hpp"

Particle::Particle(Graphic & graphic, std::string textureName, 
const int sourceX, const int sourceY, const int width, const int height, double animationInMS, 
int initialFrame, const int frames, const Vector2<double> & position, bool startAnimation) :
texture(graphic.getTexture(textureName, false)), timer(animationInMS, startAnimation), 
X(sourceX), Y(sourceY), W(width), H(height), 
currentFrame(initialFrame), START_FRAME(initialFrame), FRAMES(frames),
position(position) {
	this->setSource();
}

Particle::~Particle(){logger::log("~Particle()");}

void Particle::update(double elapsedTime){
	if(this->currentFrame < (this->START_FRAME + this->FRAMES)){
		this->timer.update(elapsedTime);	
		if(this->timer.isTimeUp()){
			++this->currentFrame;
			this->setSource();
			this->timer.resetAndStart();
		} 	
	}else{
		this->timer.stop();
	}
}

void Particle::draw(Graphic & graphic, const Vector2<double> & cameraOffset){
	if(this->timer.isClockRunning() && this->currentFrame < (this->START_FRAME + this->FRAMES)){
		SDL_Rect dest = {
			(int) (this->position.x - cameraOffset.x),
			(int) (this->position.y - cameraOffset.y),
			this->W * globals::SPRITE_SCALER,
			this->H * globals::SPRITE_SCALER };

		graphic.blitSurface(this->texture, &this->source, &dest);
	}
}

bool Particle::isDone() const {
	return !this->timer.isClockRunning();
}

void Particle::setPos(const Vector2<double> & pos){
	this->position = pos;
}

void Particle::resetCurrentFrame(){
	this->timer.resetAndStart();
	this->currentFrame = this->START_FRAME;
	this->setSource();
}

void Particle::setSource(){
	this->source = {
		this->currentFrame * this->W, 
		this->Y, 
		this->W, 
		this->H };
}

void Particle::stopAnimation() {
	this->timer.stop();
}

void Particle::startAnimation() {
	this->timer.start();
}

Vector2<double> Particle::getCenteredPosition() const {
	return Vector2<double>(this->position.x - (this->source.w * globals::SPRITE_SCALER / 2.0), 
				this->position.y - (this->source.h * globals::SPRITE_SCALER / 2.0));
}
