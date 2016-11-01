game: animatedSprite.cpp boundingBox.cpp graphic.cpp camera.cpp game.cpp globals.h HUD.cpp player.cpp input.cpp level.cpp tinyxml2.cpp main.cpp sprite.cpp tileset.cpp utils.h tile.cpp
	g++ -Wall -Werror -o bin/game animatedSprite.cpp boundingBox.cpp graphic.cpp camera.cpp player.cpp globals.h HUD.cpp input.cpp level.cpp tinyxml2.cpp main.cpp sprite.cpp tileset.cpp utils.h tile.cpp game.cpp -lSDL2 -lSDL2_image

dgame: animatedSprite.cpp boundingBox.cpp graphic.cpp camera.cpp game.cpp globals.h HUD.cpp player.cpp input.cpp level.cpp tinyxml2.cpp main.cpp sprite.cpp tileset.cpp utils.h tile.cpp
	g++ -Wall -Werror -g -o bin/debug/dgame animatedSprite.cpp boundingBox.cpp graphic.cpp camera.cpp player.cpp globals.h HUD.cpp input.cpp level.cpp tinyxml2.cpp main.cpp sprite.cpp tileset.cpp utils.h tile.cpp game.cpp -lSDL2 -lSDL2_image
