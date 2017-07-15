#include "../header/input.hpp"
#include <iostream>

Input::Input(){}

Input::~Input(){}

bool Input::handleInput(const SDL_Event &event){
	bool quit = false;
	if(event.type == SDL_KEYDOWN){
		this->keyPressed[event.key.keysym.scancode] = true;
		this->keyHeld[event.key.keysym.scancode] = true;
	}else if(event.type == SDL_KEYUP){
		this->keyReleased[event.key.keysym.scancode] = true;
		this->keyHeld[event.key.keysym.scancode] = false;
	}else if(event.type == SDL_QUIT){
		quit = true;
	}	
	return quit;	
}

bool Input::wasKeyPressed(const SDL_Scancode code){
	return this->keyPressed[code];
}

bool Input::wasKeyReleased(const SDL_Scancode code){
	return this->keyReleased[code];
}


bool Input::wasKeyHeld(const SDL_Scancode code){
	return this->keyHeld[code];
}

void Input::clear(){
	this->keyPressed.clear();
	this->keyReleased.clear();
	//this->keyHeld.clear();
}
