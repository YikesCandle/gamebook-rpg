CXX=g++
LD=g++
CXXFLAGS=-std=c++17 -Wall -pedantic

all: bednaji2

compile: bednaji2
	rm -f *.om

run: bednaji2
	./bednaji2

bednaji2: main.o game.o player.o gamedata.o action.o other.o enemy.o choicer.o
	$(LD) $(CXXFLAGS) -o $@ $^ -lncurses

%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f *.o bednaji2
	if [ -d "doc" ]; then rm -rf doc; fi

deps:
	$(CXX) -MM src/*cpp > Makefile.d

doc:
	doxygen Doxyfile
	mv html doc


-include Makefile.d