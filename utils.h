#ifndef UTILS_H
#define UTILS_H
#include <SDL2/SDL.h>
#include <iostream>

struct EventPair {
	bool value;
	SDL_Scancode code;
	
	EventPair():
	value(false), code(SDL_SCANCODE_UNKNOWN) 
	{}
	
	EventPair(SDL_Scancode s, bool b) :
	code(s), value(b) 
	{}
	
	~EventPair(){}

	bool getValue(){
		return this->value;	
	}
	
	SDL_Scancode getScancode(){
		return this->code;
	}
	
	void setValue(bool b){
		this->value = b;
	}
	
	void setScancode(SDL_Scancode s){
		this->code = s;
	}

	void resetEventPair(){
		this->code = (SDL_Scancode) 0;
		this->value = false;
	}
};

#endif
