#ifndef LEVEL_H
#define LEVEL_H

#include "globals.h"
#include <vector>
#include <string>

struct Graphic;
struct Tileset;
struct Tile;
struct Player;
struct BoundingBox;

class Level {
public: 
	Level(Graphic &graphic,std::string levelName, Vector2 spawnPoint);
	~Level();

	void update(double elapsedTime, Player * player);
	void draw(Graphic &graphic);
private:
	Vector2 size;
	Vector2 tileSize;
	Vector2 spawnPoint;
	std::string currentLevelName;
	std::vector<BoundingBox*> collidables;
	std::vector<Tileset*> tilesetList;

	void mapLoader(std::string mapName, Graphic &graphic);
	void parseCSV(const char * text, std::string name, int layerWidht, int layerHeight);
	void addTileToTileset(Tile *tile);
};


#endif
