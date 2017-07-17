#include "../header/gameNotification.hpp"
#include "../header/player.hpp"
#include "../header/enemy.hpp"
#include "../header/bat.hpp"
#include "../header/text.hpp"
#include "../header/graphic.hpp"
#include "../header/logger.hpp"

GameNotification * GameNotification::theGNInstance = nullptr;

GameNotification::GameNotification(){}

GameNotification::~GameNotification(){
	if(GameNotification::theGNInstance)
		delete GameNotification::theGNInstance;
}

GameNotification * GameNotification::createGameNotification(){
	if(!GameNotification::theGNInstance){
		GameNotification::theGNInstance = new GameNotification();	
	}
	return GameNotification::theGNInstance;
}

void GameNotification::addEnemyNotifier(const std::shared_ptr<Enemy> & enemy){
	logger::log("add enemy notifier", enemy);
	this->enemies[enemy->getDamageText()] = std::weak_ptr<Enemy>(enemy);
}

void GameNotification::addPlayerNotifier(const std::shared_ptr<Player> & player){
	this->player = std::make_pair(player->getDamageText(), std::weak_ptr<Player>(player));
}

void GameNotification::update(double elapsedTime){
	for(auto it = this->enemies.begin(); it != this->enemies.end(); ){
		std::weak_ptr<Enemy> weakEnemy = it->second;
		if(!weakEnemy.expired()){
			std::shared_ptr<Enemy> enemy(weakEnemy);	
			it->first->setPos(enemy->getCenteredPosition());
		}

		if(!it->first->update(elapsedTime) && weakEnemy.expired()){
			logger::log("delete text damage");
			it = this->enemies.erase(it);
		} else {
			++it;
		}
	}	

	std::shared_ptr<Player> p(this->player.second);	
	this->player.first->setPos(p->getCenteredPosition());
	this->player.first->update(elapsedTime);
}

void GameNotification::draw(Graphic & graphic, const Vector2<double> & cameraOffset){
	for(auto it = this->enemies.begin(); it != this->enemies.end(); ++it){
		it->first->draw(graphic, cameraOffset);
	}	
	this->player.first->draw(graphic, cameraOffset);
}
