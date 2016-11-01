#include <SDL2/SDL.h>
#include "utils.h"
#include "game.h"

int main(int argc, char* argv[]){
	Game game;
	game.gameLoop();
	std::cout << "End of main()" << std::endl;
	return 0;
}
