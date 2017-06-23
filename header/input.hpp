#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>
#include <map>
#include "utils.hpp"

class Input {
	
public: 
	Input();
	~Input();
	bool handleInput(const SDL_Event &event);
	bool wasKeyPressed(const SDL_Scancode code);
	bool wasKeyReleased(const SDL_Scancode code);
	bool wasKeyHeld(const SDL_Scancode code);
	void clear();
private:	
	std::map<SDL_Scancode, bool> keyPressed;
	std::map<SDL_Scancode, bool> keyReleased;
	std::map<SDL_Scancode, bool> keyHeld;
};

#endif
