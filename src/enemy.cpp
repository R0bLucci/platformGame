#include "../header/enemy.hpp"
#include "../header/graphic.hpp"
#include "../header/vector.hpp"
#include "../header/camera.hpp"
#include <string>

Enemy::Enemy(Graphic& graphic, std::string textureName, int sourceX, int sourceY,
	int width, int height, Vector2<double> spawnPoint) : 
AnimatedSprite(graphic, textureName, sourceX, sourceY, width, height, spawnPoint, 100),
health(30.0) {}


Enemy::~Enemy(){}


void Enemy::update(double elapsedTime){}


void Enemy::draw(Graphic & graphic, const Camera & camera){}
