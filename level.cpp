#include <SDL2/SDL.h>
#include "level.h"
#include "graphic.h"
#include <iostream>
#include "tinyxml2.h"
#include "tile.h"
#include "tileset.h"
#include "player.h"
#include "camera.h"
#include "boundingBox.h"

using namespace tinyxml2;

Level::Level(Graphic &graphic,std::string levelName, Vector2 spawnPoint):
spawnPoint(spawnPoint), currentLevelName(levelName), size(0,0), tileSize(0,0){
	this->mapLoader(levelName, graphic);
}

Level::~Level(){
	for(int i=0, n = this->tilesetList.size(); i < n; i++){
		delete this->tilesetList[i];
		this->tilesetList[i] = NULL;
	}

	for(int i=0, n = this->collidables.size(); i < n; i++){
		delete this->collidables[i];
		this->collidables[i] = NULL;
	}
	delete this->camera;
	this->camera = NULL;
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
	this->size = Vector2(width, height);
	
	int tileWidth = 0, tileHeight = 0;
	mapNode->QueryIntAttribute("tilewidth", &tileWidth);
	mapNode->QueryIntAttribute("tileheight", &tileHeight);
	this->tileSize = Vector2(tileWidth, tileHeight);

	// Determine the whole level width and hieght in pixels	
	this->setLevelWidthAndHeight(width * tileWidth, height * tileHeight);
	
	// set Camera for the level
	this->camera = new Camera(Vector2(), globals::WIDTH,
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
					Vector2(std::ceil(x) * globals::SPRITE_SCALER,
					std::ceil(y) * globals::SPRITE_SCALER), 
					std::ceil(width) * globals::SPRITE_SCALER, 
					std::ceil(height) * globals::SPRITE_SCALER);
				this->collidables.push_back(box);
			}
			obj = obj->NextSiblingElement("object");
		}
		objGroup = objGroup->NextSiblingElement("objectgroup");
	}
}

void Level::parseCSV(const char * text, std::string name, int layerWidth, int layerHeight){
	std::string csv = text;	
	int commaIndex = 0; // Index position of the last occurance of a comma
	int counter = 0; // Check when the csv has a new line character 
	int lastComma = 0; // Save index position of the second last comma that was found 
	int result = commaIndex; // Value to check when the csv formatted string has ended
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
			Tile * tile = new Tile(gid, layerX, layerY);
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

int Level::getWidth(){
	return this->width;
}

int Level::getHeight(){
	return this->height;
}

void Level::addTileToTileset(Tile *tile){
	for(int i = 0, n = this->tilesetList.size(); i < n; i++){
		if(this->tilesetList[i]->addTile(tile)){ 
			break;
		}
	}
}

void Level::update(double elapsedTime, Player * player){	
	std::vector<BoundingBox> onScreen;
	//std::vector<Tile *> onScreen;
	for(int i = 0, n = this->collidables.size(); i < n; i++){
		BoundingBox * b = this->collidables[i];
		if(b->isOnCamera(this->camera) && player->isColliding(b)){
			BoundingBox copy = *b;
			/*copy.setOrigin(
			Vector2(((copy.x - this->camera->getPosition().x)),
				((copy.y - this->camera->getPosition().y)))
			);
			copy.setWidth(copy.getWidth() - this->camera->getPosition().x);
			copy.setHeight(copy.getHeight() - this->camera->getPosition().y);*/
			onScreen.push_back(copy);
			player->handleCollision2(onScreen);
		}
	}
	//player->handleCollision(this->collidables);
	/*for(int i = 0, n = this->tilesetList.size(); i < n; i++){
		Tileset * ts = this->tilesetList[i];
		onScreen = ts->update(elapsedTime, this->camera);
	}
	player->handleTileCollision(onScreen);*/

	//this->camera->move(player->getPosition().x,
	//		player->getPosition().y);
}

void Level::draw(Graphic &graphic){
	for(int i = 0, n = this->tilesetList.size(); i < n; i++){
		this->tilesetList[i]->draw(graphic, *this->camera);
	}
}

Camera* Level::getCamera(){
	return this->camera;
}
