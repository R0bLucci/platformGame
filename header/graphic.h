#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <string>
#include <map>

struct SDL_Window;
struct SDL_Rederer;
struct SDL_Rect;
struct SDL_Texture;

class Graphic {
public:
	Graphic();
	~Graphic();
	SDL_Renderer * getRenderer();
	
	// Display on the screen what have been drawn to the renderer so far	
	void render();
	// Clear the screen to set a blank canvas for the new frame to be drawn
	void clear();
	// Get png file  	
	SDL_Texture * getTexture(const std::string name, bool isLevel = true);
	// Prepare sprite to renderer buffer so that it can be displayed later
	void blitSurface(SDL_Texture * texture, const SDL_Rect * source, const SDL_Rect * destination);
	
private:
	SDL_Window * window;
	SDL_Renderer * renderer;
	std::map<std::string, SDL_Texture*> textures;
	
	void *throwError(const std::string errMsg, const std::string filepath);
};

#endif
