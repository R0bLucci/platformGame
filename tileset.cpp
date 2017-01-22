#include "tile.h"
#include "tileset.h"
#include "camera.h"
#include "globals.h"
#include "boundingBox.h"


Tileset::Tileset(int firstgid, int tileWidth, int tileHeight, int tileCount, int columns, std::string source,
		int imageWidth, int imageHeight, Graphic & graphic) :
	firstgid(firstgid), tileWidth(tileWidth), tileHeight(tileHeight), tileCount(tileCount), columns(columns),
		image(source, imageWidth, imageHeight, graphic){}

Tileset::~Tileset(){
	/*for(int i = 0, n = this->tiles.size(); i < n; i++){
		delete this->tiles[i];
		this->tiles[i] = nullptr;
	}*/
}

int Tileset::getFirstgid() const {
	return this->firstgid;
}

int Tileset::getTileWidth() const {
	return this->tileWidth;	
}

int Tileset::getTileHeight() const {
	return this->tileHeight;
}

int Tileset::getTileCount() const {
	return this->tileCount;
}

int Tileset::getColumns() const {
	return this->columns;
}

Tileset::Image Tileset::getImage() const {
	return this->image;
}

bool Tileset::addTile(std::unique_ptr<Tile>& tile){
	if(tile->gid >= this->firstgid && tile->gid <= this->tileCount){
		tile->setSource(*this);
		this->tiles.push_back(std::move(tile));
		return true;
	}
	return false;
}

/*std::vector<std::unique_ptr<Tile>> Tileset::getTiles(){
	return this->tiles;
}*/

void Tileset::draw(Graphic &graphic, Camera & camera){
	for(int i = 0, n = this->tiles.size(); i < n; i++){
		this->tiles[i]->draw(*this, graphic, camera);
	}
}

/*std::vector<Tile*> Tileset::update(double elapsedTime, Camera * camera){
	std::vector<Tile*> tiles;
	for(int i = 0, n = this->tiles.size(); i < n; i++){
		Tile * t = this->tiles[i].get();
		if(t->isVisible(*camera)){
			if(t->gid > 1){
				t->update(elapsedTime, camera);
				tiles.push_back(t);
			}
		}
	}	
	return tiles;
}*/

// ------------------ Image ------------------------------ 

Tileset::Image::Image(std::string source, int imageWidth, int imageHeight, Graphic & graphic):
	width(imageWidth), height(imageHeight), source(source){
		this->createTexture(graphic);
}

Tileset::Image::~Image() {}


void Tileset::Image::createTexture(Graphic & graphic){
	this->texture = graphic.getTexture(this->source);
}
