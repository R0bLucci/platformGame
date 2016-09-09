#include "player.h"
#include <iostream>


Player::Player(Graphic & graphic, Vector2 spawnPoint) : 
isGrounded(true), dx(0.0f), dy(0.0f), facing(LEFT), 
isLookingUp(false), isLookingDown(false),
AnimatedSprite(graphic, 0, 0, 16, 16, spawnPoint.x, spawnPoint.y, 100) {
	this->setUpAnimation();
}

Player::~Player(){}

void Player::setUpAnimation(){
	this->addAnimation("walkLeft", 3, Vector2());
	this->addAnimation("walkRight", 3, Vector2(0, 1));
	this->addAnimation("idleRight", 1, Vector2(0, 1));
	this->addAnimation("idleLeft", 1, Vector2());
	this->addAnimation("lookUpRight", 1, Vector2(3, 1));
	this->addAnimation("lookUpLeft", 1, Vector2(3, 0));
	this->addAnimation("lookDownRight", 1, Vector2(6, 1));
	this->addAnimation("lookDownLeft", 1, Vector2(6, 0));
}

void Player::update(float elapsedTime){
	if(this->dx > 0.0f){
		this->posX += std::ceil(this->dx * elapsedTime);
	}else{
		this->posX += this->dx * elapsedTime;
	}
	std::cout << "elapsed: " << elapsedTime << std::endl;
	std::cout << "dx: " << this->dx << std::endl;
	std::cout << this->dx * elapsedTime << std::endl;
	AnimatedSprite::update(elapsedTime);
}

void Player::draw(Graphic & graphic){

	AnimatedSprite::draw(graphic);
}

void Player::moveRight(){
	this->setCurrentAnimation("walkRight");
	if(this->isGrounded){
		this->dx = globals::WALK_SPEED;
	}
	this->facing = RIGHT;
}

void Player::moveLeft(){
	this->setCurrentAnimation("walkLeft");
	if(this->isGrounded){
		this->dx = -globals::WALK_SPEED;
	}
	this->facing = LEFT;
}

void Player::stopMoving(){
	this->dx = 0.0f;
}

void Player::jump(){}

void Player::lookUp(){
	this->isLookingUp = true;
	this->dx = 0.0f;
	if(this->isGrounded){
		this->setCurrentAnimation(this->facing == RIGHT ? "lookUpRight" : "lookUpLeft");	
	}
}

void Player::lookDown(){
	this->isLookingDown = true;
	this->dx = 0.0f;
	if(this->isGrounded){
		this->setCurrentAnimation(this->facing == RIGHT ? "lookDownRight" : "lookDownLeft");	
	}
}

void Player::idle() {
	if(this->isGrounded){
		this->dx = 0.0f;
		this->setCurrentAnimation(this->facing == RIGHT ? "idleRight" : "idleLeft");
	}
}

void Player::stopLookUp(){
	this->isLookingUp = false;
	this->idle();
}

void Player::stopLookDown(){
	this->isLookingDown = false;
	this->idle();
}
