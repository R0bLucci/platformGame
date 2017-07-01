#include "sprite.hpp"
#include "vector.hpp"
#include "animatedSprite.hpp"
#include <string>
#include <map>

struct Graphic;

class Arm : public Sprite {
public:
	enum orientation {
		HORIZONTAL_RIGHT,	
		HORIZONTAL_LEFT,	
		VERTICAL_UP_RIGHT,
		VERTICAL_UP_LEFT,
		VERTICAL_DOWN_RIGHT,
		VERTICAL_DOWN_LEFT
	}; 
	Arm(Graphic & graphic, int sourceX, int sourceY, int width, int height, Vector2<double> position);

	~Arm();

	void update(double elapsedTime, AnimatedSprite::Direction wielderFacing);
	void draw(Graphic & graphic, const Vector2<double> & cameraOffset, const Vector2<double> & playerPos);
protected:
	std::map<orientation, std::pair<SDL_Rect, Vector2<double>>> sources;
	Vector2<double> offset;
	virtual void setArmOrientations() = 0;
	SDL_Rect armRect(int x, int y, int w, int h) const;
};
