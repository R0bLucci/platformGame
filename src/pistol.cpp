#include "../header/pistol.hpp"
#include "../header/utils.hpp"
#include "../header/pistolBullet.hpp"
#include "../header/logger.hpp"

Pistol::Pistol(Graphic & graphic, double reloadTime, Vector2<double> position) : 
Arm(graphic, 34, 26, 9, 3, reloadTime, position) {
	this->setArmOrientations();
}

Pistol::~Pistol(){}

void Pistol::setArmOrientations() {
	this->sources[HORIZONTAL_LEFT] = std::make_pair(utils::makeRect(29, 10, 9, 3), Vector2<double>(-24.0,2.0));
	this->sources[HORIZONTAL_RIGHT] = std::make_pair(utils::makeRect(34, 26, 9, 3), Vector2<double>(6.0,2.0));
	this->sources[VERTICAL_UP_LEFT] = std::make_pair(utils::makeRect(35, 33, 4, 7), Vector2<double>(-16.0,-24.0));
	this->sources[VERTICAL_UP_RIGHT] = std::make_pair(utils::makeRect(32, 50, 4, 7), Vector2<double>(6.0,-24.0));
	this->sources[VERTICAL_DOWN_LEFT] = std::make_pair(utils::makeRect(36, 72, 4, 7), Vector2<double>(-12.0,8.0));
	this->sources[VERTICAL_DOWN_RIGHT] = std::make_pair(utils::makeRect(31, 87, 4, 7), Vector2<double>(2.0,8.0));
}

Bullet * Pistol::fire(Graphic & graphic){
	if(this->isReadyToFire()){
		Bullet * b = new PistolBullet(graphic, this->bulletOrientationState, this->position);
		this->reload();
		return b;
	}
	return nullptr;
}
