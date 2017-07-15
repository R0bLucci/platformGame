#ifndef TEXT_H
#define TEXT_H

#include "vector.hpp"
#include "sprite.hpp"
#include "timer.hpp"
#include "digit.hpp"

struct Graphic;

class Text {
public:
	Text(Graphic & graphic, Vector2<double> position, double width, double height);
	~Text();

	void update(double elapsedTime);
	void draw(Graphic & graphic, const Vector2<double> cameraOffset = {0.0, 0.0});
	void damage(double damage);
protected:
	SDL_Texture * texture;
	SDL_Rect sourceText;
	Vector2<double> position;
	double w, h;
};

class DamageText : public Text {
public:
	DamageText(Graphic & graphic, Vector2<double> position);
	~DamageText();
	void accumulateDamage(const double damage);
	void draw(Graphic & graphic, const Vector2<double> cameraOffset = {0.0, 0.0});
	void update(double elapsedTime, const Vector2<double> newPos);
	void resetClock();
	bool isTextShowing() const;
	void rise();
private:
	void resetDamage();
	Vector2<double> getSignOffset() const;
	std::pair<int, int> handleDigits();

	Digit onesColumn;	
	Digit tensColumn;	
	double riseLevel;
	double damage;
	Animation drawTime;
};

#endif 
