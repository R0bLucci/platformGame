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
		this->tilesetList[i] = NULL;
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
				this->parseCSV(text, layerWidth, layerHeight);
			}else if(name == "Tile Layer 1"){
				//Genetare foreground tile (these tiles will be collidable with the player)
				this->parseCSV(text, layerWidth, layerHeight);
			}
				
			dataNode = dataNode->NextSiblingElement("data");
		}
		layerNode = layerNode->NextSiblingElement("layer");
	}
}

void Level::parseCSV(const char * text, int layerWidth, int layerHeight){
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

void Level::update(double elapsedTime){

}


void Level::draw(Graphic &graphic){
	for(int i = 0, n = this->tilesetList.size(); i < n; i++){
		this->tilesetList[i]->draw(graphic);
	}
}
