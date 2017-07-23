#include "../header/arm.hpp"
#include "../header/camera.hpp"
#include "../header/graphic.hpp"
#include "../header/boundingBox.hpp"
#include "../header/globals.hpp"

Arm::Arm(Graphic & graphic, int sourceX, int sourceY, int width, int height, double reloadTime, Vector2<double> position)
: Sprite(graphic, "Arms.png", sourceX, sourceY, width, height, position), 
bulletOrientationState(Bullet::orientation::HORIZONTAL_LEFT), TIME_TO_RELOAD(reloadTime),
timeToFire(0.0), starFire(graphic, position, false) {}

Arm::~Arm(){}

void Arm::update(double elapsedTime, AnimatedSprite::Direction wielderFacing, const Vector2<double> & playerPos){
	std::pair<SDL_Rect, Vector2<double>> pair; 
	orientation armOrientationState;
	switch(wielderFacing){
		case AnimatedSprite::Direction::RIGHT:
			armOrientationState = HORIZONTAL_RIGHT;
			pair = this->sources[HORIZONTAL_RIGHT];
		break;
		case AnimatedSprite::Direction::LEFT:
			armOrientationState = HORIZONTAL_LEFT;
			pair = this->sources[HORIZONTAL_LEFT];
		break;
		case AnimatedSprite::Direction::UP_RIGHT:
			armOrientationState = VERTICAL_UP_RIGHT;
			pair = this->sources[VERTICAL_UP_RIGHT];
		break;
		case AnimatedSprite::Direction::BOTTOM_RIGHT:
			armOrientationState = VERTICAL_DOWN_RIGHT;
			pair = this->sources[VERTICAL_DOWN_RIGHT];
		break;
		case AnimatedSprite::Direction::UP_LEFT:
			armOrientationState = VERTICAL_UP_LEFT;
			pair = this->sources[VERTICAL_UP_LEFT];
		break;
		case AnimatedSprite::Direction::BOTTOM_LEFT:
			armOrientationState = VERTICAL_DOWN_LEFT;
			pair = this->sources[VERTICAL_DOWN_LEFT];
		break;
	}
	this->source = pair.first;
	this->offset = pair.second;
	this->updateOrientationState(armOrientationState);
	this->position = playerPos + this->offset;
	
	// Update bounding box position, width and height
	this->boundingBox->w = pair.first.w * globals::SPRITE_SCALER; 
	this->boundingBox->h = pair.first.h * globals::SPRITE_SCALER; 
	this->boundingBox->moveBoundingBox(this->position);

	this->reloading(elapsedTime);
	this->starFire.setPos(this->getArmCenteredPos(armOrientationState));
	this->starFire.update(elapsedTime);
}


void Arm::draw(Graphic & graphic,const Vector2<double> & cameraOffset){
	Sprite::draw(graphic, cameraOffset);
	graphic.blitBoundingBox("tile.png", NULL, {
				this->boundingBox->position.x, 
				this->boundingBox->position.y, 
				this->boundingBox->w, 
				this->boundingBox->h 
			});
	starFire.draw(graphic, cameraOffset);
}

void Arm::updateOrientationState(const orientation & currentState){
	switch(currentState){
		case HORIZONTAL_RIGHT:
			this->bulletOrientationState = Bullet::orientation::HORIZONTAL_RIGHT;
		break;
		case HORIZONTAL_LEFT:
			this->bulletOrientationState = Bullet::orientation::HORIZONTAL_LEFT;
		break;
		case VERTICAL_UP_RIGHT:
		case VERTICAL_UP_LEFT:
			this->bulletOrientationState = Bullet::orientation::VERTICAL_UP;
		break;
		case VERTICAL_DOWN_RIGHT:
		case VERTICAL_DOWN_LEFT:
			this->bulletOrientationState = Bullet::orientation::VERTICAL_DOWN;
		break;
	}
}

void Arm::reload(){
	this->timeToFire = this->TIME_TO_RELOAD;
}

void Arm::reloading(double elapsedTime){
	if(!this->isReadyToFire()){
		this->timeToFire -= elapsedTime;
	}
}

bool Arm::isReadyToFire() const {
	return this->timeToFire <= 0.0;
}

Vector2<double> Arm::getArmCenteredPos(Arm::orientation orientation) const {
	double x,y;
	switch(orientation){
		case orientation::HORIZONTAL_RIGHT:
			x = this->position.x + this->source.w * globals::SPRITE_SCALER;
			y = this->position.y + ((this->source.h * globals::SPRITE_SCALER) / 2);
		break;
		case orientation::HORIZONTAL_LEFT:
			x = this->position.x;
			y = this->position.y + ((this->source.h * globals::SPRITE_SCALER) / 2);
		break;
		case orientation::VERTICAL_UP_RIGHT:
		case orientation::VERTICAL_UP_LEFT:
			x = this->position.x + ((this->source.w * globals::SPRITE_SCALER) / 2);
			y = this->position.y;
		break;
		case orientation::VERTICAL_DOWN_RIGHT:
		case orientation::VERTICAL_DOWN_LEFT:
			x = this->position.x + ((this->source.w * globals::SPRITE_SCALER) / 2);
			y = this->position.y + this->source.h * globals::SPRITE_SCALER;
		break;
	}
	return Vector2<double>(x, y);	
}
