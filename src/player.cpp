#include "../header/player.h"
#include <iostream>
#include "../header/boundingBox.h"
#include "../header/tile.h"
#include "../header/camera.h"

Player::Player(Graphic & graphic, Vector2 spawnPoint) : 
AnimatedSprite(graphic, "MyChar.png", 0, 0, 16, 16, spawnPoint.x, spawnPoint.y, 100),
isGrounded(false), isLookingUp(false), isLookingDown(false),  
dx(0.0), dy(0.0), facing(LEFT), 
hud(graphic, "TextBox.png", Vector2(50, 50)),
headBox(Vector2(spawnPoint.x, spawnPoint.y), 16 * globals::SPRITE_SCALER, 16),
bodyBox(Vector2(spawnPoint.x, spawnPoint.y), 18, 16 * globals::SPRITE_SCALER, Vector2(7.0, 0.0)){
	this->setUpAnimation();
}

Player::~Player(){std::cout << "~Player()" << std::endl;}

void Player::setUpAnimation(){
	this->addAnimation("walkLeft", 3, Vector2());
	this->addAnimation("walkRight", 3, Vector2(0, 1));
	this->addAnimation("idleRight", 1, Vector2(0, 1));
	this->addAnimation("idleLeft", 1, Vector2());
	this->addAnimation("lookUpRight", 1, Vector2(3, 1));
	this->addAnimation("lookUpLeft", 1, Vector2(3, 0));
	this->addAnimation("lookDownRight", 1, Vector2(6, 1));
	this->addAnimation("lookDownLeft", 1, Vector2(6, 0));
	
	//set starting animation
	this->currentAnimation = "idleLeft";
}

Vector2 Player::getPosition(){
	return Vector2(this->posX + (this->source.w * globals::SPRITE_SCALER / 2), 
			this->posY + (this->source.h * globals::SPRITE_SCALER / 2));
}

void Player::update(double elapsedTime, Camera *camera){
	
	//std::cout << "time " << elapsedTime << std::endl;
	this->posX += this->dx * elapsedTime;

	//std::cout << "dx " << this->dx << std::endl;

	if(this->dy <= globals::GRAVITY_CAP){
		this->dy += globals::GRAVITY * elapsedTime;
		//std::cout << "dy " << this->dy << std::endl;
	}
	this->posY += this->dy * elapsedTime;

	AnimatedSprite::update(elapsedTime);
	this->headBox.moveBoundingBox(this->posX, this->posY);
	this->bodyBox.moveBoundingBox(this->posX, this->posY);

	if(camera){
		camera->move(this->getPosition().x, this->getPosition().y);
		this->hud.update(elapsedTime, camera->getPosition());
	}

	//std::cout << "posX " << this->posX << std::endl;
	//std::cout << "posY " << this->posY << std::endl;
}

std::vector<Vector2> Player::surrindingArea(int unitX, int unitY){
	std::vector<Vector2> vects(8);
	int x = this->posX / unitX;	
	int y = this->posY / unitY;	
	std::cout << "x " << x << "y " << y << std::endl;
	std::cout << "posX " << posX << "posY " << posY << std::endl;
	vects[0] = Vector2(x,y+2);
	vects[1] = Vector2(x-1,y+2);
	vects[2] = Vector2(x+1,y+2);
	vects[3] = Vector2(x-1,y);
	vects[4] = Vector2(x+1,y);
	vects[5] = Vector2(x-1,y-1);
	vects[6] = Vector2(x+1,y-1);
	vects[7] = Vector2(x,y-1);
	return vects;
	
}

void Player::handleCollision2(std::vector<BoundingBox> boxes){

	for(int i = 0, n = boxes.size(); i < n ; i++){
		std::cout << "check boxes[" << i << "]: " << n << std::endl;
		BoundingBox box = boxes[i];

		switch(box.sideIsCollidingWith(this->bodyBox)){
			case collision::TOP:
				if(this->dy >= 0.0){
					this->dy = 0.0;
					this->isGrounded = true;
					this->posY = box.getTopSide() - this->bodyBox.getHeight();
					std::cout << "BODY Colliding top" << std::endl;
				}
			break;
			default: 
			break;
		}

		switch(box.sideIsCollidingWith(this->headBox)){
			case collision::RIGHT:
				this->posX = box.getRightSide();
				std::cout << "HEAD Colliding right" << std::endl;
				hud.decreaseHealth(1);
			break;
			case collision::LEFT:
				this->posX = box.getLeftSide() - (this->headBox.getWidth());
				std::cout << "HEAD Colliding left" << std::endl;
				hud.increaseHealth(1);
			break;
			case collision::BOTTOM:
				this->dy = 0;
				this->posY = box.getBottomSide();
				std::cout << "HEAD Colliding bottom" << std::endl;
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
			case collision::TOP:
			this->dy = 0.0;
			//std::cout << "Colliding top" << std::endl;
			this->posY = box->getTopSide() - (this->boundingBox->getHeight() + 1);
			this->isGrounded = true;
			break;
		
			case collision::BOTTOM:
			this->dy = 0;
			this->posY = box->getBottomSide() + 1;
			//std::cout << "Colliding bottom" << std::endl;
			break;

			case collision::RIGHT:
			this->posX = box->getRightSide() + 1;
			//std::cout << "Colliding right" << std::endl;
			break;

			case collision::LEFT:
			this->posX = box->getLeftSide() - (this->boundingBox->getWidth() + 1);
			//std::cout << "Colliding left" << std::endl;
			break;

			case collision::NONE:
			break;
		}

	}
}

void Player::handleTileCollision(Tile * tile){
	BoundingBox * box = tile->getBoundingBox();
	if(!box){ return; }
	switch(box->sideIsCollidingWith(*this->boundingBox)){
		case collision::TOP:
		this->dy = 0.0f;
		this->posY = box->getTopSide() - (this->boundingBox->getHeight() + 1);
		this->isGrounded = true;
		std::cout << "Colliding top" << std::endl;
		break;
	
		case collision::BOTTOM:
		this->dy = 0;
		this->posY = box->getBottomSide() + 1;
		std::cout << "Colliding bottom" << std::endl;
		break;

		case collision::RIGHT:
		this->posX = box->getRightSide() + 1;
		std::cout << "Colliding right" << std::endl;
		break;

		case collision::LEFT:
		this->posX = box->getLeftSide() - (this->boundingBox->getWidth() + 1);
		std::cout << "Colliding left" << std::endl;
		break;

		case collision::NONE:
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
			case collision::TOP:
			this->dy = 0.0;
			this->posY = box->getTopSide() - (this->boundingBox->getHeight() + 1);
			this->isGrounded = true;
			break;
		
			case collision::BOTTOM:
			this->posY = box->getBottomSide() + 1;
			break;

			case collision::RIGHT:
			this->posX = box->getRightSide() + 1;
			break;

			case collision::LEFT:
			this->posX = box->getLeftSide() - (this->boundingBox->getWidth() + 1);
			break;

			case collision::NONE:
			break;
		}
	}
}

void Player::draw(Graphic & graphic, Camera & camera){
	this->hud.draw(graphic, camera.getPosition());
	AnimatedSprite::draw(graphic, camera.getPosition());
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