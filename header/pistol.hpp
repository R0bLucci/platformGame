#ifndef PISTOL_H
#define PISTOL_H

#include "arm.hpp"
#include "vector.hpp"

struct Graphic;
struct Bullet;

class Pistol : public Arm {
public:
	Pistol(Graphic & graphic, double reloadTime, Vector2<double> position);
	
	~Pistol();

	void setArmOrientations();
	
	Bullet * fire(Graphic & graphic);
};

#endif
