#ifndef PLAYER_H
#define PLAYER_H
#include "globals.h"
#include "animatedSprite.h"
struct Graphic;

class Player : public AnimatedSprite {
public:
	Player(Graphic & graphic, Vector2 spawnPoint);
	~Player();
	
	void moveRight();
	void moveLeft();
	void jump();
	void lookUp();
	void lookDown();
	void stopLookUp();
	void stopLookDown();
	void idle();
	void update(float elapsedTime);
	void draw(Graphic & graphic);
	void stopMoving();
private:
	enum Direction {
		UP,
		RIGHT,
		DOWN,
		LEFT	
	};
	bool isGrounded;
	bool isLookingUp;
	bool isLookingDown;
	float dx;
	float dy;
	Direction facing;	
	void setUpAnimation();
};

#endif
