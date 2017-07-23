#include "../header/deathCloud.hpp"
#include "../header/logger.hpp"

DeathCloud::DeathCloud(Graphic & graphic, const Vector2<double> position) :
Particle(graphic, "NpcSym.png", 16, 0, 16, 16, 100, 1, 7, position){}

DeathCloud::~DeathCloud(){logger::log("~Dissipated()");}
