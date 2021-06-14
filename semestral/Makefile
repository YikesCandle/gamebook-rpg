CXX=g++
LD=g++
CXXFLAGS=-std=c++17 -Wall -pedantic

all: gamebook

gamebook: main.o game.o player.o gamedata.o action.o other.o enemy.o choicer.o
	$(LD) $(CXXFLAGS) -o $@ $^ -lncurses

%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f *.o gamebook

deps:
	$(CXX) -MM src/*cpp > Makefile.d

-include Makefile.d