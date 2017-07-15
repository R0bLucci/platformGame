#include <SDL2/SDL.h>
#include "../header/level.hpp"
#include "../header/graphic.hpp"
#include <iostream>
#include "../header/tinyxml2.hpp"
#include "../header/tile.hpp"
#include "../header/tileset.hpp"
#include "../header/player.hpp"
#include "../header/camera.hpp"
#include "../header/boundingBox.hpp"
#include "../header/bat.hpp"
#include "../header/bullet.hpp"
#include "../header/logger.hpp"

using namespace tinyxml2;

Level::Level(Graphic &graphic,std::string levelName):
size(0,0), tileSize(0,0),
spawnPoint(Vector2<double>(0.0, 0.0)), currentLevelName(levelName),
width(0), height(0){
	this->mapLoader(levelName, graphic);
}

Level::~Level(){
	for(int i=0, n = this->tilesetList.size(); i < n; ++i){
		delete this->tilesetList[i];
		this->tilesetList[i] = nullptr;
	}

	for(int i=0, n = this->collidables.size(); i < n; ++i){
		delete this->collidables[i];
		this->collidables[i] = nullptr;
	}
	for(int i=0, n = this->enemies.size(); i < n; ++i){
		delete this->enemies[i];
		this->enemies[i] = nullptr;
	}
	delete this->camera;
	this->camera = nullptr;
}

void Level::mapLoader(std::string mapName, Graphic &graphic){
	XMLDocument doc;
	std::string level("resources/level/"+ mapName + ".tmx");
	XMLError isLoaded = doc.LoadFile(level.c_str());

	if(isLoaded != XML_SUCCESS){
		std::cout << "Error loading map" << std::endl;
		std::cout << doc.ErrorID() << std::endl;
		return;
	}

	// Get map node attribute 
	XMLElement * mapNode = doc.FirstChildElement("map");
	int width = 0, height = 0;
	mapNode->QueryIntAttribute("width", &width);
	mapNode->QueryIntAttribute("height", &height);
	this->size = Vector2<double>(width, height);
	
	int tileWidth = 0, tileHeight = 0;
	mapNode->QueryIntAttribute("tilewidth", &tileWidth);
	mapNode->QueryIntAttribute("tileheight", &tileHeight);
	this->tileSize = Vector2<double>(tileWidth, tileHeight);

	// Determine the whole level width and hieght in pixels	
	this->setLevelWidthAndHeight(width * tileWidth, height * tileHeight);
	
	// set Camera for the level
	this->camera = new Camera(Vector2<double>(), globals::WIDTH,
				globals::HEIGHT, this->width * globals::SPRITE_SCALER, this->height * globals::SPRITE_SCALER);
	XMLElement * tilesetNode = mapNode->FirstChildElement("tileset");
	while(tilesetNode){
		//Get tileset attribute keep looping if there are more than onetile set	
		int firstgid = 0, tileWidth = 0, tileHeight = 0, tileCount = 0, columns = 0;
		tilesetNode->QueryIntAttribute("firstgid", &firstgid);
		tilesetNode->QueryIntAttribute("tilewidth", &tileWidth);
		tilesetNode->QueryIntAttribute("tileheight", &tileHeight);
		tilesetNode->QueryIntAttribute("tilecount", &tileCount);
		tilesetNode->QueryIntAttribute("columns", &columns);

		XMLElement * imageNode = tilesetNode->FirstChildElement("image");	
		while(imageNode){
			int imageWidth = 0, imageHeight = 0;
			imageNode->QueryIntAttribute("width", &imageWidth);	
			imageNode->QueryIntAttribute("height", &imageHeight);	
			const char * source = imageNode->Attribute("source");
			
			Tileset *ts = new Tileset(firstgid, tileWidth, tileHeight, tileCount, columns, source,
						imageWidth, imageHeight, graphic);

			this->tilesetList.push_back(ts);

			imageNode = imageNode->NextSiblingElement("image");	
		}
		tilesetNode = tilesetNode->NextSiblingElement("tileset");	
	}
	
	XMLElement * layerNode = mapNode->FirstChildElement("layer");
	while(layerNode){
		std::string name = layerNode->Attribute("name");	
		
		XMLElement * dataNode = layerNode->FirstChildElement("data");
		const char * text = dataNode->GetText();
		int layerWidth = 0, layerHeight = 0;
		layerNode->QueryIntAttribute("width", &layerWidth);
		layerNode->QueryIntAttribute("height", &layerHeight);
		while(dataNode){
			if(name == "background"){
				//Generate backgound tile
				this->parseCSV(text, name, layerWidth, layerHeight);
			}else if(name == "Tile Layer 1"){
				//Genetare foreground tile (these tiles will be collidable with the player)
				this->parseCSV(text, name, layerWidth, layerHeight);
			}
				
			dataNode = dataNode->NextSiblingElement("data");
		}
		layerNode = layerNode->NextSiblingElement("layer");
	}
	
	XMLElement * objGroup = mapNode->FirstChildElement("objectgroup");
	while(objGroup){
		std::string name = objGroup->Attribute("name");
		XMLElement * obj = objGroup->FirstChildElement("object");	
		while(obj){
			if(name == "collidables"){
				double x = 0, y = 0, width = 0, height = 0;	
				obj->QueryDoubleAttribute("x", &x);
				obj->QueryDoubleAttribute("y", &y);
				obj->QueryDoubleAttribute("width", &width);
				obj->QueryDoubleAttribute("height", &height);
				BoundingBox * box = new BoundingBox(
					Vector2<double>(std::ceil(x) * globals::SPRITE_SCALER,
					std::ceil(y) * globals::SPRITE_SCALER), 
					std::ceil(width) * globals::SPRITE_SCALER, 
					std::ceil(height) * globals::SPRITE_SCALER);
				this->collidables.push_back(box);
			}else if(name == "spawn"){
				double x, y;
				obj->QueryDoubleAttribute("x", &x);
				obj->QueryDoubleAttribute("y", &y);
				this->spawnPoint = Vector2<double>(std::ceil(x) * globals::SPRITE_SCALER, 
							std::ceil(y) * globals::SPRITE_SCALER);
			}else if(name == "enemies"){
				double x = 0, y = 0;	
				std::string enemyType = obj->Attribute("name");
				obj->QueryDoubleAttribute("x", &x);
				obj->QueryDoubleAttribute("y", &y);
				this->generateEnemy(graphic, enemyType, 
						Vector2<double>(x, y) * globals::SPRITE_SCALER); 
			}
			obj = obj->NextSiblingElement("object");
		}
		objGroup = objGroup->NextSiblingElement("objectgroup");
	}
}

void Level::generateEnemy(Graphic & graphic, std::string enemyType, const Vector2<double> & spawnPoint){
	if(enemyType == "bat") {
		this->enemies.push_back(new Bat(graphic, spawnPoint));
	}
}

void Level::parseCSV(const char * text, std::string name, int layerWidth, int layerHeight){
	std::string csv = text;	
	bool isBackground = (name == "background");
	int commaIndex = 0; // Index position of the last occurance of a comma
	int counter = 0; // Check when the csv has a new line character 
	int lastComma = 0; // Save index position of the second last comma that was found 
	std::size_t result = commaIndex; // Value to check when the csv formatted string has ended
	int layerX = 0, layerY = 0; // Origin point (x,y) of the square in the map
	while(result != std::string::npos){
		commaIndex = csv.find(",", ++commaIndex);
		result = commaIndex;
		// get tile gid as a string
		std::string sGid = csv.substr(lastComma + 1, commaIndex - (lastComma + 1));	
		// Convert gid to interger
		int gid = stoi(sGid);
		// Save last index of the comma for the next iteration
		lastComma = commaIndex;
		// Create a new tile only if the gid is positive
		// a gid of zero means that the tile is empty
		if(gid > 0){
			std::unique_ptr<Tile> tile(new Tile(gid, layerX, layerY, isBackground));
			//Tile * tile = new Tile(gid, layerX, layerY);
			this->addTileToTileset(tile);
		}
		// Increment x to move the origin point by one at each iteration 
		layerX++;

		// Check if a row is completely trasversed in that case
		// Reset the x point and the counter to zero and increment y by one.
		// Incrememtn the comma index so that the new line character for the next row is skipped
		if(++counter == layerWidth){
			lastComma++;
			layerX = 0;
			counter = 0;	
			layerY++;
		}
	}
}
	
void Level::setLevelWidthAndHeight(int w, int h){
	this->width = w;
	this->height = h;
}

int Level::getWidth() const{
	return this->width;
}

int Level::getHeight() const{
	return this->height;
}

void Level::addTileToTileset(std::unique_ptr<Tile>& tile){
	for(int i = 0, n = this->tilesetList.size(); i < n; i++){
		if(this->tilesetList[i]->addTile(tile)){ 
			break;
		}
	}
}

void Level::update(double elapsedTime, std::unique_ptr<Player>& player){	
	std::vector<BoundingBox> onScreen;
	for(int i = 0, n = this->collidables.size(); i < n; i++){
		BoundingBox * b = this->collidables[i];
		//if(b->isOnCamera(this->camera) && player->isColliding(b)){
		if(this->camera->isOnCamera(*b) && player->isColliding(b)){
			BoundingBox copy = *b;
			onScreen.push_back(copy);
		}
	}

	for(int i = 0, n = this->enemies.size(); i < n; i++){
		this->enemies[i]->update(elapsedTime, *player, *this->camera);
	}

	if(onScreen.size() > 0){
		player->handleCollision2(onScreen);
	}

	if(this->firedBullets.size() > 0){
		//logger::log("bullets around", this->firedBullets.size());	
		std::vector<Bullet*>::iterator bullet = this->firedBullets.begin();
		while(bullet != this->firedBullets.end()){
			if((*bullet)){
				//logger::log("bullet to be updated", ((*bullet)));
				(*bullet)->update(elapsedTime, *this, bullet);
			}
			if(bullet != this->firedBullets.end()){
				++bullet;
			}
		}
	}


}

void Level::draw(Graphic &graphic){
	for(int i = 0, n = this->tilesetList.size(); i < n; i++){
		this->tilesetList[i]->draw(graphic, *this->camera);
	}

	for(int i = 0, n = this->enemies.size(); i < n; i++){
		if(this->enemies[i])
			this->enemies[i]->draw(graphic, *this->camera);
	}

	for(unsigned int i = 0; i < this->firedBullets.size();i++){
		if(this->firedBullets[i])
			this->firedBullets[i]->draw(graphic, *this->camera);
	}
}

Vector2<double> Level::getSpawnPoint() const{
	return this->spawnPoint;
}

Camera* Level::getCamera() const{
	return this->camera;
}

void Level::handleBullet(Bullet * bullet) {
	if(bullet){
		this->firedBullets.push_back(bullet);
	}
}
