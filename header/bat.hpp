#include "enemy.hpp"
#include "vector.hpp"

struct Graphic;
struct Player;
struct Camera;

class Bat : public Enemy {
public:	
	Bat(Graphic & graphic, Vector2<double> position);

	~Bat();
	void update(double elapsedTime, Player & player, const Camera & camera);

private:

	void setUpAnimation();
	void moveUp();
	void moveRight();
	void moveDown();
	void moveLeft();
	
	void attackPlayer(Player & player, double elapsedTime);
};
