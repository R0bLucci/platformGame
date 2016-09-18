#ifndef PLAYER_H
#define PLAYER_H
#include "globals.h"
#include "animatedSprite.h"
#include <vector>

struct BoundingBox;
struct Graphic;
struct Tile;

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
	void update(double elapsedTime);
	void draw(Graphic & graphic);
	void stopMoving();
	std::vector<Vector2> surrindingArea(int unitX, int unitY);
	void handleTileCollision(std::vector<Tile*> tiles);
	void handleTileCollision(Tile* tile);
	void handleCollision(std::vector<BoundingBox*> boxes);
	BoundingBox * boundingBox;
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
	double dx;
	double dy;
	Direction facing;	
	void setUpAnimation();
};

#endif
