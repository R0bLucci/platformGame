#ifndef TILE_H
#define TILE_H

#include <SDL2/SDL.h>

class Tileset;
class Graphic;

class Tile {
public:
	Tile(int gid, int layerX, int layerY, int width, int height); 
	Tile(int gid, int x, int y); 
	~Tile(); 
	int layerX;
	int layerY;
	int imageX;
	int imageY;
	int w;
	int h;
	int gid;
	SDL_Rect source;

	void draw(Tileset &tileset, Graphic &graphic);
	void setSource(Tileset &tileset);	
private:
	
};

#endif
