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
	if((boxLeft < this->getLeftSide() && boxRight > this->getLeftSide()) &&
		((boxTop > this->getTopSide() && boxTop < this->getBottomSide()) ||
		(boxBottom > this->getTopSide() && boxBottom < this->getBottomSide()))){
		distances[++index] = std::abs(this->getRightSide() - boxLeft);
		sides[index] = collision::LEFT;
	}

	// Check top collision with the top side of this bounding box
	if((boxTop < this->getTopSide() && boxBottom > this->getTopSide()) && 
		((boxLeft > this->getLeftSide() && boxLeft < this->getRightSide()) ||
		(boxRight > this->getLeftSide() && boxRight < this->getRightSide()))){
		distances[++index] = std::abs(boxBottom - this->getTopSide());
		sides[index] = collision::TOP;
	}
	
	// Check bottom collision with bottom side of this bounding box	
	if((boxBottom > this->getBottomSide() && boxTop < this->getBottomSide()) && 
		((boxLeft > this->getLeftSide() && boxLeft < this->getRightSide()) ||
		(boxRight > this->getLeftSide() && boxRight < this->getRightSide()))){
		distances[++index] = std::abs(this->getBottomSide() - boxTop);
		sides[index] = collision::BOTTOM;
	}
	
	// Check right collision with the right side of the bounding box	
	if((boxRight > this->getRightSide() && boxLeft < this->getRightSide()) &&
		((boxTop > this->getTopSide() && boxTop < this->getBottomSide()) ||
		(boxBottom > this->getTopSide() && boxBottom < this->getBottomSide()))){
		distances[++index] = std::abs(boxRight - this->getLeftSide());
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


void BoundingBox::moveBoundingBox(double x, double y){
	this->x = std::ceil(x); 
	this->y = std::ceil(y);
}

Vector2 BoundingBox::getRightSideCentre(){
	double x = this->getRightSide();
	double y = this->getTopSide() + (this->getHeight() / 2);
	Vector2 point(x,y);
	return point;
}

Vector2 BoundingBox::getLeftSideCentre(){
	double x = this->getLeftSide();
	double y = this->getTopSide() + (this->getHeight() / 2);
	Vector2 point(x,y);
	return point;
}

Vector2 BoundingBox::getTopSideCentre(){
	double x = this->getLeftSide() + (this->getWidth() / 2);
	double y = this->getTopSide();
	Vector2 point(x,y);
	return point;
}

Vector2 BoundingBox::getBottomSideCentre(){
	double x = this->getLeftSide() + (this->getWidth() / 2);
	double y = this->getBottomSide();
	Vector2 point(x,y);
	return point;
}

double BoundingBox::getDistance(Vector2 v1, Vector2 v2){
	Vector2 result = v2 - v1;
	double x = result.x * result.x;
	double y = result.y * result.y;
	return sqrt( (x + y) );
}

BoundingBox::~BoundingBox(){}
