#include "../header/arm.hpp"
#include "../header/graphic.hpp"
#include "../header/camera.hpp"

Arm::Arm(Graphic & graphic, int sourceX, int sourceY, int width, int height, Vector2<double> position)
: Sprite(graphic, "Arms.png", sourceX, sourceY, width, height, position) {}

Arm::~Arm(){}

void Arm::update(double elapsedTime, AnimatedSprite::Direction wielderFacing){
	std::pair<SDL_Rect, Vector2<double>> pair; 
	switch(wielderFacing){
		case AnimatedSprite::Direction::RIGHT:
			pair = this->sources[HORIZONTAL_RIGHT];
		break;
		case AnimatedSprite::Direction::LEFT:
			pair = this->sources[HORIZONTAL_LEFT];
		break;
		case AnimatedSprite::Direction::UP_RIGHT:
			pair = this->sources[VERTICAL_UP_RIGHT];
		break;
		case AnimatedSprite::Direction::BOTTOM_RIGHT:
			pair = this->sources[VERTICAL_DOWN_RIGHT];
		break;
		case AnimatedSprite::Direction::UP_LEFT:
			pair = this->sources[VERTICAL_UP_LEFT];
		break;
		case AnimatedSprite::Direction::BOTTOM_LEFT:
			pair = this->sources[VERTICAL_DOWN_LEFT];
		break;
	}
	this->source = pair.first;
	this->offset = pair.second;
}


void Arm::draw(Graphic & graphic,const Vector2<double> & cameraOffset, const Vector2<double> & playerPos){
	this->position = playerPos + this->offset;
	Sprite::draw(graphic, cameraOffset);
}

SDL_Rect Arm::armRect(int x, int y, int w, int h) const {
	SDL_Rect rect;
	rect.x = x; rect.y = y; rect.w = w; rect.h = h;
	return rect;
}
