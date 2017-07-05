#include "../header/utils.hpp"

namespace utils {
	SDL_Rect makeRect(int x, int y, int w, int h){
		SDL_Rect rect;
		rect.x = x; rect.y = y; rect.w = w; rect.h = h;
		return rect;
	}
}
