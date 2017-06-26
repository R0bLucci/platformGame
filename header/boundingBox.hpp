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
	position(origin.x + offset.x, origin.y + offset.y), w(width), h(height), offset(offset) {} 
	
	BoundingBox(const Tile & tile, Vector2<double> offset = {0.0, 0.0}) : 
	position(tile.position.x + offset.x, tile.position.y + offset.y), w(tile.w), h(tile.h), offset(offset) { } 
	~BoundingBox();
	
	Vector2<int> position;
	int w, h;	
	
	inline int getTopSide() const { return this->position.y + this->offset.y; }
	inline int getRightSide() const { return (this->position.x + this->offset.x) + this->w; }
	inline int getBottomSide() const { return (this->position.y + this->offset.y) + this->h; }	
	inline int getLeftSide() const { return this->position.x + this->offset.x; }
	inline int getWidth() const { return this->w; }
	inline int getHeight() const { return this->h; }
	inline void setWidth(double w) { this->w = w;}
	inline void setHeight(double h) { this->h = h;}
	Vector2<double> getRightSideCentre() const;
	Vector2<double> getLeftSideCentre() const;
	Vector2<double> getTopSideCentre() const;
	Vector2<double> getBottomSideCentre() const;
	double getDistance(const Vector2<double> & v1, const Vector2<double> & v2) const;
	//void moveBoundingBox(double x, double y);
	void moveBoundingBox(const Vector2<double> & pos);
	void setOrigin(Vector2<double> newOrigin);
	bool isOnCamera(const Camera * const camera) const;
	side sideIsCollidingWith(const BoundingBox & box) const;
	friend std::ostream & operator << (std::ostream & o, const BoundingBox & lhs);

private:
	Vector2<double> offset;
};

#endif
