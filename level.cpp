#include <SDL2/SDL.h>
#include "level.h"
#include "graphic.h"
#include <iostream>
#include "tinyxml2.h"
#include "tile.h"
#include "tileset.h"

using namespace tinyxml2;

Level::Level(Graphic &graphic,std::string levelName, Vector2 spawnPoint):
spawnPoint(spawnPoint), currentLevelName(levelName), size(0,0), tileSize(0,0){
	this->mapLoader(levelName, graphic);
}

Level::~Level(){
	for(int i=0, n = this->tilesetList.size(); i < n; i++){
		delete this->tilesetList[i];
	}
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
				this->parseCSV(text, layerWidth, layerHeight, graphic);
			}else if(name == "Tile Layer 1"){
				//Genetare foreground tile (these tiles will be collidable with the player)
				this->parseCSV(text, layerWidth, layerHeight, graphic);
			}
				
			dataNode = dataNode->NextSiblingElement("data");
		}
		layerNode = layerNode->NextSiblingElement("layer");
	}
}

void Level::parseCSV(const char * text, int layerWidth, int layerHeight, Graphic &graphic){
	std::string csv = text;	
	int commaIndex = 0;
	int counter = 0; 
	int lastComma = 0; 
	int result = commaIndex;
	int layerX = 0, layerY = 0;
	int imageX = 0, imageY = 0;
	while(result != std::string::npos){
		commaIndex = csv.find(",", ++commaIndex);
		result = commaIndex;
		// get numbert
		std::string sGid = csv.substr(lastComma + 1, commaIndex - (lastComma + 1));	
		int gid = stoi(sGid);
		lastComma = commaIndex;
		if(gid > 0){
			Tile * tile = new Tile(gid, layerX, layerY);
			this->addTileToTileset(tile);
		}
		layerX++;

		if(++counter == layerWidth){
			lastComma++;
			layerY++;
			layerX = 0;
			counter = 0;	
		}
	}
}

void Level::addTileToTileset(Tile *tile){
	for(int i = 0, n = this->tilesetList.size(); i < n; i++){
		if(this->tilesetList[i]->addTile(tile)){
			break;
		}
	}
}

void Level::update(float elapsedTime){

}


void Level::draw(Graphic &graphic){
	for(int i = 0, n = this->tilesetList.size(); i < n; i++){
		this->tilesetList[i]->draw(graphic);
	}
}
