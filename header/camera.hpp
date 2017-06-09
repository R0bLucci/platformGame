#include "globals.hpp"
#include "vector.hpp"

struct Tile;

class Camera {
public:
	Camera(const Vector2<double>& position, int width, int height, int levelWidth,
		int levelHeight);
	~Camera();
	
	inline int getWidth() const { return this->width; }
	inline int getHeight() const { return this->height; }
	inline Vector2<double> getPosition() const { return this->position; }
	void move(const double x, const double y);
    
private:
	Vector2<double> position;
	int width;
	int height;
	int levelWidth;
	int levelHeight;
};
