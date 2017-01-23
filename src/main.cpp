#include <SDL2/SDL.h>
#include "../header/utils.h"
#include "../header/game.h"

int main(int argc, char* argv[]){
	Game game;
	game.gameLoop();
	std::cout << "End of main()" << std::endl;
	return 0;
}
