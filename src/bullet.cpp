#include "../header/bullet.hpp"
#include "../header/level.hpp"
#include "../header/camera.hpp"
#include "../header/boundingBox.hpp"
#include "../header/enemy.hpp"
#include "../header/graphic.hpp"
#include "../header/logger.hpp"

Bullet::Bullet(Graphic & graphic, int sourceX, int sourceY, int width, int height, double firePower, orientation orientation, double timeToLive, Vector2<double> position) :
Sprite(graphic, "Bullet.png", sourceX, sourceY, width, height, position),
bulletOrientation(orientation),
TIME_TO_LIVE(timeToLive), lifeTime(0.0), firePower(firePower) {}

Bullet::~Bullet(){
	logger::log("~Bullet()");
}

void Bullet::draw(Graphic & graphic, Camera & camera){
	if(camera.isOnCamera(*this->boundingBox)){
		Sprite::draw(graphic, camera.getPosition());
		graphic.blitBoundingBox("box.png", NULL, {
				this->boundingBox->position.x,
				this->boundingBox->position.y,
				this->boundingBox->w,
				this->boundingBox->h,
			});
	}	
}

void Bullet::update(double elapsedTime, Level & levelEnviroment, std::vector<Bullet*>::iterator & bullet) {
	this->boundingBox->moveBoundingBox(this->position);
	Sprite::update(elapsedTime);
}

bool Bullet::hasBulletCollided(Level & level, std::vector<Bullet*>::iterator & bullet){
	bool isBulletBusted = false;
	if(this->handleWallCollision(level.collidables)){
		this->eraseBullet(level.firedBullets, bullet);
		isBulletBusted = true;
	}else if(this->hasBulletHitEnemy(level.enemies)){
		this->eraseBullet(level.firedBullets, bullet);
		isBulletBusted = true;
	}else if(this->isTimeToDie()){
		this->eraseBullet(level.firedBullets, bullet);
		isBulletBusted = true;
	}
	return isBulletBusted;
}

bool Bullet::hasBulletHitEnemy(std::vector<std::shared_ptr<Enemy>> & enemies){
	std::vector<std::shared_ptr<Enemy>>::iterator begin = enemies.begin();
	const std::vector<std::shared_ptr<Enemy>>::iterator end  = enemies.end();
	while(begin != end){
		if(this->isColliding((*begin)->getBoundingBox())){
			logger::log("enemy hit"); 
			(*begin)->decreaseHealth(this->firePower);
			if((*begin)->isDead()){
				enemies.erase(begin);
			}
			return true;
		}
		++begin;
	}
	return false;
}

bool Bullet::handleWallCollision(std::vector<BoundingBox*> & collidables){
	std::vector<BoundingBox*>::iterator begin = collidables.begin();
	const std::vector<BoundingBox*>::iterator end = collidables.end();
	while(begin != end){
		if(this->isColliding((*begin))){
			logger::log("wall collision"); 
			return true;
		}
		++begin;
	}
	return false;
}

void Bullet::eraseBullet(std::vector<Bullet*> & firedBullets, std::vector<Bullet*>::iterator & bullet){
	delete *bullet;
	bullet = firedBullets.erase(bullet);
}


bool Bullet::isTimeToDie() const {
	return this->lifeTime >= this->TIME_TO_LIVE;
}

void Bullet::updateLifeTime(double elapsedTime){
	this->lifeTime += elapsedTime;
}
