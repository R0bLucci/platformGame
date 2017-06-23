#include "../header/camera.hpp"
#include "../header/logger.hpp"
#include <iostream>
#include <cmath>

Camera::Camera(const Vector2<double>& position, int width, int height, int levelWidth,
		int levelHeight):
	position(position), width(width), height(height), 
	levelWidth(levelWidth), levelHeight(levelHeight){}

Camera::~Camera(){}

void Camera::move(const double x,const double y){
	this->position.x = x - (globals::WIDTH / 2.0);
	this->position.y = y - (globals::HEIGHT / 2.0);
	
	if(this->position.x < 0.0){
		this->position.x = 0.0;
	}
	if(this->position.y < 0.0){
		this->position.y = 0.0;
	}
	if(this->position.x > this->levelWidth - this->width){
		this->position.x = this->levelWidth - this->width;
	}
	if(this->position.y > levelHeight - this->height){
		this->position.y = levelHeight - this->height;
	}
	//logger::log(position);
}
