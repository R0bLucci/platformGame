CC=g++

CFLAGS=-Wall -Werror
LDFLAGS=-lSDL2 -lSDL2_image

CPPS=$(shell ls src/*.cpp)
TEMP=$(subst src/,obj/,$(CPPS))
OBJS=$(subst .cpp,.o,$(TEMP))
HEADERS=$(shell ls header/*.h)

RELEASE=bin/release
DEBUG=bin/debug

game: $(OBJS) $(HEADERS)
	$(CC) -o $(RELEASE)/$@ $(OBJS) $(CFLAGS) $(LDFLAGS)

dgame: $(OBJS) $(HEADERS)
	$(CC) -g -o $(DEBUG)/$@ $(OBJS) $(CFLAGS) $(LDFLAGS)
	
cleanobj: 
	rm $(OBJS)

obj/%.o: src/%.cpp
	$(CC) -c $(CFLAGS) $< -o $@
