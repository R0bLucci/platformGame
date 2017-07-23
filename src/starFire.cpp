#include "../header/starFire.hpp"
#include "../header/globals.hpp"
#include "../header/logger.hpp"

StarFire::StarFire(Graphic & graphic, const Vector2<double> position, bool startAnimation) : 
Particle(graphic, "Caret.png", 0, 48, 16, 16, 30, 0, 4, position, startAnimation) {}

StarFire::~StarFire(){logger::log("~StarFire()");}

void StarFire::setPos(const Vector2<double> & pos){
	Particle::setPos(pos);	
	this->position = this->getCenteredPosition();
}
