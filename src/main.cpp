#include <SDL2/SDL.h>
#include "../header/utils.hpp"
#include "../header/game.hpp"

int main(int argc, char* argv[]){
	Game game;
	game.gameLoop();
	return 0;
}
