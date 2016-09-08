#ifndef GRAPHIC_H
#define GRAPHIC_H

struct SDL_Window;
struct SDL_Rederer;

class Graphic {
public:
	Graphic();
	~Graphic();
	SDL_Renderer * getRenderer();
	
	// Display on the screen what have been drawn to the renderer so far	
	void render();
	// Clear the screen to set a blank canvas for the new frame to be drawn
	void clear();
private:
	SDL_Window * window;
	SDL_Renderer * renderer;

};


#endif
