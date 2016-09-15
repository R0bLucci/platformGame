#include "sprite.h"
#include "graphic.h"
#include "globals.h"


Sprite::Sprite(Graphic &graphic, int originX, int originY, int width, int height, float posX, float posY) : 
posX(posX), posY(posY) {
	SDL_Surface * surface = graphic.getSurface("MyChar.png", false);
	if(surface == nullptr){
		return;
	}

	this->texture = SDL_CreateTextureFromSurface(graphic.getRenderer(), surface);
	if(this->texture == nullptr){
		return;
	}

	this->source = { originX, originY, width, height};
	SDL_FreeSurface(surface);
}

Sprite::~Sprite(){}
	
void Sprite::draw(Graphic &graphic){
	SDL_Rect destination = {this->posX, this->posY, 
		this->source.w * globals::SPRITE_SCALER, this->source.h * globals::SPRITE_SCALER};
	graphic.blitSurface(this->texture, &this->source, &destination);
}

void Sprite::update(float elapsedTime){}

