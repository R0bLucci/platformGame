#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include "globals.hpp"
#include "tile.hpp"
#include "vector.hpp"
#include <iostream>

class Camera;

class BoundingBox {
public:
	enum side {
		TOP,
		RIGHT,
		BOTTOM,
		LEFT,
		NONE
	};

	BoundingBox(Vector2<double> origin, int width, int height, Vector2<double> offset = {0.0, 0.0}) :
	x(origin.x + offset.x), y(origin.y + offset.y), w(width), h(height), offset(offset) {} 
	
	BoundingBox(Tile & tile, Vector2<double> offset = {0.0, 0.0}) : x((tile.layerX * tile.w) + offset.x), 
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
	Vector2<double> getRightSideCentre();
	Vector2<double> getLeftSideCentre();
	Vector2<double> getTopSideCentre();
	Vector2<double> getBottomSideCentre();
	double getDistance(Vector2<double> v1, Vector2<double> v2);
	void moveBoundingBox(double x, double y);
	void setOrigin(Vector2<double> newOrigin);
	bool isOnCamera(Camera * camera);
	side sideIsCollidingWith(BoundingBox box);
	friend std::ostream & operator << (std::ostream & o, const BoundingBox & lhs);

private:
	Vector2<double> offset;
};

#endif
