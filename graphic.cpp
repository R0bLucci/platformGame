#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "graphic.h"
#include "globals.h"
#include <iostream>

Graphic::Graphic(): 
surface(0)
{
	this->window = SDL_CreateWindow("Game", 100, 100, globals::WIDTH, globals::HEIGHT, SDL_WINDOW_SHOWN);
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

SDL_Surface * Graphic::getSurface(const std::string path){
	if(this->surface == 0){
		this->surface = IMG_Load(path.c_str());
	}	

	if(!this->surface){
		std::cout << "Img error loading " << IMG_GetError() << std::endl;
		return nullptr;
	}	
	
	return this->surface;
}

Graphic::~Graphic(){
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
}

void Graphic::blitSurface(SDL_Texture* texture, const SDL_Rect * source, const SDL_Rect * destination){
	SDL_RenderCopy(this->renderer, texture, source, destination); 
}

SDL_Renderer * Graphic::getRenderer(){
	return this->renderer;
}

void Graphic::clear(){
	SDL_RenderClear(this->renderer);
}

void Graphic::render(){
	SDL_RenderPresent(this->renderer);
}
