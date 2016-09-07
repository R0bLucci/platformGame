#ifndef GAME_H
#define GAME_H

struct Graphic;

class Game {
public:
	Game();	
	~Game();

	// Game loop that handles event, sprites updates, and draw to screen 
	void gameLoop();
private:
	// Time passed on each interation of the game loop
	unsigned int elapsedTime;

	// Update oblects in the game
	void update();
	// Redraw sprites 
	void draw(Graphic &graphic);	
	// Compute the time that passes on each iteration of the game loop	
	int calculateElapsedTime(int &lastElapsedTime);


};

#endif