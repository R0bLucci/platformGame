#ifndef GAME_H
#define GAME_H

#include "globals.hpp"
#include <memory>

struct Graphic;
struct Player;
struct Level;
struct Camera;

class Game {
public:
	Game();	
	~Game();

	// Game loop that handles event, sprites updates, and draw to screen 
	void gameLoop();
private:

	// Update oblects in the game
	void update();
	// Redraw sprites 
	void draw(Graphic &graphic);	
	// Compute the time that passes on each iteration of the game loop	
	void calculateElapsedTime(double &lastElapsedTime);
	
	// Time passed on each interation of the game loop
	double elapsedTime;

	std::unique_ptr<Player> player;
	std::unique_ptr<Level> level;
};

#endif
