#include "../header/HUD.hpp"
#include "../header/graphic.hpp"
#include <iostream>
#include "../header/logger.hpp"

/*---------------------------- Start Health bar -----------------------------*/

HUD::HealthBar::HealthBar(Graphic &graphic, std::string source, const Vector2<double> & position, HUD& hud):
Sprite(graphic, source, 0, 40, HUDUnits::OUTER_HEALTH_BAR_WIDTH, HUDUnits::OUTER_HEALTH_BAR_HEIGHT, position),
hud(hud){
	this->outerBar = this->source; 
	this->innerBar = { 0, 25, HUDUnits::INNER_HEALTH_BAR_WIDTH, 
				HUDUnits::INNER_HEALTH_BAR_HEIGHT };
}

HUD::HealthBar::~HealthBar(){/*logger::log("~HealthBar()");*/}

void HUD::HealthBar::draw(Graphic& graphic, const Vector2<double> & cameraOffset){
	// Save outer health bar reference texture away 
	this->source = this->outerBar;

	// Draw the outer health bar 
	Sprite::draw(graphic, cameraOffset);

	// Draw the inner health bar
	this->source = this->innerBar;	

	// Draw inner health bar on top of the outer offset to the right to see the health level number
	Sprite::draw(graphic, cameraOffset + this->offsetInnerHealthBar());
	
	// Reclaim the source one texture reference for the next time this method is called
	this->source = this->outerBar;
}

void HUD::HealthBar::update(double elapsedTime, const Vector2<double>& cameraOffset){
	Sprite::update(elapsedTime);
	this->hud.offset(this->position.x, this->position.y, cameraOffset);
}

const Vector2<double> HUD::HealthBar::offsetInnerHealthBar() const {
	const Vector2<double> offset = {(double)(-HUDUnits::HEALTH_NUMBER_WIDTH * globals::SPRITE_SCALER) * 3, -2.0 };
	return offset;
}
	
void HUD::HealthBar::decreaseInnerHealthBarLength(int healthLeft){
	double unit = this->getHealthUnit();
	this->innerBar.w = unit * healthLeft;
}

void HUD::HealthBar::increaseInnerHealthBarLength(int health){
	double unit = this->getHealthUnit();
	this->innerBar.w = unit * health;
}

double HUD::HealthBar::getHealthUnit() const{
	return (double) ((double)HUDUnits::INNER_HEALTH_BAR_WIDTH / (double) this->hud.maxHealth);
}
/*------------------------------- End Health bar ----------------------------------------*/


/*---------------------------- Start Health level -----------------------------*/

HUD::HealthLevel::HealthLevel(Graphic &graphic, std::string source, int x, int y, int width, 
					int height, const Vector2<double> & position, HUD& hud):
Sprite(graphic, source, x, y, width, height, position),
onesColumn(0), tensColumn(0),
hud(hud), 
source2(new SDL_Rect())
{}


HUD::HealthLevel::~HealthLevel(){
	delete this->source2;
	this->source2 = nullptr;
	//logger::log("~HealthLevel()");
}

void HUD::HealthLevel::update(double elapsedTime, const Vector2<double>& cameraOffset){
	Sprite::update(elapsedTime);
	this->computeOnesAndTensColumn();

	Vector2<double> offset;
	if(this->source2){
		offset = {(double) this->source.w * globals::SPRITE_SCALER, 0.0};
	}else{
		offset = {(double) (this->source.w * globals::SPRITE_SCALER) * 2, 0.0};
	}
	this->hud.offset(this->position.x, this->position.y, cameraOffset + offset);
}
	
void HUD::HealthLevel::draw(Graphic& graphic, const Vector2<double>& cameraOffset){
	Sprite::draw(graphic, cameraOffset);
	if(this->tensColumn != 0){
		SDL_Rect onesColumns = {
				(int)(this->position.x - cameraOffset.x) + this->source2->w * globals::SPRITE_SCALER, 
				(int)(this->position.y - cameraOffset.y),
				this->source2->w * globals::SPRITE_SCALER,
				this->source2->h * globals::SPRITE_SCALER };
		graphic.blitSurface(this->texture, this->source2, &onesColumns);
	}
}

void HUD::HealthLevel::computeOnesAndTensColumn(){
	std::string sHealth = std::to_string(this->hud.health);
	if(sHealth.size() == 1){
		this->parseHealthValue(this->onesColumn, sHealth, 0, 1);
		this->source.x = this->onesColumn * this->source.w;
		this->tensColumn = 0;
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

/*------------------- End Health level -----------------------*/


/*------------------- Start HUD -----------------------*/

HUD::HUD(Graphic &graphic, std::string source, double health, const Vector2<double>& position) :
position(position),
health(health){
	this->maxHealth = this->health;
	this->healthBar = new HealthBar(graphic, source, position, *this);
	this->healthLevel = new HealthLevel(graphic, source, 0, 56, 
			HUDUnits::HEALTH_NUMBER_WIDTH, HUDUnits::HEALTH_NUMBER_HEIGHT, position, *this);

}


HUD::~HUD(){
	delete this->healthBar;
	delete this->healthLevel;
	this->healthBar = nullptr;
	this->healthLevel = nullptr;
}

void HUD::draw(Graphic &graphic, const Vector2<double> &cameraOffset){
	this->healthBar->draw(graphic, cameraOffset);	
	this->healthLevel->draw(graphic, cameraOffset);	
}
void HUD::update(double elapsedTime, const Vector2<double>& cameraOffset){
	const Vector2<double> offset = cameraOffset + this->position;
	this->healthBar->update(elapsedTime, offset);
	this->healthLevel->update(elapsedTime, offset);
}

void HUD::offset(double&x, double&y, const Vector2<double>&cameraOffset){
	x = cameraOffset.x;
	y = cameraOffset.y;
}

int HUD::getHealth() const {
	return this->health;
}

void HUD::decreaseHealth(int v){
	int tmpHealth = this->health - v;
	if(tmpHealth > 0){
		this->health -= v;
	}else{
		this->health = 0;
	}
	this->healthBar->decreaseInnerHealthBarLength(this->health);
}

void HUD::increaseHealth(int v){
	int tmpHealth = this->health + v;
	if(tmpHealth >= this->maxHealth){
		this->health = this->maxHealth;
	}else{
		this->health += v;
	}
	this->healthBar->increaseInnerHealthBarLength(this->health);
}

void HUD::setMaxHealth(int newMax){
	if(newMax < 3 ){
		return;
	}
	this->maxHealth = newMax;
}
/*------------------- End HUD -----------------------*/
