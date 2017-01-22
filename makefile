CC=g++

CFLAGS=-Wall -Werror
LDFLAGS=-lSDL2 -lSDL2_image

objects=main.o animatedSprite.o boundingBox.cpp graphic.o camera.o game.o HUD.o player.o \
input.o level.o tinyxml2.o sprite.o tileset.o tile.o 

game: $(objects) 
	$(CC) -o bin/game $(objects) $(CFLAGS) $(LDFLAGS)

dgame: $(objects)
	$(CC) -g -o bin/debug/dgame $(objects) $(CFLAGS) $(LDFLAGS)
	
cleanobj: 
	rm *.o 

main.o: main.cpp
	$(CC) -c $(CFLAGS) main.cpp

animatedSprite.o: animatedSprite.cpp
	$(CC) -c $(CFLAGS) animatedSprite.cpp

boundingBox.o: boudingBox.cpp
	$(CC) -c $(CFLAGS) boundingBox.cpp

graphic.o: graphic.cpp
	$(CC) -c $(CFLAGS) graphic.cpp

camera.o: camera.cpp
	$(CC) -c $(CFLAGS) camera.cpp

game.o: game.cpp
	$(CC) -c $(CFLAGS) game.cpp
	
HUD.o: HUD.cpp
	$(CC) -c $(CFLAGS) HUD.cpp

player.o: player.cpp
	$(CC) -c $(CFLAGS) player.cpp

input.o: input.cpp
	$(CC) -c $(CFLAGS) input.cpp

level.o: level.cpp
	$(CC) -c $(CFLAGS) level.cpp
	
tinyxml2.o: tinyxml2.cpp
	$(CC) -c $(CFLAGS) tinyxml2.cpp

sprite.o: sprite.cpp
	$(CC) -c $(CFLAGS) sprite.cpp

tileset.o: tileset.cpp
	$(CC) -c $(CFLAGS) tileset.cpp

tile.o: tile.cpp
	$(CC) -c $(CFLAGS) tile.cpp
