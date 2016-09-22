#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "graphic.h"
#include "globals.h"
#include <iostream>

Graphic::Graphic() {
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

SDL_Texture * Graphic::getTexture(const std::string name, bool isLevel){
	std::string path;
	if(isLevel){
		path = "resources/level/" + name;
	}else{
		path = "resources/spriteSheet/" + name;
	}

	if(this->textures.count(path) == 0){
		SDL_Surface * surface = IMG_Load(path.c_str());
		if(!surface){
			return (SDL_Texture*) this->throwError("Could not load surface", name);
		}

		SDL_Texture * texture = SDL_CreateTextureFromSurface(this->renderer, surface);
		if(!texture){
			return (SDL_Texture *) this->throwError("Could not load texture", name);
		}
		
		this->textures[path] = texture;
		SDL_FreeSurface(surface);

		return texture;
	}	
	
	return this->textures[path];
}

void *Graphic::throwError(const std::string errMsg, const std::string filepath){
	std::cout << errMsg << ": " << filepath << std::endl;
	return nullptr;
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
