#ifndef GRAPHIC_H
#define GRAPHIC_H

struct SDL_Window;
struct SDL_Rederer;

class Graphic {
public:
	Graphic();
	~Graphic();
	SDL_Renderer * getRenderer();
private:
	SDL_Window * window;
	SDL_Renderer * renderer;

};


#endif
