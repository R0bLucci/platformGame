#include "../header/sprite.hpp"
#include "../header/graphic.hpp"
#include "../header/boundingBox.hpp"
#include "../header/logger.hpp"

Sprite::Sprite(Graphic &graphic, std::string textureName, int originX, int originY, int width, int height, Vector2<double> position) : 
position(position), texture(graphic.getTexture(textureName, false)),
boundingBox(new BoundingBox(Vector2<double>(position), width * globals::SPRITE_SCALER, height * globals::SPRITE_SCALER)){
	this->source = { originX, originY, width, height};
}

Sprite::~Sprite(){
	delete this->boundingBox;
	this->boundingBox = nullptr;
	//logger::log("~Sprite()");
}
	
void Sprite::draw(Graphic &graphic, const Vector2<double> & cameraOffset){
	SDL_Rect destination = {(int)(this->position.x - cameraOffset.x), (int)(this->position.y - cameraOffset.y),
		this->source.w * globals::SPRITE_SCALER, this->source.h * globals::SPRITE_SCALER};
	graphic.blitSurface(this->texture, &this->source, &destination);
}

void Sprite::update(double elapsedTime){}

bool Sprite::isColliding(const BoundingBox * const box) const{ 

	int boxLeft, thisLeft;
	int boxRight, thisRight;
	int boxTop, thisTop;
	int boxBottom, thisBottom;

	boxLeft = box->getLeftSide();
	boxRight = box->getRightSide();
	boxTop = box->getTopSide();
	boxBottom = box->getBottomSide();
	thisLeft = this->boundingBox->getLeftSide();
	thisRight = this->boundingBox->getRightSide();	
	thisTop = this->boundingBox->getTopSide();
	thisBottom = this->boundingBox->getBottomSide();
	
	if(boxBottom <= thisTop ||
		boxTop >= thisBottom ||
		boxRight <= thisLeft ||
		boxLeft >= thisRight){
		return false;
	}
	
	return true;	
}

BoundingBox * Sprite::getBoundingBox() const{
	return this->boundingBox;
}
