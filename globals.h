#ifndef GLOBALS_H
#define GLOBALS_H

namespace globals {
	const int WIDTH = 640;
	const int HEIGHT = 480; 
	const int SPRITE_SCALER = 2;
	const float WALK_SPEED = 0.2f;
	
	const float GRAVITY = 0.002f;
	const float JUMP = 13.0f;
	const float GRAVITY_CAP = 0.8f;
}

namespace collision {
	enum side {
		TOP,
		RIGHT,
		BOTTOM,
		LEFT,
		NONE
	};
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
	
	Vector2 operator -(Vector2 v){
		int x = this->x - v.x;
		int y = this->y - v.y;
		Vector2 result(x,y);
		return result;
	}
};

struct Vector2f {
	float x, y;	

	Vector2f() :
	x(0.0f), y(0.0f) 
	{}

	Vector2f(float x, float y) :
	x(x), y(y) 
	{}

	Vector2f zero(){
		return Vector2f(0.0f,0.0f);
	}
	
	Vector2f operator *(float factor) {
		Vector2f v(*this);
		v.x *= factor;
		v.y *= factor;
		return v;
	}
	
	Vector2f operator -(Vector2f v){
		float x = this->x - v.x;
		float y = this->y - v.y;
		Vector2f result(x,y);
		return result;
	}
};
#endif
