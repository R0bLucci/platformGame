#ifndef ARM_H
#define ARM_H

#include "sprite.hpp"
#include "vector.hpp"
#include "animatedSprite.hpp"
#include "bullet.hpp"
#include <string>
#include <map>

struct Graphic;

class Arm : public Sprite {
public:
	enum orientation {
		HORIZONTAL_RIGHT,	
		HORIZONTAL_LEFT,	
		VERTICAL_UP_RIGHT,
		VERTICAL_UP_LEFT,
		VERTICAL_DOWN_RIGHT,
		VERTICAL_DOWN_LEFT
	}; 
	Arm(Graphic & graphic, int sourceX, int sourceY, int width, int height, double reloadTime, Vector2<double> position);

	~Arm();

	virtual void update(double elapsedTime, AnimatedSprite::Direction wielderFacing, const Vector2<double> & playerPos);
	void draw(Graphic & graphic, const Vector2<double> & cameraOffset);
	virtual Bullet * fire(Graphic & graphic) = 0;
protected:
	std::map<orientation, std::pair<SDL_Rect, Vector2<double>>> sources;
	Vector2<double> offset;
	virtual void setArmOrientations() = 0;
	void updateOrientationState(const orientation & currentState);
	Bullet::orientation bulletOrientationState;

	void reload();
	void reloading(double elapsedTime);
	bool isReadyToFire() const;
	
	const double TIME_TO_RELOAD;
	double timeToFire;
	
};

#endif
