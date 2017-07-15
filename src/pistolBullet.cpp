#include "../header/pistolBullet.hpp"
#include "../header/utils.hpp"
#include "../header/level.hpp"
#include "../header/enemy.hpp"
#include "../header/logger.hpp"
#include "../header/globals.hpp"

bool PistolBullet::isSet = false;

std::map<Bullet::orientation, std::pair<SDL_Rect, Vector2<double>>> PistolBullet::sources;

PistolBullet::PistolBullet(Graphic & graphic, Bullet::orientation orientation, Vector2<double> position) :
Bullet(graphic, 64, 23, 16, 2, 1.0, orientation, 200, position) {
	this->setBulletOrientations();
	this->source = PistolBullet::sources[orientation].first;
	this->setBulletOffset(orientation);	
}


PistolBullet::~PistolBullet(){
	logger::log("~PistolBullet()");
}

void PistolBullet::update(double elapsedTime, Level & levelEnvironment, std::vector<Bullet *>::iterator & bullet){
	if(!this->hasBulletCollided(levelEnvironment, bullet)){
		this->move(elapsedTime);
		this->updateLifeTime(elapsedTime);
		Bullet::update(elapsedTime, levelEnvironment, bullet);
	}
}

void PistolBullet::setBulletOrientations(){
	if(!PistolBullet::isSet){
		PistolBullet::sources[HORIZONTAL_RIGHT] = std::make_pair(utils::makeRect(96,23,16,2), Vector2<double>(15.0,1.0));
		PistolBullet::sources[HORIZONTAL_LEFT] = std::make_pair(utils::makeRect(64,23,16,2), Vector2<double>(-25.0,1.0));
		PistolBullet::sources[VERTICAL_UP] = std::make_pair(utils::makeRect(87,16,2,16), Vector2<double>(2.0,-25.0)); 
		PistolBullet::sources[VERTICAL_DOWN] = std::make_pair(utils::makeRect(119,16,2,16), Vector2<double>(2.0,15.0)); 
		PistolBullet::isSet = true;
	}
}

void PistolBullet::setBulletOffset(const Bullet::orientation & orientation){
	this->offset = PistolBullet::sources[orientation].second;
	this->position += this->offset;

	this->boundingBox->position.x = this->position.x;
	this->boundingBox->position.y = this->position.y;

	this->boundingBox->w = PistolBullet::sources[orientation].first.w * globals::SPRITE_SCALER;
	this->boundingBox->h = PistolBullet::sources[orientation].first.h * globals::SPRITE_SCALER;
}

void PistolBullet::move(const double & elapsedTime){
	switch(this->bulletOrientation){
		case HORIZONTAL_RIGHT:
			this->position.x += .7 * elapsedTime;
		break;
		case HORIZONTAL_LEFT:
			this->position.x -= .7 * elapsedTime;
		break;
		case VERTICAL_UP:
			this->position.y -= .7 * elapsedTime;
		break;
		case VERTICAL_DOWN:
			this->position.y += .7 * elapsedTime;
		break;
	}
}
