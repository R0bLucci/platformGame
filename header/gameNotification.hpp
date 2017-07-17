#ifndef GAME_NOTIFICATION_H
#define GAME_NOTIFICATION_H

#include <map>
#include <memory>
#include "vector.hpp"
class Player;
class Enemy;
class DamageText;
class Graphic;

// Singleton class
// This class is responsible for the deletion of the DamageText pointers
class GameNotification {
private:	
	GameNotification();
	~GameNotification();
	static GameNotification * theGNInstance;
	std::map<std::shared_ptr<DamageText>, std::weak_ptr<Enemy>> enemies;
	std::pair<std::shared_ptr<DamageText>, std::weak_ptr<Player>> player;
	
	Vector2<double> position;
public:
	static GameNotification * createGameNotification();
	void addEnemyNotifier(const std::shared_ptr<Enemy> & enemy);
	void addPlayerNotifier(const std::shared_ptr<Player> &player);
	void update(double elapsedTime);
	void draw(Graphic & graphic, const Vector2<double> & cameraOffset);
};

#endif 
