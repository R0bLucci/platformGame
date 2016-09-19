#include "globals.h"

struct Tile;

class Camera {
public:
	Camera(Vector2 position, int width, int height, int levelWidth,
		int levelHeight);
	~Camera();
	
	inline int getWidth(){ return this->width; }
	inline int getHeight(){ return this->height; }
	inline Vector2 getPosition(){ return this->position; }
	void move(double x, double y);
    
private:
	Vector2 position;
	int width;
	int height;
	int levelWidth;
	int levelHeight;
};
