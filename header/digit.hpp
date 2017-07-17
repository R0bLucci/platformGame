#ifndef DIGIT_H
#define DIGIT_H

#include "vector.hpp"
#include <SDL2/SDL.h>

class Graphic;

namespace units {
	const int NEG_SIGN_X = 40;
	const int NEG_SIGN_Y = 51;
	const int NEG_SIGN_W = 7;
	const int NEG_SIGN_H = 3;

	const int POS_SIGN_X = 32;
	const int POS_SIGN_Y = 49;
	const int POS_SIGN_W = 7;
	const int POS_SIGN_H = 7;

	const int DIGIT_X = 0;

	const int POS_DIGIT_Y = 56; 
	const int NEG_DIGIT_Y = 64; 

	const int DIGIT_W_AND_H = 8;
}
// draw single base 10 digit if double digit number is supplied the ones column number will be saved 
class Digit {
public:
	enum color { RED, WHITE };

	Digit(Graphic & graphic, double digit, const Vector2<double> pos, Digit::color color);
	~Digit();
	
	void draw(Graphic & graphic, const Vector2<double> cameraOffset);
	void updateSource(const double digit);
	void updateColor(Digit::color color);
	void updatePosition(const Vector2<double> pos);
	Vector2<double> & getPosition();

private:
	SDL_Texture * texture;	
	SDL_Rect source;	
	Vector2<double> position;
	int digitColor;
};
#endif 
