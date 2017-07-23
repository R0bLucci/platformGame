#ifndef DEATH_CLOUD_H
#define DEATH_CLOUD_H

#include "vector.hpp"
#include "particle.hpp"

class Graphic;

class DeathCloud : public Particle {
public:
	DeathCloud(Graphic & graphic, const Vector2<double> position);
	~DeathCloud();
};
#endif
