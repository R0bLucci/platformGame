#include <SDL2/SDL.h> 
#include "../header/graphic.hpp"
#include "../header/tileset.hpp"
#include "../header/tile.hpp"
#include "../header/boundingBox.hpp"
#include "../header/camera.hpp"
#include "../header/logger.hpp"

Tile::Tile(int gid, int layerX, int layerY, int width, int height, bool isBackground):
	gid(gid), position(layerX * width * globals::SPRITE_SCALER, layerY * height * globals::SPRITE_SCALER), w(width * globals::SPRITE_SCALER), h(height * globals::SPRITE_SCALER), box(nullptr), isBackground(isBackground){
	/*this->scalerX = this->w * globals::SPRITE_SCALER; 	
	this->scalerY = this->h * globals::SPRITE_SCALER; */
}

Tile::Tile(int gid, int layerX, int layerY, bool isBackground) :
	gid(gid), position(layerX, layerY), box(nullptr), isBackground(isBackground){}

Tile::~Tile() { 
	//logger::log("~Tile()");
	if(this->box){
		delete this->box;
		this->box = nullptr;
	}
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
	this->position.x *= this->w;
	this->position.y *= this->h;
	this->imageX = ((this->gid -1) % tileset.getTileWidth());
	this->imageY = std::ceil((((double) this->gid) / tileset.getTileHeight()) - 1 );

	this->source = { this->imageX * tileset.getColumns(), this->imageY * tileset.getColumns(),
			tileset.getTileWidth(), tileset.getTileHeight()};
	this->dest = { this->position.x, 
			this->position.y, 
			this->w , 
			this->h };
	//Create bounding box if the tile rappresent a forground tile and the box is not created yet
	if(!this->isBackground && !this->box ){
		this->box = new BoundingBox(*this);
	}
}

void Tile::draw(Tileset & tileset, Graphic &graphic, Camera & camera){
	if(this->isVisible(camera)){
		this->dest = { (int)(this->position.x - camera.getPosition().x), 
		 		(int)(this->position.y - camera.getPosition().y), 
				this->w , 
				this->h };
		graphic.blitSurface(tileset.getImage().getTexture(), &this->source, &this->dest);
		graphic.blitBoundingBox("box.png", NULL, { this->position.x, this->position.y, this->w, this->h});
	}
}	

void Tile::update(double elapsedTime, Camera * camera) {
	//this->box->setOrigin(Vector2<double>((int)((this->position.x * this->w) - camera->getPosition().x),
					//(int)((this->position.y * this->h) - camera->getPosition().y)));
}

bool Tile::isVisible(const Camera &camera) const {
	
	if(!this->box){
		return false;
	}

	int cameraLeft, tileLeft;
	int cameraRight, tileRight;
	int cameraTop, tileTop;
	int cameraBottom, tileBottom;

	cameraLeft = camera.getLeftSide();
	cameraRight = camera.getRightSide();
	cameraTop = camera.getTopSide();
	cameraBottom = camera.getBottomSide();
	tileLeft = this->position.x;
	tileRight = this->position.x + this->w;	
	tileTop = this->position.y;
	tileBottom = this->position.y + this->h;
	
	if(cameraBottom <= tileTop ||
		cameraTop >= tileBottom ||
		cameraRight <= tileLeft ||
		cameraLeft >= tileRight){
		return false;
	}
	
	return true;	
}

Vector2<int> Tile::getOrigin(){
	return this->position;
}

