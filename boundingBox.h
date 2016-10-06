#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include "globals.h"
#include "tile.h"
#include <iostream>

class Camera;

class BoundingBox {
public:
	BoundingBox(Vector2 origin, int width, int height, Vector2 offset = {0.0, 0.0}) :
	x(origin.x + offset.x), y(origin.y + offset.y), w(width), h(height), offset(offset) {} 
	
	BoundingBox(Tile & tile, Vector2 offset = {0.0, 0.0}) : x((tile.layerX * tile.w) + offset.x), 
				y((tile.layerY * tile.h) + offset.y), 
				w(tile.w), h(tile.h), offset(offset) { } 
	~BoundingBox();
	
	int x, y, w, h;	
	
	inline int getTopSide() { return this->y + this->offset.y; }
	inline int getRightSide() { return (this->x + this->offset.x) + this->w; }
	inline int getBottomSide() { return (this->y + this->offset.y) + this->h; }	
	inline int getLeftSide() { return this->x + this->offset.x; }
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
	collision::side sideIsCollidingWith(BoundingBox box);

private:
	Vector2 offset;
};

#endif
