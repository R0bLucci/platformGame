#include "../header/text.hpp"
#include "../header/graphic.hpp"
#include "../header/utils.hpp"
#include "../header/globals.hpp"
#include "../header/logger.hpp"

/* Start Text */
Text::Text(Graphic & graphic, Vector2<double> position, double width, double height) : 
texture(graphic.getTexture("TextBox.png", false)), position(position), w(width), h(height) {}

Text::~Text(){}


void Text::update(double elapsedTime) {}

void Text::draw(Graphic & graphic, const Vector2<double> cameraOffset){
	SDL_Rect dest = {       (int) (this->position.x - cameraOffset.x), 
				(int) (this->position.y - cameraOffset.y), 
				(int) this->w * globals::SPRITE_SCALER, 
				(int) this->h * globals::SPRITE_SCALER 
			};
	graphic.blitSurface(this->texture, &this->sourceText, &dest); 
}
/* End Text */

/* Start DamageText */

DamageText::DamageText(Graphic & graphic, Vector2<double> position) :
Text(graphic, position, units::NEG_SIGN_W, units::NEG_SIGN_H), 
onesColumn(graphic, 0.0, position, Digit::color::RED),
tensColumn(graphic, 0.0, position, Digit::color::RED),
riseLevel(0.0),
damage(0.0), drawTime(2000, false), expired(false){
	this->sourceText = {
			units::NEG_SIGN_X,
			units::NEG_SIGN_Y,
			units::NEG_SIGN_W,
			units::NEG_SIGN_H	
	};
}

DamageText::~DamageText(){
	logger::log("~DamageText()");
}

void DamageText::show() {
	this->drawTime.start();
}

void DamageText::accumulateDamage(const double damage){
	this->damage += damage; 
	if(this->damage < 10){
		this->onesColumn.updateSource(this->damage);
	}else{
		std::pair<int, int> digits = this->handleDigits();
		this->onesColumn.updateSource(digits.second);
		this->tensColumn.updateSource(digits.first);
	}
}

bool DamageText::update(double elapsedTime){
	if(!this->isTextShowing()){
		this->resetDamage();
		this->drawTime.stopAndReset();
		this->riseLevel = 0.0;
		return false;	
	}

	this->drawTime.update(elapsedTime);
	this->rise();
	return true;
}

void DamageText::draw(Graphic & graphic, const Vector2<double> cameraOffset){
	if(!this->isTextShowing()) return ;
	Text::draw(graphic, cameraOffset - this->getSignOffset());
	this->onesColumn.draw(graphic, cameraOffset);
	if(this->damage >= 10){
		this->tensColumn.draw(graphic, cameraOffset);
	}
}

Vector2<double> DamageText::getSignOffset() const {
	int x;
	if(this->damage >= 10){
		x = -units::DIGIT_W_AND_H * globals::SPRITE_SCALER * 2;
	}else{
		x = -units::DIGIT_W_AND_H * globals::SPRITE_SCALER;
	}
	return Vector2<double>(x, (units::DIGIT_W_AND_H * 2)/ 2);
}

void DamageText::resetDamage(){
	if(this->drawTime.isClockRunning() && this->damage != 0.0){
		this->damage = 0.0;
	}
}

void DamageText::resetClock(){
	this->drawTime.resetClock();
}

bool DamageText::isTextShowing() const{
	return this->drawTime.isClockRunning() && !this->drawTime.isTimeUp();
}

std::pair<int, int> DamageText::handleDigits(){
	int tensCol, onesCol;
	if(this->damage >= 10.0 && this->damage < 100.0){
		onesCol = (int) this->damage % 10;
		tensCol = (int)(this->damage / 10);
	}else{
		onesCol = tensCol = 9;
	}
	return std::make_pair(tensCol, onesCol);
}

void DamageText::rise(){
	double before = this->riseLevel;
	if(this->riseLevel > -35.0){
		before = (this->riseLevel)--;
	}

	if(this->isExpired()){
		this->position.y += (this->riseLevel - before);
	}else{
		this->position.y += this->riseLevel;
	}
	this->onesColumn.updatePosition(this->position);
	if(this->damage >= 10){
		this->tensColumn.updatePosition(this->position + 
			Vector2<double>(-units::DIGIT_W_AND_H * globals::SPRITE_SCALER, 0.0));
	}
}

void DamageText::setPos(const Vector2<double> & pos){
	this->position = pos;
	this->onesColumn.updatePosition(this->position);
	if(this->damage >= 10){
		this->tensColumn.updatePosition(this->position + 
			Vector2<double>(-units::DIGIT_W_AND_H * globals::SPRITE_SCALER, 0.0));
	}
}

bool DamageText::isExpired() const {
	return this->expired;
}

void DamageText::expire(){
	this->expired = true;
	this->riseLevel = 0.0;
}
/* End DamageText */ 
