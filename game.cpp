#include <SDL2/SDL.h>
#include <iostream>
#include "game.h"
#include "graphic.h"


Game::Game() : 
elapsedTime(0)
{
	SDL_Init(SDL_INIT_EVERYTHING);
}

Game::~Game(){}


void Game::gameLoop(){
	Graphic graphic;
	int initFrameTime = SDL_GetTicks();

	while(true){
		SDL_Event event;
		
		while(SDL_PollEvent(&event)){
			if(event.type == SDL_KEYDOWN){
				if(event.key.keysym.scancode == SDL_SCANCODE_ESCAPE){
					return;
				}
			}
		}

		this->calculateElapsedTime(initFrameTime);	
		this->update();
		this->draw(graphic);
	} 
}


void Game::update(){
	std::cout << (float)this->elapsedTime << std::endl;
}

void Game::draw(Graphic &graphic){}


int Game::calculateElapsedTime(int &lastElapsedTime){
	int currentFrameDuration = SDL_GetTicks(); 	
	int elapsedTime = currentFrameDuration - lastElapsedTime;
	lastElapsedTime = currentFrameDuration;
	this->elapsedTime = elapsedTime;
}
