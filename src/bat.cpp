#include "../header/bat.hpp"
#include "../header/boundingBox.hpp"
#include "../header/player.hpp"
#include "../header/logger.hpp"
#include "../header/camera.hpp"
#include "../header/globals.hpp"
#include "../header/logger.hpp"

namespace {

	const double SCALER = 11.0;
	const double ATTACK_AREA_WIDTH = (16 * globals::SPRITE_SCALER) * SCALER;
	const double ATTACK_AREA_HEIGHT = (16 * globals::SPRITE_SCALER) * SCALER;
	const double AAW_OFFSET = (16 * globals::SPRITE_SCALER) * ((int)(SCALER / -2.0));
	const double AAH_OFFSET = (16 * globals::SPRITE_SCALER) * ((int)(SCALER / -2.0));
	const int ANIMATION_SPEED = 100; 
	const int ATTACK_FRQ = 1000; // attack frequency
}

Bat::Bat(Graphic & graphic, Vector2<double> position) : 
Enemy(graphic, "NpcCemet.png", 32, 32, 16, 16, 30.0, 2.0, ATTACK_FRQ, position, 
new BoundingBox(Vector2<double>(position.x, position.y), ATTACK_AREA_WIDTH, ATTACK_AREA_HEIGHT, 
{AAW_OFFSET, AAH_OFFSET}), LEFT, ANIMATION_SPEED){
	this->setUpAnimation();
}

Bat::~Bat(){
	logger::log("R.I.P. Bat");
}

void Bat::setUpAnimation(){
	this->addAnimation("flyLeft", 3, Vector2<double>(2, 2));
	this->addAnimation("flyRight", 3, Vector2<double>(2, 3));
	this->addAnimation("attackLeft", 1, Vector2<double>(5, 2));
	this->addAnimation("attackRight", 1, Vector2<double>(5, 3));

	this->currentAnimation = "flyLeft";
}

void Bat::update(double elapsedTime, Player & player, const Camera & camera){
	if(camera.isOnCamera(*this->boundingBox) && this->attackArea && player.isColliding(this->attackArea)){
		this->moveToPlayer(player.getPosition());
		this->attackPlayer(player, elapsedTime);			
	}else{
		this->timeBeforeAttack = 0.0;
	}
	Enemy::update(elapsedTime, player, camera);
}

void Bat::moveRight(){
	this->currentAnimation = "flyRight";
	Enemy::moveRight();
}

void Bat::moveLeft(){
	this->currentAnimation = "flyLeft";
	Enemy::moveLeft();
}

void Bat::moveUp(){
	Enemy::moveUp();
}

void Bat::moveDown(){
	Enemy::moveDown();
}

void Bat::attackPlayer(Player & player, double elapsedTime){
	if(this->isColliding(player.getBoundingBox())){
		if(this->timeBeforeAttack <= 0.0){
			this->currentAnimation = (this->position.x < player.position.x) ? "attackRight" : "attackLeft";
			Enemy::attackPlayer(player, elapsedTime);
			this->timeBeforeAttack += this->ATTACK_RATE;
		}else{
			this->timeBeforeAttack -= elapsedTime;
		}
	}
}
