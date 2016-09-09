#include "input.h"
#include <iostream>

Input::Input(){}

Input::~Input(){}

bool Input::handleInput(SDL_Event &event){
	this->clearEventPairList();
	bool quit = false;
	if(event.type == SDL_KEYDOWN){
		this->keysPressed.push_back(EventPair(event.key.keysym.scancode, true));		
	}else if (event.type = SDL_KEYUP){
		this->keysReleased.push_back(EventPair(event.key.keysym.scancode, true));		
	}else if(event.type = SDL_QUIT){
		quit = true;
	}	
	return quit;	
}

bool Input::wasKeyPressed(SDL_Scancode code){
	for(unsigned int i = 0, n = this->keysPressed.size(); i < n; i++){
		if(this->keysPressed.at(i).getScancode() ==  code){
			return this->keysPressed.at(i).getValue();
		}
	}
	return false;
}

bool Input::wasKeyReleased(SDL_Scancode code){
	for(unsigned int i = 0, n = this->keysReleased.size(); i < n; i++){
		if(this->keysReleased.at(i).getScancode() ==  code){
			return this->keysReleased.at(i).getValue();
		}
	}
	return false;
}

void Input::clearEventPairList(){
	this->keysPressed.clear();
	this->keysReleased.clear();
}

