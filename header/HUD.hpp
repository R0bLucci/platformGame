#ifndef HUD_H
#define HUD_H

#include "sprite.hpp"
#include <string>
#include "globals.hpp"


struct Graphic;

namespace HUDUnits {
	// Health level constants
	const int HEALTH_NUMBER_WIDTH = 8;
	const int HEALTH_NUMBER_HEIGHT = 8;

	// Health bar constans
	const int INNER_HEALTH_BAR_WIDTH = 39;
	const int OUTER_HEALTH_BAR_WIDTH = 63;

	const int OUTER_HEALTH_BAR_HEIGHT = 7; 
	const int INNER_HEALTH_BAR_HEIGHT = 5; 
	
	const int HEALTH_BAR_HEART_LENGTH_UNIT = INNER_HEALTH_BAR_WIDTH / 3;
}

class HUD {
public:
	HUD(Graphic & graphic, std::string source, double playerHealth, const Vector2<double> & position);
	~HUD();
	
	const Vector2<double> position;

	int getHealth() const;
	void decreaseHealth(int v);
	void increaseHealth(int v);
	void setMaxHealth(int newMax);	
	void draw(Graphic &graphic, const Vector2<double> &cameraOffset);
	void update(double elapsedTime,const Vector2<double>& cameraOffset);

private:
	class HealthBar : public Sprite {
	public:
		HealthBar(Graphic &graphic, std::string source, const Vector2<double>& position, HUD& hud);
		~HealthBar();
		
		void update(double elapsedTime, const Vector2<double>& cameraOffset);
		void draw(Graphic& graphic, const Vector2<double>& cameraOffset);
		void decreaseInnerHealthBarLength(int healthLeft);
		void increaseInnerHealthBarLength(int healthLeft);
	private:
		// Inner Healthbar within the healthbar class
		SDL_Rect outerBar;
		SDL_Rect innerBar;
		HUD& hud;

		const Vector2<double> offsetInnerHealthBar() const;
		double getHealthUnit() const;
	};

	class HealthLevel : public Sprite {
	public: 
		HealthLevel(Graphic &graphic, std::string source, int x, int y, int width, int heigh, const Vector2<double>& position, HUD& hud);
		~HealthLevel();

		inline int getX() const { return this->source.x; }
		inline int getY() const { return this->source.y; }
		inline int getWidth() const { return this->source.w; }
		inline int getHeight() const { return this->source.h; }

		void update(double elapsedTime, const Vector2<double>& cameraOffset);
		void draw(Graphic& graphic, const Vector2<double>& cameraOffset);

	private:
		int onesColumn;
		int tensColumn;
		HUD& hud;
		
		// SDL Rect used when the health reaches double digit value
		SDL_Rect *source2;	
	
		void computeOnesAndTensColumn();
		void parseHealthValue(int& column, std::string& sHealth, int beginIndex, int length);

	};
	int health;
	int maxHealth;
	HealthBar *healthBar;
	HealthLevel* healthLevel;

	void offset(double & x, double & y, const Vector2<double> &offset);
};
#endif
