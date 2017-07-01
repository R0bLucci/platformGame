#include "arm.hpp"
#include "vector.hpp"

struct Graphic;

class Pistol : public Arm {
public:
	Pistol(Graphic & graphic, Vector2<double> position);
	
	~Pistol();

	void setArmOrientations();
};
