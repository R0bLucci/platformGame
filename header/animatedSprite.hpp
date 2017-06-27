#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include <SDL2/SDL.h>
#include <map>
#include <string>
#include <vector>
#include "sprite.hpp"
#include "globals.hpp"
#include "vector.hpp"
struct Graphic;

class AnimatedSprite : public Sprite {
public:
	AnimatedSprite(Graphic &graphic, std::string textureName, int originX, int originY, int width, int height, 
		Vector2<double> position ,const double timeToUpdate);

	~AnimatedSprite();
	void update(double elapsedTime, const Vector2<double> & cameraOffset = {0.0, 0.0});

	void draw(Graphic & graphic, const Vector2<double> & cameraOffset = {0.0, 0.0});

protected:
	enum Direction {
		UP, RIGHT, BOTTOM, LEFT 
	};

	std::size_t frameIndex;
	const double timeToUpdate;
	double elapsedTime;
	std::string currentAnimation;
	void setUpAnimation();
	void setCurrentAnimation(std::string animationName);
	
	void addAnimation(std::string animationName, int frames, Vector2<double> origin,  bool isHorizotal = true);
	std::map<std::string, std::vector<SDL_Rect>> animations;	
private:
	void moveBoundingBox(const Vector2<double> &cameraOffset = {0.0, 0.0});
};

#endif
