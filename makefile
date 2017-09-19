CC=g++

CFLAGS=-Wall -Werror
LDFLAGS=-lSDL2 -lSDL2_image
LDGTEST_FLAGS=-lgtest

CPPS=$(shell ls src/*.cpp)
TEST_CPPS=$(shell ls test/*.cpp)
TEMP=$(subst src/,obj/,$(CPPS))
OBJS=$(subst .cpp,.o,$(TEMP))
HEADERS=$(shell ls header/*.hpp)

RELEASE=bin/release
DEBUG=bin/debug
TEST=bin/test

run: 
	$(RELEASE)/game
drun: 
	$(DEBUG)/dgame
run_gtest:
	$(TEST)/gtest	
gtest: 
	$(CC) $(LDGTEST_FLAGS) -o $(TEST)/$@ $(TEST_CPPS)
	
game: $(OBJS) $(HEADERS)
	$(CC) -o $(RELEASE)/$@ $(OBJS) $(CFLAGS) $(LDFLAGS)

dgame: $(OBJS) $(HEADERS)
	$(CC) -g -o $(DEBUG)/$@ $(OBJS) $(CFLAGS) $(LDFLAGS)
	
cleanobj: 
	rm $(OBJS)

obj/%.o: src/%.cpp
	$(CC) -c $(CFLAGS) $< -o $@
