#include "player.h"
#include <iostream>
#include "boundingBox.h"


Player::Player(Graphic & graphic, Vector2 spawnPoint) : 
isGrounded(false), dx(0.0), dy(0.0), facing(LEFT), 
isLookingUp(false), isLookingDown(false),
AnimatedSprite(graphic, 0, 0, 16, 16, spawnPoint.x, spawnPoint.y, 100) {
	this->boundingBox = new BoundingBox(Vector2(spawnPoint.x, spawnPoint.y), 
		this->source.w * globals::SPRITE_SCALER, this->source.h * globals::SPRITE_SCALER);
	box = new BoundingBox(Vector2(0, 480), 680, 400);
	box2 = new BoundingBox(Vector2(0, 448), 64, 32);
	this->setUpAnimation();
}

Player::~Player(){
	delete this->boundingBox;
	delete this->box;
	delete this->box2;
}

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

void Player::update(double elapsedTime){
	
	std::cout << "time " << elapsedTime << std::endl;
	this->posX += this->dx * elapsedTime;

	std::cout << "dx " << this->dx << std::endl;
	
	if(this->dy <= globals::GRAVITY_CAP){
		this->dy += globals::GRAVITY * elapsedTime;
		std::cout << "dy " << this->dy << std::endl;
	}

	this->posY += this->dy * elapsedTime;

	std::cout << "posX " << this->posX << std::endl;
	std::cout << "posY " << this->posY << std::endl;

	AnimatedSprite::update(elapsedTime);
	this->boundingBox->moveBoundingBox(this->posX, this->posY);
	switch(box->sideIsCollidingWidth(*this->boundingBox)){
		case collision::TOP:
		this->dy = 0.0f;
		this->posY = box->getTopSide() - (this->boundingBox->getHeight() + 1);
		this->isGrounded = true;
		break;
	
		case collision::BOTTOM:
		break;

		case collision::RIGHT:
		break;

		case collision::LEFT:
		break;

		case collision::NONE:
		break;
	}	
	switch(box2->sideIsCollidingWidth(*this->boundingBox)){
		case collision::TOP:
		this->dy = 0.0f;
		this->posY = box2->getTopSide() - (this->boundingBox->getHeight() + 1);
		this->isGrounded = true;
		break;
	
		case collision::BOTTOM:
		break;

		case collision::RIGHT:
		this->posX = box2->getRightSide() + 1;
		break;

		case collision::LEFT:
		this->posX = box2->getLeftSide() - (this->boundingBox->getWidth() + 1);
		break;

		case collision::NONE:
		break;
	}	
}

void Player::draw(Graphic & graphic){

	AnimatedSprite::draw(graphic);
}

void Player::moveRight(){
	//if(this->isGrounded){
		this->setCurrentAnimation("walkRight");
		this->dx = globals::WALK_SPEED;
	//}
	this->facing = RIGHT;
}

void Player::moveLeft(){
	//if(this->isGrounded){
		this->setCurrentAnimation("walkLeft");
		this->dx = -globals::WALK_SPEED;
	//}
	this->facing = LEFT;
}

void Player::jump(){
	if(this->isGrounded){
		this->isGrounded = false;
		this->dy = 0.0;
		this->dy -= globals::JUMP;
	}
}

void Player::stopMoving(){
	this->dx = 0.0;
}

void Player::lookUp(){
	this->isLookingUp = true;
	this->dx = 0.0;
	if(this->isGrounded){
		this->setCurrentAnimation(this->facing == RIGHT ? "lookUpRight" : "lookUpLeft");	
	}
}

void Player::lookDown(){
	this->isLookingDown = true;
	this->dx = 0.0;
	if(this->isGrounded){
		this->setCurrentAnimation(this->facing == RIGHT ? "lookDownRight" : "lookDownLeft");	
	}
}

void Player::idle() {
	//if(this->isGrounded){
		this->dx = 0.0;
		this->setCurrentAnimation(this->facing == RIGHT ? "idleRight" : "idleLeft");
	//}

}

void Player::stopLookUp(){
	this->isLookingUp = false;
	this->idle();
}

void Player::stopLookDown(){
	this->isLookingDown = false;
	this->idle();
}
