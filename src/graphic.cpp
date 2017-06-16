#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../header/graphic.hpp"
#include "../header/globals.hpp"
#include <iostream>

Graphic::Graphic() : window(nullptr), renderer(nullptr) {
	if(!this->window){
		this->window = SDL_CreateWindow("Game", 100, 100, globals::WIDTH, globals::HEIGHT, SDL_WINDOW_SHOWN);
		// Check if window was successufuly creted 
		if(!this->window){
			std::cout << SDL_GetError() << std::endl;	
			SDL_Quit();
		}
	}

	if(!this->renderer){
		this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
		// Check if renderer was successufuly creted 
		if(!this->renderer){
			std::cout << SDL_GetError() << std::endl;	
			SDL_DestroyWindow(this->window);
			SDL_Quit();
		}
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
			SDL_FreeSurface(surface);
			return (SDL_Texture*) this->throwError("Could not load surface", name);
		}

		SDL_Texture * texture = SDL_CreateTextureFromSurface(this->renderer, surface);
		if(!texture){
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
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
	for(auto & texture: textures){
		std::pair<std::string, SDL_Texture*> pair = texture;
		SDL_DestroyTexture(pair.second);
	}
	SDL_DestroyWindow(this->window);
	SDL_DestroyRenderer(this->renderer);
}

void Graphic::blitSurface(SDL_Texture * texture, const SDL_Rect * source, const SDL_Rect * destination){
	SDL_RenderCopy(Graphic::renderer, texture, source, destination); 
}

void Graphic::blitBoundingBox(const std::string textureName, const SDL_Rect * source, const SDL_Rect & destination){
	if(blitBB){
		SDL_Texture * texture = this->getTexture(textureName, false);
		SDL_RenderCopy(Graphic::renderer, texture, source, &destination); 
	}
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
