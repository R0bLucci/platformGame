#include "../header/digit.hpp"
#include "../header/graphic.hpp"
#include "../header/globals.hpp"

Digit::Digit(Graphic & graphic, double digit, const Vector2<double> pos, Digit::color color)
: texture(graphic.getTexture("TextBox.png", false)), 
position(pos),
digitColor((color == color::RED) ? units::NEG_DIGIT_Y : units::POS_DIGIT_Y) {
	this->source = {(int) ((int)digit % 10) * units::DIGIT_W_AND_H, 
			this->digitColor,
			units::DIGIT_W_AND_H, 
			units::DIGIT_W_AND_H}; 
}

Digit::~Digit(){}

void Digit::updateSource(const double digit){
	this->source = { (int) ((int)digit % 10) * units::DIGIT_W_AND_H, 
		this->digitColor,
		units::DIGIT_W_AND_H, 
		units::DIGIT_W_AND_H };
}

void Digit::updatePosition(const Vector2<double> pos){
	this->position = pos;
}

void Digit::updateColor(Digit::color color){
	this->digitColor = (color == color::RED) ? units::NEG_DIGIT_Y : units::POS_DIGIT_Y; 
}

void Digit::draw(Graphic & graphic, const Vector2<double> cameraOffset){
	SDL_Rect dest = {
			(int) (this->position.x - cameraOffset.x), 
			(int) (this->position.y - cameraOffset.y), 
			(int) units::DIGIT_W_AND_H * globals::SPRITE_SCALER, 
			(int) units::DIGIT_W_AND_H * globals::SPRITE_SCALER };
	graphic.blitSurface(this->texture, &this->source, &dest); 
}

Vector2<double> & Digit::getPosition() {
	return this->position;
}
