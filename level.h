#ifndef LEVEL_H
#define LEVEL_H

#include "globals.h"
#include "boundingBox.h"
#include <vector>
#include <string>

struct Graphic;
struct Tileset;
struct Tile;

class Level {
public: 
	Level(Graphic &graphic,std::string levelName, Vector2 spawnPoint);
	~Level();

	void update(double elapsedTime);
	void draw(Graphic &graphic);
private:
	Vector2 size;
	Vector2 tileSize;
	Vector2 spawnPoint;
	std::string currentLevelName;
	std::vector<BoundingBox> collaidables;
	std::vector<Tileset*> tilesetList;

	void mapLoader(std::string mapName, Graphic &graphic);
	void parseCSV(const char * text, int layerWidht, int layerHeight, Graphic &graphic);
	void addTileToTileset(Tile *tile);
};


#endif
