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

		inline int getX() const { return this->source.x; }
		inline int getY() const { return this->source.y; }
		inline int getWidth() const { return this->source.w; }
		inline int getHeight() const { return this->source.h; }

		void update(double elapsedTime, const Vector2& cameraOffset);
		void draw(Graphic& graphic, const Vector2& cameraOffset);

		inline int getHealth() const { return this->health; }
		inline void encreaseHealth(){ this->health++; }
		inline void decreaseHealth(){ this->health--; }
		
	private:
		int onesColumn;
		int tensColumn;
		int health;
		
		// SDL Rect used when the health reaches double digit value
		SDL_Rect *source2;	
	
		void computeOnesAndTensColumn();
		void parseHealthValue(int& column, std::string& sHealth, int beginIndex, int length);

	};
	HealthBar *healthBar;
	HealthLevel* healthLevel;
	
	static void offset(double & x, double & y, const Vector2 &offset);
};
#endif
