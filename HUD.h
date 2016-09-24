#ifndef HUD_H
#define HUD_H

#include "sprite.h"
#include <string>
#include "globals.h"

struct Graphic;

class HUD {
public:
	HUD(Graphic & graphic, std::string source, const Vector2 & position);
	~HUD();
	
	const Vector2 position;

	int getHealth() const;
	void decreaseHealth();
	void increaseHealth();	
	void draw(Graphic &graphic, const Vector2 &cameraOffset);
	void update(double elapsedTime,const Vector2& cameraOffset);

private:
	int health;
	class HealthBar : public Sprite {
	public:
		HealthBar(Graphic &graphic, std::string source, const Vector2& position);
		~HealthBar();
		
		void update(double elapsedTime, const Vector2& cameraOffset);
	private:
	};

	class HealthLevel : public Sprite {
	public: 
		HealthLevel(Graphic &graphic, std::string source, int x, int y, int width, int heigh, const Vector2& positiont);	
		~HealthLevel();

		inline int getX() const { return this->x; }
		inline int getY() const { return this->y; }
		inline int getWidth() const { return this->w; }
		inline int getHeight() const { return this->h; }

		void update(double elapsedTime, const Vector2& cameraOffset);
	private:
		int x, y, w, h;

	};
	HealthBar *healthBar;
	HealthLevel* healthLevel;
	
	static void offset(double & x, double & y, const Vector2 &offset);
};
#endif
