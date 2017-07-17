#ifndef LEVEL_H
#define LEVEL_H

#include "globals.hpp"
#include "vector.hpp"
#include <vector>
#include <string>
#include <memory>

struct Graphic;
struct Tileset;
struct Tile;
struct Player;
struct Camera;
struct BoundingBox;
struct Enemy;
struct Bullet;

class Level {
public: 
	Level(Graphic &graphic,std::string levelName);
	~Level();

	void update(double elapsedTime, std::shared_ptr<Player>& player);
	void draw(Graphic &graphic);
	int getWidth() const;
	int getHeight() const;
	Vector2<double> getSpawnPoint() const;
	Camera * getCamera() const;

	void handleBullet(Bullet * bullet);
	std::vector<BoundingBox*> collidables;
	std::vector<std::shared_ptr<Enemy>> enemies;
	std::vector<Bullet*> firedBullets;
private:
	Vector2<double> size;
	Vector2<double> tileSize;
	Vector2<double> spawnPoint;
	std::string currentLevelName;
	std::vector<Tileset*> tilesetList;
	int width;
	int height;
	Camera * camera;

	void setLevelWidthAndHeight(int w, int h);
	void mapLoader(std::string mapName, Graphic &graphic);
	void parseCSV(const char * text, std::string name, int layerWidht, int layerHeight);
	void addTileToTileset(std::unique_ptr<Tile> & tile);
	void generateEnemy(Graphic & graphic, std::string enemyType, const Vector2<double> & spawnPoint);
};


#endif
