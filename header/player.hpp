#ifndef PLAYER_H
#define PLAYER_H
#include "globals.hpp"
#include "animatedSprite.hpp"
#include <vector>
#include "HUD.hpp"
#include "boundingBox.hpp"

struct Graphic;
struct Tile;
struct Camera;

class Player : public AnimatedSprite {
public:
	Player(Graphic & graphic, Vector2<double> spawnPoint);
	~Player();
	
	void moveRight();
	void moveLeft();
	void jump();
	void lookUp();
	void lookDown();
	void stopLookUp();
	void stopLookDown();
	void idle();
	void stopJump();
	void update(double elapsedTime, Camera * camera);
	void draw(Graphic & graphic, Camera & cameraOffset);
	Vector2<double> getPosition();
	std::vector<Vector2<double>> surrindingArea(int unitX, int unitY);
	void handleTileCollision(std::vector<Tile*> tiles);
	void handleTileCollision(Tile* tile);
	void handleCollision(std::vector<BoundingBox*> boxes);
	void handleCollision2(std::vector<BoundingBox> boxes);
private:
	enum Direction {
		UP,
		RIGHT,
		DOWN,
		LEFT	
	};
	const double ACC;
	const double SLOW_ACC;
	const double MAX_ACC;
	const double SLOW_JUMP;
	double currentAcc;
	bool isGrounded;
	bool isLookingUp;
	bool isLookingDown;
	double dx;
	double dy;
	Direction facing;	
	HUD hud;
	BoundingBox headBox;
	BoundingBox bodyBox;
	void setUpAnimation();
	void accelerate(double elapsedTime);
};

#endif
