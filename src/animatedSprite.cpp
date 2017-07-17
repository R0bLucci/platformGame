#include "../header/animatedSprite.hpp"
#include <iostream>
#include "../header/boundingBox.hpp"
#include "../header/logger.hpp"

AnimatedSprite::AnimatedSprite(Graphic &graphic, std::string textureName, int originX, int originY, int width, int height, double health, Vector2<double> position, Direction facing, const double timeToUpdate) : 
Sprite(graphic, textureName, originX, originY, width, height, position), health(health),
facing(facing), frameIndex(0), timeToUpdate(timeToUpdate), elapsedTime(0), currentAnimation(""), 
damageText(new DamageText(graphic, position)){
	this->setUpAnimation();
}

AnimatedSprite::~AnimatedSprite(){}

void AnimatedSprite::addAnimation(std::string animationName, int frames, Vector2<double> origin, bool isHorizontal){
	std::vector<SDL_Rect> rects;
	origin *= 16.0;
	// Get next rectangles left to right 
	if(isHorizontal){
		for(int i = 0; i < frames; i++){
			SDL_Rect rect = { (i * this->source.w) + (int) origin.x, 0 + (int) origin.y, this->source.w, this->source.h };
			rects.push_back(rect);
		}
	}else{ // Get next rectangles top to bottom
		for(int i = 0; i < frames - 1; i++){
			SDL_Rect rect = { 0 + (int) origin.x, (i * this->source.h) +(int) origin.y, this->source.w, this->source.h };
			rects.push_back(rect);
		}
	}
	this->animations.insert(std::pair<std::string, std::vector<SDL_Rect>>(animationName, rects));
}
void AnimatedSprite::setCurrentAnimation(std::string animationName){
	this->currentAnimation = animationName;
}

void AnimatedSprite::setUpAnimation(){}

void AnimatedSprite::moveBoundingBox(const Vector2<double> &cameraOffset){
	Vector2<double> pos = this->position - cameraOffset;
	this->boundingBox->moveBoundingBox(pos); 
}

void AnimatedSprite::update(double elapsedTime, const Vector2<double>& cameraOffset){
	Sprite::update(elapsedTime);
	//damageText->update(elapsedTime);
	damageText->setPos(this->getCenteredPosition());
	this->moveBoundingBox(cameraOffset);

	this->elapsedTime += elapsedTime;
	std::vector<SDL_Rect> cachedAnimations = this->animations[this->currentAnimation];
	if(this->elapsedTime >= this->timeToUpdate){
		this->elapsedTime -= this->timeToUpdate;
		if(this->frameIndex < cachedAnimations.size()){
			this->source = cachedAnimations[this->frameIndex++];
		}else{
			this->frameIndex = 0;
			this->source = cachedAnimations[this->frameIndex++];
		}
	}
}

void AnimatedSprite::draw(Graphic &graphic, const Vector2<double> &cameraOffset){
	Sprite::draw(graphic, cameraOffset);
}

void AnimatedSprite::decreaseHealth(const double damage){
	damageText->accumulateDamage(damage);
}

void AnimatedSprite::encreaseHealth(const double lives){}

Vector2<double> AnimatedSprite::getPosition() const {
	return this->position;
}

Vector2<double> AnimatedSprite::getCenteredPosition() const {
	return Vector2<double>(this->position.x + (this->source.w * globals::SPRITE_SCALER / 2), 
			this->position.y + (this->source.h * globals::SPRITE_SCALER / 2));
}

const std::shared_ptr<DamageText> AnimatedSprite::getDamageText() const {
	return this->damageText;
}
