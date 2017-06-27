#include "animatedSprite.hpp"

struct Graphic;
struct Camera;

class Enemy : public AnimatedSprite {
public:
	Enemy(Graphic &graphic,std::string textureName, int sourceX, int sourceY, int width, int height, Vector2<double> spawnPoint);

	virtual ~Enemy();

	virtual void update(double elapsedTime);
	virtual void draw(Graphic & graphic, const Camera & camera);

	inline double getHealth() const { return this->health; }

private:
	double health;
	virtual void setUpAnimation() = 0; // set animation for the enemy
};
