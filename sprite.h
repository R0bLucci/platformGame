#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include "globals.h"
struct Graphic;
struct SDL_Texture;

class Sprite {
public:
	Sprite(Graphic &graphic, int originX, int originY, int width, int height, double posX, double posY);
	~Sprite();
	
	void draw(Graphic &graphic, const Vector2 &cameraOffset = {0.0, 0.0});	
	void update(double elapsedTime);
protected:
	SDL_Rect source;
	SDL_Texture * texture;
	double posX;
	double posY;
};

#endif
