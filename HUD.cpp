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
health(23), source2(new SDL_Rect()),
Sprite(graphic, source, x, y, width, height, position.x, position.y)
{}

HUD::HealthLevel::~HealthLevel(){}

void HUD::HealthLevel::update(double elapsedTime, const Vector2& cameraOffset){
	Sprite::update(elapsedTime);
	this->computeOnesAndTensColumn();

	Vector2 offset;
	if(this->source2){
		offset = {(double) this->source.w * globals::SPRITE_SCALER, 0.0};
	}else{
		offset = {(double) (this->source.w * globals::SPRITE_SCALER) * 2, 0.0};
	}
	HUD::offset(this->posX, this->posY, cameraOffset + offset);
}
	
void HUD::HealthLevel::draw(Graphic& graphic, const Vector2& cameraOffset){
	Sprite::draw(graphic, cameraOffset);
	if(this->source2){
		SDL_Rect onesColumns = {
				(int)(this->posX - cameraOffset.x) + this->source2->w * globals::SPRITE_SCALER, 
				(int)(this->posY - cameraOffset.y),
				this->source2->w * globals::SPRITE_SCALER,
				this->source2->h * globals::SPRITE_SCALER };
		graphic.blitSurface(this->texture, this->source2, &onesColumns);
	}
}

void HUD::HealthLevel::computeOnesAndTensColumn(){
	std::string sHealth = std::to_string(this->health);
	if(sHealth.size() == 1){
		this->parseHealthValue(this->onesColumn, sHealth, 0, 1);
		this->source.x = this->onesColumn * this->source.w;
		this->source2 = NULL;
	} else if(sHealth.size() == 2){
		*this->source2 = this->source;
		this->parseHealthValue(this->tensColumn, sHealth, 0, 1);
		this->parseHealthValue(this->onesColumn, sHealth, 1, 1);
		this->source.x = this->tensColumn * this->source.w;
		this->source2->x = this->onesColumn * this->source2->w;
	}	
}

void HUD::HealthLevel::parseHealthValue(int& column, std::string& sHealth, int beginIndex, int length){
		std::string sOnesColumns(sHealth, beginIndex, length);
		column = std::stoi(sOnesColumns);
}

// End Health level


// Start HUD
HUD::HUD(Graphic &graphic, std::string source, const Vector2& position):
healthBar(new HealthBar(graphic, source, position)), 
healthLevel(new HealthLevel(graphic, source, 0, 56, 8, 8, position)),
position(position)
{}


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
	return this->healthLevel->getHealth();
}

void HUD::decreaseHealth(){
	this->healthLevel->decreaseHealth();
}

void HUD::increaseHealth(){
	this->healthLevel->encreaseHealth();
}

// End HUD
