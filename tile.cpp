#include <SDL2/SDL.h> 
#include "globals.h"
#include "graphic.h"
#include "tileset.h"
#include "tile.h"
#include "boundingBox.h"

Tile::Tile(int gid, int layerX, int layerY, int width, int height):
	gid(gid), layerX(layerX), layerY(layerY), w(width), h(height), box(nullptr){
	this->scalerX = this->w * globals::SPRITE_SCALER; 	
	this->scalerY = this->h * globals::SPRITE_SCALER; 	
}

Tile::Tile(int gid, int layerX, int layerY):
	gid(gid), layerX(layerX), layerY(layerY), box(nullptr){}

Tile::~Tile() { 
	delete this->box;
}

void Tile::setBoundingBox(BoundingBox * b){
	this->box = b;
}

BoundingBox * Tile::getBoundingBox(){
	return this->box;
}

void Tile::setSource(Tileset &tileset){
	this->source = { this->imageX * tileset.getColumns(), this->imageY * tileset.getColumns(),
			this->w, this->h};
}

void Tile::draw(Tileset & tileset, Graphic &graphic){
	SDL_Rect dest = { this->layerX * (globals::SPRITE_SCALER * this->w), this->layerY * (globals::SPRITE_SCALER * this->h), this->w * globals::SPRITE_SCALER, this->h * globals::SPRITE_SCALER };
	graphic.blitSurface(tileset.getImage().getTexture(), &this->source, &dest);

}	
