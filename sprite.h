#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
struct Graphic;
struct SDL_Texture;

class Sprite {
public:
	Sprite(Graphic &graphic, int originX, int originY, int width, int height, float posX, float posY);
	~Sprite();
	
	void draw(Graphic &graphic);	
	void update(float elapsedTime);
protected:
	SDL_Rect source;
	SDL_Texture * texture;
	int posX;
	int posY;
};

#endif
