#ifndef PISTOL_BULLET_H
#define PISTOL_BULLET_H

#include "bullet.hpp"
#include "vector.hpp"
#include <map>
#include <vector>

struct Graphic;
struct Level;

class PistolBullet : public Bullet {
public:
	PistolBullet(Graphic & graphic, Bullet::orientation orientation, Vector2<double> position);
	
	~PistolBullet();	

protected:
	void update(double elapsedTime, Level & levelEnvironment, std::vector<Bullet*>::iterator & bullet);
	void move(const double & elapsedTime);

	void setBulletOrientations();
	void setBulletOffset(const Bullet::orientation  & orientation);
	static bool isSet;
	Vector2<double> offset;
	static std::map<orientation, std::pair<SDL_Rect, Vector2<double>>> sources;
};

#endif
