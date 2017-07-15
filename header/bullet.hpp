#ifndef BULLET_H
#define BULLET_H

#include "sprite.hpp"
#include "vector.hpp"
#include <vector>

struct Graphic;
struct Camera;
struct Level;
struct Enemy;
struct BoundingBox;

class Bullet : public Sprite {
public:
	enum orientation {
		HORIZONTAL_RIGHT, HORIZONTAL_LEFT, VERTICAL_UP, VERTICAL_DOWN
	};

	Bullet(Graphic & graphic, int sourceX, int sourceY, int width, int height, 
		double firePower, orientation orientation, double timeToLive, Vector2<double> position);

	virtual ~Bullet();
	
	virtual void update(double elapsedTimea, Level & levelEnvironment, std::vector<Bullet*>::iterator & bullet);
	void draw(Graphic & graphic, Camera & camera);
	virtual void move(const double & elpsedTime) = 0;
protected:
	
	virtual void setBulletOrientations() = 0;
	bool hasBulletCollided(Level & level, std::vector<Bullet*>::iterator & bullet);
	bool handleWallCollision(std::vector<BoundingBox*> & collidables);
	bool hasBulletHitEnemy(std::vector<Enemy*> & enemies);
	void eraseBullet(std::vector<Bullet*> & firedBullets, std::vector<Bullet*>::iterator & bullet);
	orientation bulletOrientation;
	
	const double TIME_TO_LIVE;
	double lifeTime;

	double firePower;
	Vector2<double> offset;	
	
	bool isTimeToDie() const;
	void updateLifeTime(double elapsedTime);
};
#endif 
