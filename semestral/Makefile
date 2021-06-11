#Zde bude funkcni Makefile.

CXX=g++
LD=g++
CXXFLAGS=-std=c++17 -w

all: gamebook

gamebook: main.o game.o choicer.o player.o gamedata.o action.o other.o enemy.o
	$(LD) $(CXXFLAGS) -o $@ $^ -lncurses

%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f *.o gamebook

deps:
	$(CXX) -MM src/*cpp > Makefile.d

-include Makefile.d