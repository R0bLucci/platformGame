#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include <SDL2/SDL.h>
#include <map>
#include <string>
#include <vector>
#include "sprite.h"
#include "globals.h"
struct Graphic;

class AnimatedSprite : public Sprite {
public:
	AnimatedSprite(Graphic &graphic, int originX, int originY, int width, int height, float posX, float posY
		,const int timeToUpdate);

	~AnimatedSprite();
	void update(float elapsedTime);
	void draw(Graphic & graphic);

protected:
	int frameIndex;
	const int timeToUpdate;
	int elapsedTime;
	std::string currentAnimation;
	void setUpAnimation();
	void setCurrentAnimation(std::string animationName);
	
	void addAnimation(std::string animationName, int frames, Vector2 origin,  bool isHorizotal = true);
	std::map<std::string, std::vector<SDL_Rect>> animations;	
};

#endif
