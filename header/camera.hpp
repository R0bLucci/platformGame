#include "globals.hpp"
#include "vector.hpp"
#include "tile.hpp"

struct Tile;
struct BoundingBox;

class Camera {
public:
	Camera(const Vector2<double>& position, int width, int height, int levelWidth,
		int levelHeight);
	~Camera();
	
	inline int getWidth() const { return this->width; }
	inline int getHeight() const { return this->height; }
	inline int getRightSide() const{ return this->position.x + this->width;}
	inline int getLeftSide() const{ return this->position.x; }
	inline int getBottomSide() const{ return this->position.y + this->height; }
	inline int getTopSide() const{ return this->position.y; }
	inline Vector2<double> getPosition() const { return this->position; }
	void move(const double x, const double y);
	//bool isOnCamera(const Tile & tile) const;
	bool isOnCamera(const BoundingBox & box) const;
    
private:
	Vector2<double> position;
	int width;
	int height;
	int levelWidth;
	int levelHeight;
};
