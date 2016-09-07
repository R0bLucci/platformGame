#include <SDL2/SDL.h>
#include <iostream>
#include "game.h"
#include "input.h"
#include "graphic.h"

Game::Game() : 
elapsedTime(0)
{
	SDL_Init(SDL_INIT_EVERYTHING);
}

Game::~Game(){}


void Game::gameLoop(){
	Graphic graphic;
	Input input;
	int initFrameTime = SDL_GetTicks();
	
	bool quit = false;
	while(!quit){
		SDL_Event event;
		
		while(SDL_PollEvent(&event)){
			quit = input.handleInput(event);
			if(input.wasKeyPressed(SDL_SCANCODE_ESCAPE)){
				quit = true;	
			}else if(input.wasKeyPressed(SDL_SCANCODE_UP)){
				std::cout << "UP" << std::endl;
			}else if(input.wasKeyPressed(SDL_SCANCODE_DOWN)){
				std::cout << "DOWN" << std::endl;
			}else if(input.wasKeyPressed(SDL_SCANCODE_RIGHT)){
				std::cout << "RIGHT" << std::endl;
			}else if(input.wasKeyPressed(SDL_SCANCODE_LEFT)){
				std::cout << "LEFT" << std::endl;
			}
		}

		this->calculateElapsedTime(initFrameTime);	
		this->update();
		this->draw(graphic);
	} 
}


void Game::update(){
	//std::cout << (float)this->elapsedTime << std::endl;
}

void Game::draw(Graphic &graphic){}


int Game::calculateElapsedTime(int &lastElapsedTime){
	int currentFrameDuration = SDL_GetTicks(); 	
	int elapsedTime = currentFrameDuration - lastElapsedTime;
	lastElapsedTime = currentFrameDuration;
	this->elapsedTime = elapsedTime;
}
