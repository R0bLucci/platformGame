#include "../header/player.hpp"
#include <iostream>
#include "../header/boundingBox.hpp"
#include "../header/tile.hpp"
#include "../header/camera.hpp"
#include "../header/logger.hpp"
#include "../header/graphic.hpp"

Player::Player(Graphic & graphic, Vector2<double> spawnPoint) : 
AnimatedSprite(graphic, "MyChar.png", 0, 0, 16, 16, spawnPoint.x, spawnPoint.y, 100),
ACC(0.0015), SLOW_ACC(0.75), MAX_ACC(.345), SLOW_JUMP(.65), currentAcc(0.0), isGrounded(false), isLookingUp(false), isLookingDown(false),  
dx(0.0), dy(0.0), facing(LEFT), 
hud(graphic, "TextBox.png", Vector2<double>(50, 50)),
headBox(Vector2<double>(spawnPoint.x, spawnPoint.y), 16 * globals::SPRITE_SCALER, 16),
bodyBox(Vector2<double>(spawnPoint.x, spawnPoint.y), 18, 16 * globals::SPRITE_SCALER, Vector2<double>(7.0, 0.0)){
	this->setUpAnimation();
}

Player::~Player(){/*logger::log("~Player()");*/}

void Player::setUpAnimation(){
	this->addAnimation("walkLeft", 3, Vector2<double>());
	this->addAnimation("walkRight", 3, Vector2<double>(0, 1));
	this->addAnimation("idleRight", 1, Vector2<double>(0, 1));
	this->addAnimation("idleLeft", 1, Vector2<double>());
	this->addAnimation("lookUpRight", 1, Vector2<double>(3, 1));
	this->addAnimation("lookUpLeft", 1, Vector2<double>(3, 0));
	this->addAnimation("lookDownRight", 1, Vector2<double>(6, 1));
	this->addAnimation("lookDownLeft", 1, Vector2<double>(6, 0));
	
	//set starting animation
	this->currentAnimation = "idleLeft";
}

Vector2<double> Player::getPosition(){
	return Vector2<double>(this->posX + (this->source.w * globals::SPRITE_SCALER / 2), 
			this->posY + (this->source.h * globals::SPRITE_SCALER / 2));
}

void Player::update(double elapsedTime, Camera *camera){

	//logger::log("time:", elapsedTime);

	this->posX += elapsedTime * this->currentAcc;
	this->accelerate(elapsedTime);

	if(this->dy <= globals::GRAVITY_CAP){
		this->dy += globals::GRAVITY * elapsedTime;
	}
	this->posY += this->dy * elapsedTime;
	logger::log("posY POS:", this->posY);

	AnimatedSprite::update(elapsedTime);
	this->headBox.moveBoundingBox(this->posX, this->posY);
	this->bodyBox.moveBoundingBox(this->posX, this->posY);

	if(camera){
		camera->move(this->getPosition().x, this->getPosition().y);
		this->hud.update(elapsedTime, camera->getPosition());
	}

	//logger::log("posX:", this->posX);
	//logger::log("posY:", this->posY);
}

std::vector<Vector2<double>> Player::surrindingArea(int unitX, int unitY){
	std::vector<Vector2<double>> vects(8);
	int x = this->posX / unitX;	
	int y = this->posY / unitY;	
	std::cout << "x " << x << "y " << y << std::endl;
	std::cout << "posX " << posX << "posY " << posY << std::endl;
	vects[0] = Vector2<double>(x,y+2);
	vects[1] = Vector2<double>(x-1,y+2);
	vects[2] = Vector2<double>(x+1,y+2);
	vects[3] = Vector2<double>(x-1,y);
	vects[4] = Vector2<double>(x+1,y);
	vects[5] = Vector2<double>(x-1,y-1);
	vects[6] = Vector2<double>(x+1,y-1);
	vects[7] = Vector2<double>(x,y-1);
	return vects;
	
}

void Player::handleCollision2(std::vector<BoundingBox> boxes){

	for(int i = 0, n = boxes.size(); i < n ; i++){
		//logger::log(std::string("check boxes[") + std::to_string(i) + "]: " + std::to_string(n));
		BoundingBox box = boxes[i];
		//logger::log(box);

		switch(box.sideIsCollidingWith(this->bodyBox)){
			case BoundingBox::side::TOP:
				if(this->dy >= 0.0){
					this->dy = 0.0;
					this->isGrounded = true;
					this->posY = box.getTopSide() - this->bodyBox.getHeight();
					//logger::log("BODY Colliding top");	
				}
			break;
			default: 
			break;
		}

		switch(box.sideIsCollidingWith(this->headBox)){
			case BoundingBox::side::RIGHT:
				this->posX = box.getRightSide();
				//logger::log("HEAD Colliding right");	
				hud.decreaseHealth(1);
			break;
			case BoundingBox::side::LEFT:
				this->posX = box.getLeftSide() - (this->headBox.getWidth());
				hud.decreaseHealth(1);
				//logger::log("HEAD Colliding left");	
				hud.increaseHealth(1);
			break;
			case BoundingBox::side::BOTTOM:
				this->dy = 0;
				this->posY = box.getBottomSide();
				//logger::log("HEAD Colliding bottom");	
			break;
			default: 
			break;
		}

	}
}

void Player::handleCollision(std::vector<BoundingBox*> boxes){
	BoundingBox * box = nullptr;
	for(int i = 0, n = boxes.size(); i < n ; i++){
		box = boxes[i];
		if(!box){ continue; }
		switch(box->sideIsCollidingWith(*this->boundingBox)){
			case BoundingBox::side::TOP:
			this->dy = 0.0;
			//std::cout << "Colliding top" << std::endl;
			this->posY = box->getTopSide() - (this->boundingBox->getHeight() + 1);
			this->isGrounded = true;
			break;
		
			case BoundingBox::side::BOTTOM:
			this->dy = 0;
			this->posY = box->getBottomSide() + 1;
			//std::cout << "Colliding bottom" << std::endl;
			break;

			case BoundingBox::side::RIGHT:
			this->posX = box->getRightSide() + 1;
			//std::cout << "Colliding right" << std::endl;
			break;

			case BoundingBox::side::LEFT:
			this->posX = box->getLeftSide() - (this->boundingBox->getWidth() + 1);
			//std::cout << "Colliding left" << std::endl;
			break;

			case BoundingBox::side::NONE:
			break;
		}

	}
}

void Player::handleTileCollision(Tile * tile){
	BoundingBox * box = tile->getBoundingBox();
	if(!box){ return; }
	switch(box->sideIsCollidingWith(*this->boundingBox)){
		case BoundingBox::side::TOP:
		this->dy = 0.0f;
		this->posY = box->getTopSide() - (this->boundingBox->getHeight() + 1);
		this->isGrounded = true;
		std::cout << "Colliding top" << std::endl;
		break;
	
		case BoundingBox::side::BOTTOM:
		this->dy = 0;
		this->posY = box->getBottomSide() + 1;
		std::cout << "Colliding bottom" << std::endl;
		break;

		case BoundingBox::side::RIGHT:
		this->posX = box->getRightSide() + 1;
		std::cout << "Colliding right" << std::endl;
		break;

		case BoundingBox::side::LEFT:
		this->posX = box->getLeftSide() - (this->boundingBox->getWidth() + 1);
		std::cout << "Colliding left" << std::endl;
		break;

		case BoundingBox::side::NONE:
		std::cout << "Colliding none" << std::endl;
		break;
	}
}

void Player::handleTileCollision(std::vector<Tile *> tiles){
	
	for(int i = 0, n = tiles.size(); i < n; i++){
		if(!tiles[i]) { continue; }
		BoundingBox * box = tiles[i]->getBoundingBox();
		if(!box){ continue; }
		switch(box->sideIsCollidingWith(*this->boundingBox)){
			case BoundingBox::side::TOP:
			this->dy = 0.0;
			this->posY = box->getTopSide() - (this->boundingBox->getHeight() + 1);
			this->isGrounded = true;
			break;
		
			case BoundingBox::side::BOTTOM:
			this->posY = box->getBottomSide() + 1;
			break;

			case BoundingBox::side::RIGHT:
			this->posX = box->getRightSide() + 1;
			break;

			case BoundingBox::side::LEFT:
			this->posX = box->getLeftSide() - (this->boundingBox->getWidth() + 1);
			break;

			case BoundingBox::side::NONE:
			break;
		}
	}
}

void Player::draw(Graphic & graphic, Camera & camera){
	this->hud.draw(graphic, camera.getPosition());
	AnimatedSprite::draw(graphic, camera.getPosition());
	graphic.blitBoundingBox("box.png", NULL, { this->headBox.x, this->headBox.y, this->headBox.w, this->headBox.h});
	graphic.blitBoundingBox("box.png", NULL, { this->bodyBox.x, this->bodyBox.y, this->bodyBox.w, this->bodyBox.h});
}

void Player::moveRight(){
	this->setCurrentAnimation("walkRight");
	this->dx = globals::WALK_SPEED;
	this->facing = RIGHT;
}

void Player::moveLeft(){
	this->setCurrentAnimation("walkLeft");
	this->dx = -globals::WALK_SPEED;
	this->facing = LEFT;
}

void Player::accelerate(double elapsedTime){
	this->currentAcc += this->dx * elapsedTime * this->ACC;
	if(this->dx > 0.0){
		this->currentAcc = std::min(this->currentAcc, this->MAX_ACC);
	}else if(this->dx < 0.0){
		this->currentAcc = std::max(this->currentAcc, -this->MAX_ACC);
	}else if(this->isGrounded){
		this->currentAcc *= this->SLOW_ACC;
	}
}

void Player::jump(){
	if(this->isGrounded){
		this->isGrounded = false;
		this->dy = -globals::JUMP;
	}
}

void Player::stopJump(){
	this->dy *= this->SLOW_JUMP;
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
	this->dx = 0.0;
	this->setCurrentAnimation(this->facing == RIGHT ? "idleRight" : "idleLeft");
}


void Player::stopLookUp(){
	this->isLookingUp = false;
	this->idle();
}

void Player::stopLookDown(){
	this->isLookingDown = false;
	this->idle();
}
