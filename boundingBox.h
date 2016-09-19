#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include "globals.h"
#include "tile.h"
#include <iostream>

class Camera;

class BoundingBox {
public:
	BoundingBox(Vector2 origin, int width, int height) :
	x(origin.x), y(origin.y), w(width), h(height) {} 
	
	BoundingBox(Tile & tile) : x(tile.layerX * tile.w), 
				y(tile.layerY * tile.h), 
				w(tile.w), h(tile.h) { } 
	~BoundingBox();
	
	int x, y, w, h;	
	
	inline int getTopSide() { return this->y; }
	inline int getRightSide() { return this->x + this->w; }
	inline int getBottomSide() { return this->y + this->h; }	
	inline int getLeftSide() { return this->x; }
	inline int getWidth() { return this->w; }
	inline int getHeight() { return this->h; }
	inline void setWidth(double w) { this->w = w;}
	inline void setHeight(double h) { this->h = h;}
	Vector2 getRightSideCentre();
	Vector2 getLeftSideCentre();
	Vector2 getTopSideCentre();
	Vector2 getBottomSideCentre();
	double getDistance(Vector2 v1, Vector2 v2);
	void moveBoundingBox(double x, double y);
	void setOrigin(Vector2 newOrigin);
	bool isOnCamera(Camera * camera);
	collision::side sideIsCollidingWidth(BoundingBox box);
};

#endif
