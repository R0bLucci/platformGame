#include "../header/pistol.hpp"

Pistol::Pistol(Graphic & graphic, Vector2<double> position) : 
Arm(graphic, 34, 25, 9, 3, position) {
	this->setArmOrientations();
}

Pistol::~Pistol(){}

void Pistol::setArmOrientations() {
	this->sources[HORIZONTAL_LEFT] = std::make_pair(Arm::armRect(29, 10, 9, 3), Vector2<double>(-24.0,2.0));
	this->sources[HORIZONTAL_RIGHT] = std::make_pair(Arm::armRect(34, 26, 9, 3), Vector2<double>(6.0,2.0));
	this->sources[VERTICAL_UP_LEFT] = std::make_pair(Arm::armRect(35, 33, 4, 7), Vector2<double>(-16.0,-24.0));
	this->sources[VERTICAL_UP_RIGHT] = std::make_pair(Arm::armRect(32, 50, 4, 7), Vector2<double>(6.0,-24.0));
	this->sources[VERTICAL_DOWN_LEFT] = std::make_pair(Arm::armRect(36, 72, 4, 7), Vector2<double>(-12.0,8.0));
	this->sources[VERTICAL_DOWN_RIGHT] = std::make_pair(Arm::armRect(31, 87, 4, 7), Vector2<double>(2.0,8.0));
}
