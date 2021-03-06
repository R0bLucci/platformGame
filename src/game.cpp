#include <SDL2/SDL.h>
#include <iostream>
#include "../header/game.hpp"
#include "../header/input.hpp"
#include "../header/graphic.hpp"
#include "../header/player.hpp"
#include "../header/level.hpp"
#include "../header/camera.hpp"
#include "../header/gameNotification.hpp"
#include "../header/logger.hpp"

const double FPS = 50;
const double MAX_TIME = 1000 / FPS;
extern const bool logger::verbose = true;
extern const bool blitBB = false;

GameNotification * Game::getInGameNotifier(){
	logger::log("notification", Game::notifications);
	return Game::notifications;
}

GameNotification * Game::notifications = GameNotification::createGameNotification();

Game::Game() : 
elapsedTime(0), player(nullptr), level(nullptr){
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
	////logger::log("~Game()");
}

void Game::gameLoop(){
	Graphic graphic;
	Input input;
	SDL_Event event;
	this->level.reset(new Level(graphic, "level3"));
	this->player.reset(new Player(graphic, this->level->getSpawnPoint()));
	GameNotification * g = Game::getInGameNotifier(); 
	g->addPlayerNotifier(player);

	double initFrameTime = (double) SDL_GetTicks();	
	bool quit = false;
	while(!quit){
		input.clear();
		while(SDL_PollEvent(&event)){
			//logger::log("POLL EVENT");
			quit = input.handleInput(event);
		}


		if(input.wasKeyPressed(SDL_SCANCODE_UP)){
			this->player->lookUp();			
		}else if(input.wasKeyPressed(SDL_SCANCODE_DOWN)){
			this->player->lookDown();
		}else if(input.wasKeyReleased(SDL_SCANCODE_UP)){
			this->player->stopLookUp();
		}else if(input.wasKeyReleased(SDL_SCANCODE_DOWN)){
			this->player->stopLookDown();
		}

		if(input.wasKeyHeld(SDL_SCANCODE_RIGHT)){
			//logger::log("RIGHT");
			this->player->moveRight();
		}else if(input.wasKeyHeld(SDL_SCANCODE_LEFT)){
			//logger::log("LEFT");
			this->player->moveLeft();
		}else if(input.wasKeyReleased(SDL_SCANCODE_RIGHT) || input.wasKeyReleased(SDL_SCANCODE_LEFT)){
			//logger::log("IDLE");
			this->player->idle();
		}

		if(input.wasKeyPressed(SDL_SCANCODE_Z)){
			//logger::log("JUMP");
			this->player->jump();
		}else if(input.wasKeyReleased(SDL_SCANCODE_Z)){
			//logger::log("STOP JUMP");
			this->player->stopJump();
		}

		if(input.wasKeyPressed(SDL_SCANCODE_X)){
			this->player->fire(graphic, *this->level);
		}


		if(input.wasKeyPressed(SDL_SCANCODE_ESCAPE)){
			quit = true;
		}
		
		this->calculateElapsedTime(initFrameTime);	
		
		if(this->elapsedTime <= MAX_TIME){	
			SDL_Delay(MAX_TIME - this->elapsedTime);
		}

		this->update();
		this->draw(graphic);
	}
}

void Game::update(){
	this->player->update(this->elapsedTime, this->level->getCamera());
	this->level->update(this->elapsedTime, this->player);
	this->notifications->update(this->elapsedTime);
}

void Game::draw(Graphic &graphic){ 
	graphic.clear();
	this->level->draw(graphic);
	this->player->draw(graphic, *this->level->getCamera());
	this->notifications->draw(graphic, this->level->getCamera()->getPosition());
	graphic.render();
}

void Game::calculateElapsedTime(double &lastElapsedTime){
	double currentFrameDuration = (double) SDL_GetTicks(); 	
	double elapsedTime = currentFrameDuration - lastElapsedTime;
	lastElapsedTime = currentFrameDuration;
	this->elapsedTime = (double) std::min(elapsedTime, MAX_TIME);
}
