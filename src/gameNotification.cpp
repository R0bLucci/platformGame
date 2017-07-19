#include "../header/gameNotification.hpp"
#include "../header/player.hpp"
#include "../header/enemy.hpp"
#include "../header/bat.hpp"
#include "../header/text.hpp"
#include "../header/graphic.hpp"
#include "../header/dust.hpp"
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

void GameNotification::addDustNotifier(std::unique_ptr<Dust> dust){
	//this->dusts.push_back(std::unique_ptr<Dust>(std::move(dust)));
	this->dusts.emplace_back(std::move(dust));
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

	for(auto dust = this->dusts.begin(); dust != this->dusts.end(); ){
		if(!dust->get()->isDissipated()){
			dust->get()->update(elapsedTime);	
			++dust;
		}else{
			dust = this->dusts.erase(dust);
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
	for(unsigned int i = 0; i < this->dusts.size(); ++i){
		this->dusts[i]->draw(graphic, cameraOffset);
	}

	this->player.first->draw(graphic, cameraOffset);
}
