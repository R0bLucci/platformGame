#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>
#include <vector>
#include "utils.h"

class Input {
	
public: 
	Input();
	~Input();
	bool handleInput(SDL_Event &event);
	bool wasKeyPressed(SDL_Scancode code);
	bool wasKeyReleased(SDL_Scancode code);
private:	
	std::vector<EventPair> keysPressed;
	std::vector<EventPair> keysReleased;
	void clearEventPairList();
};

#endif
