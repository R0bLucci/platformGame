#include "tile.h"
#include "tileset.h"

Tileset::Tileset(int firstgid, int tileWidth, int tileHeight, int tileCount, int columns, std::string source,
		int imageWidth, int imageHeight, Graphic &graphic) :
	firstgid(firstgid), tileWidth(tileWidth), tileHeight(tileHeight), tileCount(tileCount), columns(columns),
		image(source, imageWidth, imageHeight, graphic) {}

Tileset::~Tileset(){
	for(int i = 0, n = this->tiles.size(); i < n; i++){
		delete this->tiles[i];
		this->tiles[i] = NULL;
	}
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

bool Tileset::addTile(Tile * tile){
	if(tile->gid >= this->firstgid && tile->gid <= this->tileCount){
		tile->w = this->tileWidth;
		tile->h = this->tileHeight;
		tile->imageX = ((tile->gid - 1) % this->tileWidth);
		tile->imageY = std::ceil((((double)tile->gid) / this->tileHeight) - 1);
		tile->setSource(*this);
		this->tiles.push_back(tile);
		return true;
	}
	return false;
}

std::vector<Tile*> Tileset::getTiles(){
	return this->tiles;
}

void Tileset::draw(Graphic &graphic){
	for(int i = 0, n = this->tiles.size(); i < n; i++){
		this->tiles[i]->draw(*this, graphic);
	}
}
