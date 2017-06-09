#ifndef TILE_H
#define TILE_H

#include <SDL2/SDL.h>
#include "globals.hpp"
#include "vector.hpp"

class Tileset;
class Graphic;
class Camera;
class BoundingBox;

class Tile {
public:
	Tile(int gid, int layerX, int layerY, int width, int height); 
	Tile(int gid, int x, int y); 
	~Tile(); 
	int gid;
	int layerX; // X position of the Tile relative to the cvs map
	int layerY; // Y position of the Tile relative to the cvs map
	int w; // width
	int h; // height
	SDL_Rect source;
	SDL_Rect dest;
	int imageX; // X position of the tile's source in the tileset image 
	int imageY; // Y position of the tile's source in the tileset image
	
	BoundingBox * getBoundingBox();
	Vector2<double> getOrigin();
	void setBoundingBox(BoundingBox * b);
	void draw(Tileset &tileset, Graphic &graphic, Camera &camera);
	void update(double elapsedTime, Camera * camera);
	void setSource(Tileset &tileset); // set the tileset in which the current tile is part of	
	bool isVisible(Camera & camera);
private:
	BoundingBox * box;
	BoundingBox * originalBox;
	int scalerX; // Store the scale ratio of which the tile will be scaled to 
	int scalerY; // Store the scale ratio of which the tile will be scaled to
	
};

#endif
