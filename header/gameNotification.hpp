#ifndef GAME_NOTIFICATION_H
#define GAME_NOTIFICATION_H

#include <map>
#include <memory>
#include <vector>
#include "vector.hpp"
class Player;
class Enemy;
class DamageText;
class Graphic;
class Particle;

// Singleton class
// This class is responsible for the deletion of the DamageText pointers
class GameNotification {
private:	
	GameNotification();
	~GameNotification();
	static GameNotification * theGNInstance;
	std::map<std::shared_ptr<DamageText>, std::weak_ptr<Enemy>> enemies;
	std::pair<std::shared_ptr<DamageText>, std::weak_ptr<Player>> player;
	std::vector<std::unique_ptr<Particle>> particles;
	
	Vector2<double> position;
public:
	static GameNotification * createGameNotification();
	void addEnemyNotifier(const std::shared_ptr<Enemy> & enemy);
	void addPlayerNotifier(const std::shared_ptr<Player> &player);
	void addParticleNotifier(std::unique_ptr<Particle> particle);
	void update(double elapsedTime);
	void draw(Graphic & graphic, const Vector2<double> & cameraOffset);
};

#endif 
