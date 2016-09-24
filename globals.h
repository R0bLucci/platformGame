#ifndef GLOBALS_H
#define GLOBALS_H

namespace globals {
	const int WIDTH = 640;
	const int HEIGHT = 512; 
	const int SPRITE_SCALER = 2;
	const double WALK_SPEED = 0.2;
	
	const double GRAVITY = 0.002;
	const double JUMP = 0.7;
	const double GRAVITY_CAP = 0.8;
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
	double x, y;	

	Vector2() :
	x(0), y(0) 
	{}

	Vector2(double x, double y) :
	x(x), y(y) 
	{}

	Vector2 zero(){
		return Vector2(0,0);
	}
	
	Vector2 operator *(double factor) {
		Vector2 v(*this);
		v.x *= factor;
		v.y *= factor;
		return v;
	}
	
	Vector2 operator -(Vector2 v){
		double x = this->x - v.x;
		double y = this->y - v.y;
		Vector2 result(x,y);
		return result;
	}
	
	Vector2 operator +(Vector2 v){
		double x = this->x + v.x;
		double y = this->y + v.y;
	 	Vector2 result(x,y);
		return result;
	}
	
	friend Vector2 operator+(const Vector2 v1, const Vector2 v2){
		double x = v1.x + v2.x;
		double y = v1.y + v2.y;
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
