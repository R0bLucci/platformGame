#include <SDL2/SDL.h> 
#include "graphic.h"
#include "tileset.h"
#include "tile.h"
#include "boundingBox.h"
#include "camera.h"

Tile::Tile(int gid, int layerX, int layerY, int width, int height):
	gid(gid), layerX(layerX), layerY(layerY), w(width), h(height), box(nullptr){
	this->scalerX = this->w * globals::SPRITE_SCALER; 	
	this->scalerY = this->h * globals::SPRITE_SCALER; 	
}

Tile::Tile(int gid, int layerX, int layerY):
	gid(gid), layerX(layerX), layerY(layerY), box(nullptr){}

Tile::~Tile() { 
	delete this->box;
	delete this->originalBox;
	this->box = NULL;
	this->originalBox = NULL;
}

void Tile::setBoundingBox(BoundingBox * b){
	this->box = b;
}

BoundingBox * Tile::getBoundingBox(){
	return this->box;
}

void Tile::setSource(Tileset &tileset){
	this->w = tileset.getTileWidth() * globals::SPRITE_SCALER;
	this->h = tileset.getTileHeight() * globals::SPRITE_SCALER;  
	this->imageX = ((this->gid -1) % tileset.getTileWidth());
	this->imageY = std::ceil((((double) this->gid) / tileset.getTileHeight()) - 1 );

	this->source = { this->imageX * tileset.getColumns(), this->imageY * tileset.getColumns(),
			tileset.getTileWidth(), tileset.getTileHeight()};
	this->dest = { this->layerX * this->w, 
			this->layerY * this->h, 
			this->w , 
			this->h };
	if(!this->box){
		this->box = new BoundingBox(*this);
		this->originalBox = new BoundingBox(*this->box);
	}
}

void Tile::draw(Tileset & tileset, Graphic &graphic, Camera & camera){
	if(this->isVisible(camera)){
		this->dest = { (int)((this->layerX * this->w) - camera.getPosition().x), 
		 		(int)((this->layerY * this->h) - camera.getPosition().y), 
				this->w , 
				this->h };
		graphic.blitSurface(tileset.getImage().getTexture(), &this->source, &this->dest);
	}

}	

void Tile::update(double elapsedTime, Camera * camera) {
	this->box->setOrigin(Vector2((int)((this->layerX * this->w) - camera->getPosition().x),
					(int)((this->layerY * this->h) - camera->getPosition().y)));
}

bool Tile::isVisible(Camera &camera){
	
	if(!this->box){
		return false;
	}

	int cameraLeft, boxLeft;
	int cameraRight, boxRight;
	int cameraTop, boxTop;
	int cameraBottom, boxBottom;

	cameraLeft = camera.getPosition().x;
	cameraRight = camera.getPosition().x + camera.getWidth();
	cameraTop = camera.getPosition().y;
	cameraBottom = camera.getPosition().y + camera.getHeight();
	boxLeft = this->originalBox->getLeftSide();
	boxRight = this->originalBox->getRightSide();	
	boxTop = this->originalBox->getTopSide();
	boxBottom = this->originalBox->getBottomSide();
	
	if(cameraBottom <= boxTop ||
		cameraTop >= boxBottom ||
		cameraRight <= boxLeft ||
		cameraLeft >= boxRight){
		return false;
	}
	
	return true;	
}

Vector2 Tile::getOrigin(){
	return Vector2(this->layerX * (globals::SPRITE_SCALER * this->w),
			this->layerY * (globals::SPRITE_SCALER * this->h));	
}

