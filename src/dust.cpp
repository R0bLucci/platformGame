#include "../header/dust.hpp"
#include "../header/graphic.hpp"
#include "../header/logger.hpp"
#include "../header/globals.hpp"

Dust::Dust(Graphic & graphic, const Vector2<double> position) :
texture(graphic.getTexture("NpcSym.png", false)), 
timer(100), position(position), w(WIDTH), 
h(HEIGHT), stage((int) FIRST){
	this->setSource();
}

Dust::~Dust(){logger::log("~Dissipated(()");}

void Dust::update(double elapsedTime){
	if(((stages) this->stage) != SEVENTH){
		this->timer.update(elapsedTime);	
		if(this->timer.isTimeUp()){
			++this->stage;
			this->setSource();
			this->timer.resetAndStart();
		} 	
	}else{
		this->timer.stop();
	}
}

void Dust::draw(Graphic & graphic, const Vector2<double> cameraOffset){
	if(this->timer.isClockRunning()){
		SDL_Rect dest = { (int) (this->position.x - cameraOffset.x),
				(int) (this->position.y - cameraOffset.y),
				(int) this->w * globals::SPRITE_SCALER,
				(int) this->h * globals::SPRITE_SCALER };
		graphic.blitSurface(this->texture, &this->source, &dest);
	}
}

void Dust::setPos(const Vector2<double> pos){
	this->position = pos;
}

void Dust::setSource(){
	this->source = {(int) (this->stage * X), (int) Y, (int) this->w, (int) this->h};
}

bool Dust::isDissipated() const {
	return !this->timer.isClockRunning();
}
