#include "HUD.h"
#include "graphic.h"

//Start Health bar 
HUD::HealthBar::HealthBar(Graphic &graphic, std::string source, const Vector2 & position):
Sprite(graphic, source, 0, 40, 63, 7, position.x, position.y) {}

HUD::HealthBar::~HealthBar(){}


void HUD::HealthBar::update(double elapsedTime, const Vector2& cameraOffset){
	Sprite::update(elapsedTime);
	HUD::offset(this->posX, this->posY, cameraOffset);
}
// End Health bar


// Start Health level

// x: 0 y: 56 , w: 8 , h: 8
HUD::HealthLevel::HealthLevel(Graphic &graphic, std::string source, int x, int y, int width, int height, const Vector2 & position):
Sprite(graphic, source, x, y, width, height, position.x, position.y), x(x), y(y), w(width), h(height){}


HUD::HealthLevel::~HealthLevel(){}

void HUD::HealthLevel::update(double elapsedTime, const Vector2& cameraOffset){
	Sprite::update(elapsedTime);
	HUD::offset(this->posX, this->posY, cameraOffset);
}

// End Health level


// Start HUD
HUD::HUD(Graphic &graphic, std::string source, const Vector2& position):
healthBar(new HealthBar(graphic, source, position)), 
healthLevel(new HealthLevel(graphic, source, 0, 56, 8, 8, position)),
position(position),
health(3){}


HUD::~HUD(){
	delete this->healthBar;
	delete this->healthLevel;
	this->healthBar = NULL;
	this->healthLevel = NULL;
}

void HUD::draw(Graphic &graphic, const Vector2 &cameraOffset){
	this->healthBar->draw(graphic, cameraOffset);	
	this->healthLevel->draw(graphic, cameraOffset);	
}

void HUD::update(double elapsedTime, const Vector2& cameraOffset){
	const Vector2 offset = cameraOffset + this->position;
	this->healthBar->update(elapsedTime, offset);
	this->healthLevel->update(elapsedTime, offset);
}

// Static method
void HUD::offset(double&x, double&y, const Vector2&cameraOffset){
	x = cameraOffset.x;
	y = cameraOffset.y;
}

int HUD::getHealth() const {
	return this->health;
}

void HUD::decreaseHealth(){
	this->health--;
}

void HUD::increaseHealth(){
	this->health++;
}

// End HUD
