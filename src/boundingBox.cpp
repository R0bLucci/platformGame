#include "../header/boundingBox.hpp"
#include <math.h>
#include <iostream>
#include "../header/camera.hpp"
#include "../header/logger.hpp"

BoundingBox::side BoundingBox::sideIsCollidingWith(const BoundingBox & box) const{
	int boxTop = box.getTopSide();
	int boxRight = box.getRightSide();
	int boxBottom = box.getBottomSide();
	int boxLeft = box.getLeftSide();
	int distances[4];
	BoundingBox::side sides[4];
	int index = -1;

	// Check left collision with the left side of the bounding box
	if((boxLeft < this->getLeftSide() && boxRight > this->getLeftSide()) &&
		((boxTop > this->getTopSide() && boxTop < this->getBottomSide()) ||
		(boxBottom > this->getTopSide() && boxBottom < this->getBottomSide()))){
		distances[++index] = abs(boxRight - this->getLeftSide());
		sides[index] = BoundingBox::side::LEFT;
	}

	// Check top collision with the top side of this bounding box
	if((boxTop < this->getTopSide() && boxBottom > this->getTopSide()) && 
		((boxLeft > this->getLeftSide() && boxLeft < this->getRightSide()) ||
		(boxRight > this->getLeftSide() && boxRight < this->getRightSide()))){
		distances[++index] = abs(this->getTopSide() - boxBottom);
		sides[index] = BoundingBox::side::TOP;
	}
	
	// Check bottom collision with bottom side of this bounding box	
	if((boxBottom > this->getBottomSide() && boxTop < this->getBottomSide()) && 
		((boxLeft > this->getLeftSide() && boxLeft < this->getRightSide()) ||
		(boxRight > this->getLeftSide() && boxRight < this->getRightSide()))){
		distances[++index] = abs(this->getBottomSide() - boxTop);
		sides[index] = BoundingBox::side::BOTTOM;
	}
	
	// Check right collision with the right side of the bounding box	
	if((boxRight > this->getRightSide() && boxLeft < this->getRightSide()) &&
		((boxTop > this->getTopSide() && boxTop < this->getBottomSide()) ||
		(boxBottom > this->getTopSide() && boxBottom < this->getBottomSide()))){
		distances[++index] = abs(boxRight - this->getLeftSide());
		sides[index] = BoundingBox::side::RIGHT;
	}

	if(index < 0){
		return BoundingBox::side::NONE;
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


/*void BoundingBox::moveBoundingBox(double x, double y){
	this->position.x = std::ceil(x) + this->offset.x; 
	this->position.y = std::ceil(y) + this->offset.y;
}*/

void BoundingBox::moveBoundingBox(const Vector2<double> & pos){
	this->position.x = std::ceil(pos.x) + this->offset.x; 
	this->position.y = std::ceil(pos.y) + this->offset.y;
}

Vector2<double> BoundingBox::getRightSideCentre() const{
	double x = this->getRightSide();
	double y = this->getTopSide() + (this->getHeight() / 2);
	Vector2<double> point(x,y);
	return point;
}

Vector2<double> BoundingBox::getLeftSideCentre() const {
	double x = this->getLeftSide();
	double y = this->getTopSide() + (this->getHeight() / 2);
	Vector2<double> point(x,y);
	return point;
}

Vector2<double> BoundingBox::getTopSideCentre() const {
	double x = this->getLeftSide() + (this->getWidth() / 2);
	double y = this->getTopSide();
	Vector2<double> point(x,y);
	return point;
}

Vector2<double> BoundingBox::getBottomSideCentre() const {
	double x = this->getLeftSide() + (this->getWidth() / 2);
	double y = this->getBottomSide();
	Vector2<double> point(x,y);
	return point;
}

double BoundingBox::getDistance(const Vector2<double> & v1,const Vector2<double> & v2) const{
	Vector2<double> result = v2 - v1;
	double x = result.x * result.x;
	double y = result.y * result.y;
	return sqrt( (x + y) );
}

void BoundingBox::setOrigin(Vector2<double> newOrigin){
	this->position.x = newOrigin.x;
	this->position.y = newOrigin.y;
}

BoundingBox::~BoundingBox(){
	//logger::log("~BoundingBox()");
}

bool BoundingBox::isOnCamera(const Camera * const camera) const{ 

	int cameraLeft, boxLeft;
	int cameraRight, boxRight;
	int cameraTop, boxTop;
	int cameraBottom, boxBottom;

	cameraLeft = camera->getPosition().x;
	cameraRight = camera->getPosition().x + camera->getWidth();
	cameraTop = camera->getPosition().y;
	cameraBottom = camera->getPosition().y + camera->getHeight();
	boxLeft = this->getLeftSide();
	boxRight = this->getRightSide();	
	boxTop = this->getTopSide();
	boxBottom = this->getBottomSide();
	
	if(cameraBottom <= boxTop ||
		cameraTop >= boxBottom ||
		cameraRight <= boxLeft ||
		cameraLeft >= boxRight){
		return false;
	}
	
	return true;	
}

std::ostream & operator<< (std::ostream & o, const BoundingBox & lhs){
	return o << "BoudingBox: [x: " << lhs.position.x << ", y: " << lhs.position.y << ", w: " 
	<< lhs.w << ", h: " << lhs.h << "]";
}
