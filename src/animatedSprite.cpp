#include "../header/animatedSprite.hpp"
#include <iostream>
#include "../header/boundingBox.hpp"

AnimatedSprite::AnimatedSprite(Graphic &graphic, std::string textureName, int originX, int originY, int width, int height, 
	double posX, double posY, const double timeToUpdate) : 
Sprite(graphic, textureName, originX, originY, width, height, posX, posY), frameIndex(0), timeToUpdate(timeToUpdate), elapsedTime(0), currentAnimation(""){
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
	this->boundingBox->moveBoundingBox(this->posX - cameraOffset.x, 
			this->posY - cameraOffset.y);
}

void AnimatedSprite::update(double elapsedTime, const Vector2<double>& cameraOffset){
	Sprite::update(elapsedTime);
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
