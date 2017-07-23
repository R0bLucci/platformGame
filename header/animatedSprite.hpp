#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include <SDL2/SDL.h>
#include <map>
#include <string>
#include <vector>
#include <memory>
#include "sprite.hpp"
#include "globals.hpp"
#include "vector.hpp"
#include "text.hpp"
#include "deathCloud.hpp"

struct Graphic;

class AnimatedSprite : public Sprite {
public:
	enum Direction {
		UP_RIGHT, UP_LEFT, RIGHT, BOTTOM_RIGHT, BOTTOM_LEFT, LEFT 
	};

	AnimatedSprite(Graphic &graphic, std::string textureName, int originX, int originY, int width, int height,
		double health, Vector2<double> position , Direction facing, const double timeToUpdate);

	~AnimatedSprite();
	void update(double elapsedTime, const Vector2<double> & cameraOffset = {0.0, 0.0});

	void draw(Graphic & graphic, const Vector2<double> & cameraOffset = {0.0, 0.0});
	
	const std::shared_ptr<DamageText> getDamageText() const;

	bool isDead() const;

protected:

	double health;
	Direction facing;
	std::size_t frameIndex;
	const double timeToUpdate;
	double elapsedTime;
	std::string currentAnimation;
	std::map<std::string, std::vector<SDL_Rect>> animations;	
	std::shared_ptr<DamageText> damageText;
	std::unique_ptr<Particle> deathCloud;


	void setUpAnimation();
	void setCurrentAnimation(std::string animationName);

	void decreaseHealth(const double damage);
	void encreaseHealth(const double lives);
	void addAnimation(std::string animationName, int frames, Vector2<double> origin,  bool isHorizotal = true);

	std::unique_ptr<Particle> getDeathCloud();
private:
	void moveBoundingBox(const Vector2<double> &cameraOffset = {0.0, 0.0});
};

#endif
