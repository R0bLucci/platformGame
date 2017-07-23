#include "../header/enemy.hpp"
#include "../header/graphic.hpp"
#include "../header/vector.hpp"
#include "../header/camera.hpp"
#include "../header/player.hpp"
#include "../header/game.hpp"
#include "../header/gameNotification.hpp"
#include "../header/enemyProperty.hpp"
#include "../header/logger.hpp"
#include <string>

Enemy::Enemy(Graphic& graphic, std::string textureName, int sourceX, int sourceY,
	int width, int height, double health, double attackDamage, double attackRate, Vector2<double> spawnPoint, BoundingBox * attackArea, AnimatedSprite::Direction facing,  double timeToUpdate) : 
AnimatedSprite(graphic, textureName, sourceX, sourceY, width, height, health, spawnPoint, facing, timeToUpdate),
attackDamage(attackDamage), ATTACK_RATE(attackRate), timeBeforeAttack(0.0), attackArea(attackArea),
intakeDamage(0.0), hitTimer(1000, false)
{}

Enemy::~Enemy(){
	delete this->attackArea;
	this->attackArea = nullptr;
	damageText->expire();
	damageText->show();

	GameNotification * g = GameNotification::createGameNotification();
	this->deathCloud->setPos(this->getPosition());
	g->addParticleNotifier(this->getDeathCloud());

	logger::log("enemy deleted");
}

void Enemy::update(double elapsedTime, Player & player, const Camera & camera){
	this->hitTimer.update(elapsedTime);
	if(this->hitTimer.isTimeUp() || this->damageText->isTextShowing()){
		hitTimer.stopAndReset();
		damageText->show();
		this->intakeDamage = 0.0;
	}
	AnimatedSprite::update(elapsedTime);
}

void Enemy::draw(Graphic & graphic, const Camera & camera){
	if(camera.isOnCamera(*this->boundingBox)){
		AnimatedSprite::draw(graphic, camera.getPosition());
		graphic.blitBoundingBox("tile.png", NULL, {
					this->attackArea->position.x,
					this->attackArea->position.y, 
					this->attackArea->w, 
					this->attackArea->h
				});
		graphic.blitBoundingBox("box.png", NULL, {
					this->boundingBox->position.x,
					this->boundingBox->position.y, 
					this->boundingBox->w, 
					this->boundingBox->h
				});
	}
}

void Enemy::moveRight(){
	this->position.x += 1.0;
	this->facing = RIGHT;	
}

void Enemy::moveLeft(){
	this->position.x -= 1.0;
	this->facing = LEFT;	
}

void Enemy::moveUp(){
	this->position.y -= 1.0;
}

void Enemy::moveDown(){
	this->position.y += 1.0;
}

BoundingBox::side Enemy::isPlayerOnSight(const BoundingBox & player) const{
	return this->attackArea->sideIsCollidingWith(player);
}

void Enemy::attackPlayer(Player & player, double elapsedTime){ 
		player.decreaseHealth(this->attackDamage);
}

void Enemy::moveToPlayer(const Vector2<double> & playerPos){
	if(playerPos.x > this->position.x){
		this->moveRight();
	} else if(playerPos.x < this->position.x){
		this->moveLeft();
	}

	if(playerPos.y < this->position.y){
		this->moveUp();
		this->facing = (this->facing == RIGHT) ? UP_RIGHT : UP_LEFT;
	}else if(playerPos.y > this->position.y){
		this->moveDown();
		this->facing = (this->facing == RIGHT) ? BOTTOM_RIGHT : BOTTOM_LEFT;
	}
	this->attackArea->moveBoundingBox(this->position);
}

void Enemy::moveToPlayer(const BoundingBox & playerPos){
	if(playerPos.getRightSide() > this->boundingBox->getLeftSide()){
		this->moveRight();
	}else if(playerPos.getLeftSide() < this->boundingBox->getRightSide()){
		this->moveLeft();
	}

	if(playerPos.getTopSide() < this->boundingBox->getTopSide()){
		this->moveUp();
		this->facing = (this->facing == RIGHT) ? UP_RIGHT : UP_LEFT;
	}else if(playerPos.getBottomSide() > this->boundingBox->getBottomSide()){
		this->moveDown();
		this->facing = (this->facing == RIGHT) ? BOTTOM_RIGHT : BOTTOM_LEFT;
	}
	this->attackArea->moveBoundingBox(this->position);
}

void Enemy::encreaseHealth(const double lives){
	AnimatedSprite::encreaseHealth(lives);
}

void Enemy::decreaseHealth(const double damage){
	this->hitTimer.resetAndStart();
	damageText->resetClock();
	//this->intakeDamage += damage;
	this->health -= damage;
	AnimatedSprite::decreaseHealth(damage);
}
