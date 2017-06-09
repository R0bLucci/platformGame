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
	int layerX;
	int layerY;
	int w;
	int h;
	SDL_Rect source;
	SDL_Rect dest;
	int imageX;
	int imageY;
	
	BoundingBox * getBoundingBox();
	Vector2<double> getOrigin();
	void setBoundingBox(BoundingBox * b);
	void draw(Tileset &tileset, Graphic &graphic, Camera &camera);
	void update(double elapsedTime, Camera * camera);
	void setSource(Tileset &tileset);	
	bool isVisible(Camera & camera);
private:
	BoundingBox * box;
	BoundingBox * originalBox;
	int scalerX;
	int scalerY;
	
};

#endif
