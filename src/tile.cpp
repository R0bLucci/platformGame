#include <SDL2/SDL.h> 
#include "../header/graphic.hpp"
#include "../header/tileset.hpp"
#include "../header/tile.hpp"
#include "../header/boundingBox.hpp"
#include "../header/camera.hpp"
#include "../header/logger.hpp"

Tile::Tile(int gid, int layerX, int layerY, int width, int height, bool isBackground):
	gid(gid), x(layerX * width * globals::SPRITE_SCALER), y(layerY * height * globals::SPRITE_SCALER), w(width * globals::SPRITE_SCALER), h(height * globals::SPRITE_SCALER), box(nullptr), isBackground(isBackground){
	/*this->scalerX = this->w * globals::SPRITE_SCALER; 	
	this->scalerY = this->h * globals::SPRITE_SCALER; */
}

Tile::Tile(int gid, int layerX, int layerY, bool isBackground) :
	gid(gid), x(layerX), y(layerY), box(nullptr), isBackground(isBackground){}

Tile::~Tile() { 
	logger::log("~Tile()");
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
	this->x *= this->w;
	this->y *= this->h;
	this->imageX = ((this->gid -1) % tileset.getTileWidth());
	this->imageY = std::ceil((((double) this->gid) / tileset.getTileHeight()) - 1 );

	this->source = { this->imageX * tileset.getColumns(), this->imageY * tileset.getColumns(),
			tileset.getTileWidth(), tileset.getTileHeight()};
	this->dest = { this->x, 
			this->y, 
			this->w , 
			this->h };
	//Create bounding box if the tile rappresent a forground tile and the box is not created yet
	if(!this->isBackground && !this->box ){
		this->box = new BoundingBox(*this);
	}
}

void Tile::draw(Tileset & tileset, Graphic &graphic, Camera & camera){
	if(this->isVisible(camera)){
		this->dest = { (int)(this->x - camera.getPosition().x), 
		 		(int)(this->y - camera.getPosition().y), 
				this->w , 
				this->h };
		graphic.blitSurface(tileset.getImage().getTexture(), &this->source, &this->dest);
		graphic.blitBoundingBox("box.png", NULL, { this->x, this->y, this->w, this->h});
	}
}	

void Tile::update(double elapsedTime, Camera * camera) {
	//this->box->setOrigin(Vector2<double>((int)((this->x * this->w) - camera->getPosition().x),
					//(int)((this->y * this->h) - camera->getPosition().y)));
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
	tileLeft = this->x;
	tileRight = this->x + this->w;	
	tileTop = this->y;
	tileBottom = this->y + this->h;
	
	if(cameraBottom <= tileTop ||
		cameraTop >= tileBottom ||
		cameraRight <= tileLeft ||
		cameraLeft >= tileRight){
		return false;
	}
	
	return true;	
}

Vector2<double> Tile::getOrigin(){
	return Vector2<double>(this->x,
			this->y);	
}

