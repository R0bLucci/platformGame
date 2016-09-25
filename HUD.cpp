#include "HUD.h"
#include "graphic.h"

/*---------------------------- Start Health bar -----------------------------*/

HUD::HealthBar::HealthBar(Graphic &graphic, std::string source, const Vector2 & position, HUD& hud):
Sprite(graphic, source, 0, 40, HUDUnits::OUTER_HEALTH_BAR_WIDTH, HUDUnits::OUTER_HEALTH_BAR_HEIGHT, position.x, position.y),
hud(hud){
	this->outerBar = this->source; 
	this->innerBar = { 0, 25, HUDUnits::INNER_HEALTH_BAR_WIDTH, 
				HUDUnits::INNER_HEALTH_BAR_HEIGHT };
}

HUD::HealthBar::~HealthBar(){}

void HUD::HealthBar::draw(Graphic& graphic, const Vector2 & cameraOffset){
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

void HUD::HealthBar::update(double elapsedTime, const Vector2& cameraOffset){
	Sprite::update(elapsedTime);
	this->hud.offset(this->posX, this->posY, cameraOffset);
}

Vector2 HUD::HealthBar::offsetInnerHealthBar(){
	Vector2 offset = {(double)(-HUDUnits::HEALTH_NUMBER_WIDTH * globals::SPRITE_SCALER) * 3, -2.0 };
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
	return (double) (HUDUnits::INNER_HEALTH_BAR_WIDTH / this->hud.maxHealth);
}
/*------------------------------- End Health bar ----------------------------------------*/


/*---------------------------- Start Health level -----------------------------*/

HUD::HealthLevel::HealthLevel(Graphic &graphic, std::string source, int x, int y, int width, 
					int height, const Vector2 & position, HUD& hud):
source2(new SDL_Rect()),
Sprite(graphic, source, x, y, width, height, position.x, position.y),
hud(hud){}

HUD::HealthLevel::~HealthLevel(){
	delete this->source2;
	this->source2 = NULL;
}

void HUD::HealthLevel::update(double elapsedTime, const Vector2& cameraOffset){
	Sprite::update(elapsedTime);
	this->computeOnesAndTensColumn();

	Vector2 offset;
	if(this->source2){
		offset = {(double) this->source.w * globals::SPRITE_SCALER, 0.0};
	}else{
		offset = {(double) (this->source.w * globals::SPRITE_SCALER) * 2, 0.0};
	}
	this->hud.offset(this->posX, this->posY, cameraOffset + offset);
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
	std::string sHealth = std::to_string(this->hud.health);
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

/*------------------- End Health level -----------------------*/


/*------------------- Start HUD -----------------------*/

HUD::HUD(Graphic &graphic, std::string source, const Vector2& position) :
health(3), 
position(position){
	this->healthBar = new HealthBar(graphic, source, position, *this);
	this->healthLevel = new HealthLevel(graphic, source, 0, 56, 
			HUDUnits::HEALTH_NUMBER_WIDTH, HUDUnits::HEALTH_NUMBER_HEIGHT, position, *this);

	this->maxHealth = this->health;
}


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

void HUD::offset(double&x, double&y, const Vector2&cameraOffset){
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
