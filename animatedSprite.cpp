#include "animatedSprite.h"
#include <iostream>

AnimatedSprite::AnimatedSprite(Graphic &graphic, int originX, int originY, int width, int height, 
	double posX, double posY, const double timeToUpdate) : frameIndex(0), currentAnimation(""), 
Sprite(graphic, originX, originY, width, height, posX, posY), timeToUpdate(timeToUpdate), elapsedTime(0){
	this->setUpAnimation();
}

AnimatedSprite::~AnimatedSprite(){}

void AnimatedSprite::addAnimation(std::string animationName, int frames, Vector2 origin, bool isHorizontal){
	std::vector<SDL_Rect> rects;
	origin = origin * 16.0;
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

void AnimatedSprite::update(double elapsedTime){
	Sprite::update(elapsedTime);
	this->elapsedTime += elapsedTime;
	std::vector<SDL_Rect> cachedAnimations = this->animations[this->currentAnimation];
	if(this->elapsedTime >= this->timeToUpdate){
		this->elapsedTime -= this->timeToUpdate;
		if(this->frameIndex < cachedAnimations.size()){
			this->source = cachedAnimations[this->frameIndex++];
		}else{
			this->frameIndex = 0;
		}
	}
}

void AnimatedSprite::draw(Graphic &graphic){
	Sprite::draw(graphic);
}
