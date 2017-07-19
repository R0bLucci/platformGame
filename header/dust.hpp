#ifndef DUST_H
#define DUST_H

#include "vector.hpp"
#include "timer.hpp"
#include <SDL2/SDL.h>

class Graphic;

namespace {
	double const X = 16.0;
	double const Y = 0.0;
	double const WIDTH = 16.0;
	double const HEIGHT = 16.0;
		
}

class Dust {
public:
	Dust(Graphic & graphic, const Vector2<double> position);
	~Dust();
	void setPos(const Vector2<double> pos);
	void update(double elapsedTime);
	void draw(Graphic & graphic, const Vector2<double> cameraOffset);

	bool isDissipated() const;
private:
	enum stages {
		NONE, FIRST, SECOND, THIRD, FOURTH, FIFTH, SIXTH, SEVENTH 
	};

	SDL_Texture * texture;
	SDL_Rect source;
	Timer timer;
	Vector2<double> position;
	double w, h;
	int stage;
	void setSource();
};
#endif
