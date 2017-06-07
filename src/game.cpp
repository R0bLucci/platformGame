#include <SDL2/SDL.h>
#include <iostream>
#include "../header/game.h"
#include "../header/input.h"
#include "../header/graphic.h"
#include "../header/player.h"
#include "../header/level.h"
#include "../header/camera.h"

const double FPS = 50;
const double MAX_TIME = 1000 / FPS;

Game::Game() : 
elapsedTime(0), player(nullptr), level(nullptr) {
	//SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Init(0);
	SDL_InitSubSystem(SDL_INIT_VIDEO);
	SDL_InitSubSystem(SDL_INIT_TIMER);
}

Game::~Game(){
	//delete this->player;
	//delete this->level;
	//this->player = nullptr;
	//this->level = nullptr;
	std::cout << "~Game()" << std::endl;
}

void Game::gameLoop(){
	Graphic graphic;
	Input input;
	this->level.reset(new Level(graphic, "level2"));
	this->player.reset(new Player(graphic, this->level->getSpawnPoint()));

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
		
		if(this->elapsedTime <= MAX_TIME){	
			SDL_Delay(MAX_TIME - this->elapsedTime);
		}

		this->update();
		this->draw(graphic);
	} 
	std::cout << "End of gameLopp()" << std::endl;
}

void Game::update(){
	this->player->update(this->elapsedTime, this->level->getCamera());
	this->level->update(this->elapsedTime, this->player);
}

void Game::draw(Graphic &graphic){ 
	graphic.clear();
	this->level->draw(graphic);
	this->player->draw(graphic, *this->level->getCamera());
	graphic.render();
}

void Game::calculateElapsedTime(double &lastElapsedTime){
	double currentFrameDuration = (double) SDL_GetTicks(); 	
	double elapsedTime = currentFrameDuration - lastElapsedTime;
	lastElapsedTime = currentFrameDuration;
	this->elapsedTime = (double) std::min(elapsedTime, MAX_TIME);
}