#ifndef LEVEL_H
#define LEVEL_H

#include "globals.h"
#include <vector>
#include <string>

struct Graphic;
struct Tileset;
struct Tile;
struct Player;
struct Camera;
struct BoundingBox;

class Level {
public: 
	Level(Graphic &graphic,std::string levelName);
	~Level();

	void update(double elapsedTime, Player * player);
	void draw(Graphic &graphic);
	int getWidth();
	int getHeight();
	Vector2 getSpawnPoint();
	Camera * getCamera();
private:
	Vector2 size;
	Vector2 tileSize;
	Vector2 spawnPoint;
	std::string currentLevelName;
	std::vector<BoundingBox*> collidables;
	std::vector<Tileset*> tilesetList;
	int width;
	int height;
	Camera * camera;

	void setLevelWidthAndHeight(int w, int h);
	void mapLoader(std::string mapName, Graphic &graphic);
	void parseCSV(const char * text, std::string name, int layerWidht, int layerHeight);
	void addTileToTileset(Tile *tile);
};


#endif
