#ifndef ENEMY_H
#define ENEMY_H
#include "animatedSprite.hpp"
#include "boundingBox.hpp"
#include "timer.hpp"

struct Graphic;
struct Camera;
struct BoundingBox; 
struct Player; 

class Enemy : public AnimatedSprite {
public:
	Enemy(Graphic &graphic,std::string textureName, int sourceX, int sourceY, int width, int height, double health, double attackDamage, double attackRate, Vector2<double> spawnPoint, BoundingBox * attackArea, AnimatedSprite::Direction facing, double timeToUpdate);

	virtual ~Enemy();

	virtual void update(double elapsedTime, Player & player, const Camera & camera);
	virtual void draw(Graphic & graphic, const Camera & camera);

	inline double getHealth() const { return this->health; }
	
	void encreaseHealth(const double lives);
	void decreaseHealth(const double damage);

private:
	virtual void setUpAnimation() = 0; // set animation for the enemy

protected:
	virtual void moveRight(); 
	virtual void moveLeft();
	virtual void moveUp();
	virtual void moveDown();
	void moveToPlayer(const Vector2<double> & playerPos);
	void moveToPlayer(const BoundingBox & playerPos);
	virtual void attackPlayer(Player & player, double elapsedTime);
	double attackDamage;
	const double ATTACK_RATE;
	double timeBeforeAttack;
	BoundingBox * attackArea;
	double intakeDamage;
	Timer hitTimer;
	
	BoundingBox::side isPlayerOnSight(const BoundingBox & player) const;
};
#endif
