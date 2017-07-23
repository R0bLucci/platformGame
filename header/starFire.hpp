#ifndef STAR_FIRE_H
#define STAR_FIRE_H

#include "vector.hpp"
#include "particle.hpp"

class Graphic;

class StarFire : public Particle {
public:
	StarFire(Graphic & graphic, const Vector2<double> position, bool startAnimation = true);
	~StarFire();

	void setPos(const Vector2<double> & pos);
}; 
#endif 
