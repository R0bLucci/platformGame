#ifndef TILESET_H
#define TILESET_H

#include "graphic.h"
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <memory>
#include <iostream>

class Tile;
class Camera;

class Tileset {
private:
	int firstgid;
	int tileWidth;
	int tileHeight;
	int tileCount;
	int columns;
	std::vector<Tile*> tiles;
	class Image {
		public:
			Image(std::string source, int imageWidth, int imageHeight, Graphic &graphic):
			width(imageWidth), height(imageHeight), source(source){ 
				this->createTexture(graphic);
			}
			~Image() {}
			
			inline int getWidth() const { return this->width; }
			inline int getHeight() const { return this->height; }
			inline std::string getSource() const { return this->source; }
			inline std::string getSourcePath() const { return "resources/level/" + this->source; }
			inline SDL_Texture * getTexture() const { return this->texture; }
		private:
			int width;
			int height;
			std::string source;
			Graphic graphic;
			SDL_Texture * texture;

			void createTexture(Graphic &graphic){
				std::cout << "TileSet::Image source: " << this->source << std::endl;
				this->texture = graphic.getTexture(this->source);
				std::cout << "Texture source addr: " << this->texture << std::endl;
			}
	};	
	Image image;
public:
	Tileset(int firstgid, int tileWidth, int tileHeight, int tileCount, int columns, std::string source, 
			int imageWidth, int imageHeight, Graphic &graphic);
	~Tileset();
	int getFirstgid() const;
	int getTileWidth() const;
	int getTileHeight() const;
	int getTileCount() const;
	int getColumns() const;
	Image getImage() const;
	bool addTile(Tile *tile);
	void draw(Graphic &graphic, Camera & camera);
	std::vector<Tile *>  update(double elapedTime, Camera * camera);

	std::vector<Tile*> getTiles();
};

#endif
