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
	AnimatedSprite(Graphic &graphic, int originX, int originY, int width, int height, double posX, double posY
		,const double timeToUpdate);

	~AnimatedSprite();
	void update(double elapsedTime, const Vector2 & cameraOffset = {0.0, 0.0});
	void draw(Graphic & graphic, const Vector2 & cameraOffset = {0.0, 0.0});

protected:
	int frameIndex;
	const double timeToUpdate;
	double elapsedTime;
	std::string currentAnimation;
	void setUpAnimation();
	void setCurrentAnimation(std::string animationName);
	
	void addAnimation(std::string animationName, int frames, Vector2 origin,  bool isHorizotal = true);
	std::map<std::string, std::vector<SDL_Rect>> animations;	
private:
	void moveBoundingBox(const Vector2 &cameraOffset = {0.0, 0.0});
};

#endif
