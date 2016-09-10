#include "boundingBox.h"
#include <math.h>
#include <iostream>

collision::side BoundingBox::sideIsCollidingWidth(BoundingBox box){
	int boxTop = box.getTopSide();
	int boxRight = box.getRightSide();
	int boxBottom = box.getBottomSide();
	int boxLeft = box.getLeftSide();
	double distances[4];
	collision::side sides[4];
	int index = -1;

	// Check left collision with the left side of the bounding box
	if((boxLeft <= this->getLeftSide() && boxRight >= this->getLeftSide()) &&
		((boxTop >= this->getTopSide() && boxTop <= this->getBottomSide()) ||
		(boxBottom >= this->getTopSide() && boxBottom <= this->getBottomSide()))){
		distances[++index] = this->getDistance(this->getLeftSideCentre(), box.getRightSideCentre());
		sides[index] = collision::LEFT;
	}

	// Check top collision with the top side of this bounding box
	if((boxTop <= this->getTopSide() && boxBottom >= this->getTopSide()) && 
		((boxLeft >= this->getLeftSide() && boxLeft <= this->getRightSide()) ||
		(boxRight >= this->getLeftSide() && boxRight <= this->getRightSide()))){
		distances[++index] = this->getDistance(this->getTopSideCentre(), box.getBottomSideCentre());
		sides[index] = collision::TOP;
	}
	
	// Check bottom collision with bottom side of this bounding box	
	if((boxBottom >= this->getBottomSide() && boxTop <= this->getBottomSide()) && 
		((boxLeft >= this->getLeftSide() && boxLeft <= this->getRightSide()) ||
		(boxRight >= this->getLeftSide() && boxRight <= this->getRightSide()))){
		distances[++index] = this->getDistance(this->getBottomSideCentre(), box.getTopSideCentre());
		sides[index] = collision::BOTTOM;
	}
	
	// Check right collision with the right side of the bounding box	
	if((boxRight >= this->getRightSide() && boxLeft <= this->getRightSide()) &&
		((boxTop >= this->getTopSide() && boxTop <= this->getBottomSide()) ||
		(boxBottom >= this->getTopSide() && boxBottom <= this->getBottomSide()))){
		distances[++index] = this->getDistance(this->getRightSideCentre(), box.getLeftSideCentre());
		sides[index] = collision::RIGHT;
	}

	if(index < 0){
		return collision::NONE;
	}
	double closest = distances[0];
	int sidesIndex = 0;
	for(int i = 1; i < index + 1; i++){
		if(distances[i] < closest){
			closest = distances[i];
			sidesIndex = i;
		}
	} 
	return sides[sidesIndex];	
}


void BoundingBox::moveBoundingBox(float x, float y){
	this->x = std::ceil(x); 
	this->y = std::ceil(y);
}

Vector2f BoundingBox::getRightSideCentre(){
	float x = this->getRightSide();
	float y = this->getTopSide() + (this->getHeight() / 2);
	Vector2f point(x,y);
	return point;
}

Vector2f BoundingBox::getLeftSideCentre(){
	float x = this->getLeftSide();
	float y = this->getTopSide() + (this->getHeight() / 2);
	Vector2f point(x,y);
	return point;
}

Vector2f BoundingBox::getTopSideCentre(){
	float x = this->getLeftSide() + (this->getWidth() / 2);
	float y = this->getTopSide();
	Vector2f point(x,y);
	return point;
}

Vector2f BoundingBox::getBottomSideCentre(){
	float x = this->getLeftSide() + (this->getWidth() / 2);
	float y = this->getBottomSide();
	Vector2f point(x,y);
	return point;
}

double BoundingBox::getDistance(Vector2f v1, Vector2f v2){
	Vector2f result = v2 - v1;
	float x = result.x * result.x;
	float y = result.y * result.y;
	return sqrt( (x + y) );
}

BoundingBox::~BoundingBox(){}
