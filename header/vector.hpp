#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
template<typename T>
struct Vector2 {
	T x, y;

	Vector2() : x(0), y(0) {}

	Vector2(T x, T y) : x(x), y(y) {}
	
	Vector2(const Vector2<T> & toCopy): x(toCopy.x), y(toCopy.y){}

	~Vector2() {}

	Vector2<T> zero(){
		return Vector2(0,0);
	}

	Vector2<T> operator*(const T& factor) {
		Vector2<T> v(*this);
		v.x *= factor;
		v.y *= factor;
		return v;
	}

	Vector2<T> operator*=(const T& factor) {
		this->x *= factor;
		this->y *= factor;
		return *this;
	}

	Vector2<T>& operator+=(const Vector2<T>& operand) {
		this->x += operand.x;
		this->y += operand.y;
		return *this;
	}

	Vector2<T>& operator-=(const Vector2<T>& operand) {
		this->x -= operand.x;
		this->y -= operand.y;
		return *this;
	}
	
	Vector2<T> operator-(const Vector2<T>& v) {
		T x = this->x - v.x;
		T y = this->y - v.y;
		Vector2<T> result(x,y);
		return result;
	}

	Vector2<T> operator-(const Vector2<T>& v) const{
		T x = this->x - v.x;
		T y = this->y - v.y;
		Vector2<T> result(x,y);
		return result;
	}
	
	Vector2<T> operator+(const Vector2<T>& v) {
		T x = this->x + v.x;
		T y = this->y + v.y;
		Vector2<T> result(x,y);
		return result;
	}

	Vector2<T> operator+(const Vector2<T>& v) const{
		T x = this->x + v.x;
		T y = this->y + v.y;
		Vector2<T> result(x,y);
		return result;
	}

	friend std::ostream & operator<<(std::ostream & o, const Vector2<T> & lhs){
		return o << "Vector2 [x: " << lhs.x << ", y: " << lhs.y << "]";
	}
};

#endif
