#ifndef PARTICLE_H
#define PARTICLE_H

#include "vector.hpp"
#include "timer.hpp"
#include <SDL2/SDL.h>

class Graphic;

class Particle {
public:
	Particle(Graphic & graphic, std::string textureName, const int sourceX, const int sourceY, 
	const int width, const int height, double animationInMS, 
	int initialFrame, const int frames, const Vector2<double> & position, bool startAnimation = true);

	virtual ~Particle();
	virtual void update(double elapsedTime);
	virtual void draw(Graphic & graphic, const Vector2<double> & cameraOffset);

	virtual void setPos(const Vector2<double> & position);
	bool isDone() const;
	void resetCurrentFrame();
	void stopAnimation();
	void startAnimation();
protected:
	void setSource();
	Vector2<double> getCenteredPosition() const;

	SDL_Texture * texture;
	SDL_Rect source;

	Timer timer;
	const int X,Y;
	const int W, H;
	int currentFrame;
	const int START_FRAME;
	const int FRAMES;	
	Vector2<double> position;
};
#endif
