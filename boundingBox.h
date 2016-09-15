#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include "globals.h"

class BoundingBox {
public:
	BoundingBox(Vector2 origin, int width, int height) :
	x(origin.x), y(origin.y), w(width), h(height) {} 

	~BoundingBox();
	
	int x, y, w, h;	
	
	inline int getTopSide() { return this->y; }
	inline int getRightSide() { return this->x + this->w; }
	inline int getBottomSide() { return this->y + this->h; }	
	inline int getLeftSide() { return this->x; }
	inline int getWidth() { return this->w; }
	inline int getHeight() { return this->h; }
	Vector2 getRightSideCentre();
	Vector2 getLeftSideCentre();
	Vector2 getTopSideCentre();
	Vector2 getBottomSideCentre();
	double getDistance(Vector2 v1, Vector2 v2);
	void moveBoundingBox(double x, double y);
	
	collision::side sideIsCollidingWidth(BoundingBox box);
};

#endif
