#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include "globals.hpp"
#include <string>
#include "vector.hpp" 

struct Graphic;
struct SDL_Texture;
struct BoundingBox;

class Sprite {
public:
	Sprite(Graphic &graphic, std::string textureName, int originX, int originY, int width, int height, double posX, double posY);
	~Sprite();
	
	void draw(Graphic &graphic, const Vector2<double> &cameraOffset = {0.0, 0.0});	
	void update(double elapsedTime);
	bool isColliding(BoundingBox * box);
protected:
	double posX;
	double posY;
	SDL_Rect source;
	SDL_Texture * texture;
	BoundingBox * boundingBox;
};

#endif
