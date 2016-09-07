#include <SDL2/SDL.h>
#include "graphic.h"
#include <iostream>

Graphic::Graphic(){
	this->window = SDL_CreateWindow("Game", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	// Check if window was successufuly creted 
	if(this->window == 0){
		std::cout << SDL_GetError() << std::endl;	
		SDL_Quit();
	}
	this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
	// Check if renderer was successufuly creted 
	if(this->renderer == 0){
		std::cout << SDL_GetError() << std::endl;	
		SDL_Quit();
	}
}

Graphic::~Graphic(){
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
}


SDL_Renderer * Graphic::getRenderer(){
	return this->renderer;
}
