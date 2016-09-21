#include <SDL2/SDL.h>
#include <iostream>
#include "game.h"
#include "input.h"
#include "graphic.h"
#include "player.h"
#include "level.h"

const double FPS = 50;
const double MAX_TIME = 1000 / FPS;

Game::Game() : 
elapsedTime(0) {
	SDL_Init(SDL_INIT_EVERYTHING);
}

Game::~Game(){
	delete this->player;
	delete this->level;
	this->player = NULL;
	this->level = NULL;
}

void Game::gameLoop(){
	Graphic graphic;
	Input input;
	this->level = new Level(graphic,"level2", Vector2(31,100));
	this->player = new Player(graphic, Vector2(200, 100));	

	double initFrameTime = (double) SDL_GetTicks();	
	bool quit = false;
	while(!quit){
		SDL_Event event;
		
		while(SDL_PollEvent(&event)){
			quit = input.handleInput(event);
			if(input.wasKeyPressed(SDL_SCANCODE_ESCAPE)){
				quit = true;	
			}else if(input.wasKeyPressed(SDL_SCANCODE_RIGHT) && 
						input.wasKeyPressed(SDL_SCANCODE_SPACE)){
				this->player->moveRight();
				this->player->jump();
			}else if(input.wasKeyPressed(SDL_SCANCODE_LEFT) && 
						input.wasKeyPressed(SDL_SCANCODE_SPACE)){
				this->player->moveLeft();
				this->player->jump();
			}else if(input.wasKeyPressed(SDL_SCANCODE_RIGHT)){
				this->player->moveRight();
			}else if(input.wasKeyPressed(SDL_SCANCODE_LEFT)){
				this->player->moveLeft();
			}

			if(input.wasKeyPressed(SDL_SCANCODE_SPACE)){
				this->player->jump();
			}

			if(input.wasKeyReleased(SDL_SCANCODE_RIGHT) || input.wasKeyReleased(SDL_SCANCODE_LEFT)){
				this->player->idle();
			}

			if(input.wasKeyPressed(SDL_SCANCODE_UP)){
				this->player->lookUp();			
			}else if(input.wasKeyPressed(SDL_SCANCODE_DOWN)){
				this->player->lookDown();
			}
			
			if(input.wasKeyReleased(SDL_SCANCODE_UP)){
				this->player->stopLookUp();
			}else if(input.wasKeyReleased(SDL_SCANCODE_DOWN)){
				this->player->stopLookDown();
			}
		}

		this->calculateElapsedTime(initFrameTime);	
		
		SDL_Delay(MAX_TIME - this->elapsedTime);

		this->update();
		this->draw(graphic);
	} 
}

void Game::update(){
	this->player->update(this->elapsedTime);
	this->level->update(this->elapsedTime, this->player);
}

void Game::draw(Graphic &graphic){ 
	graphic.clear();
	this->level->draw(graphic);
	this->player->draw(graphic, *this->level->getCamera());
	graphic.render();
}

double Game::calculateElapsedTime(double &lastElapsedTime){
	double currentFrameDuration = (double) SDL_GetTicks(); 	
	double elapsedTime = currentFrameDuration - lastElapsedTime;
	lastElapsedTime = currentFrameDuration;
	this->elapsedTime = (double) std::min(elapsedTime, MAX_TIME);
}
