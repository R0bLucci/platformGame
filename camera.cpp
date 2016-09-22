#include "camera.h"
#include <iostream>
#include <cmath>

Camera::Camera(Vector2 position, int width, int height, int levelWidth,
		int levelHeight):
	position(position), width(width), height(height), 
	levelWidth(levelWidth), levelHeight(levelHeight){}

Camera::~Camera(){}

void Camera::move(double x, double y){
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
	std::cout << position.x << " "
	<< position.y << std::endl;
}
