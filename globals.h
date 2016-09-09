#ifndef GLOBALS_H
#define GLOBALS_H

namespace globals {
	const int WIDTH = 640;
	const int HEIGHT = 480; 
	const int SPRITE_SCALER = 2;
	const float WALK_SPEED = 0.2f;
}

struct Vector2 {
	int x, y;	

	Vector2() :
	x(0), y(0) 
	{}

	Vector2(int x, int y) :
	x(x), y(y) 
	{}

	Vector2 zero(){
		return Vector2(0,0);
	}
	
	Vector2 operator *(int factor) {
		Vector2 v(*this);
		v.x *= factor;
		v.y *= factor;
		return v;
	}
};
#endif
